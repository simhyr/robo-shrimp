#include <NTPClient.h>
#include <WiFiUdp.h>
#include "Microcontroller.h"
#include "EspHttpClient.h"
#include "StepMotor.h"
#include "EspRtcMemory.h"
#include "EspRandomizer.h"

unsigned const long FIVE_MINUTES = 3e8;
unsigned const long FIFTEEEN_MINUTES = 9e8;

WiFiUDP udp;
NTPClient ntp(udp, "europe.pool.ntp.org", 3600);
EspHttpClient http;
EspRtcMemory memory;

const String FISH_ICONS[] = {":fish:", ":crocodile:", ":blowfish:", ":whale:", ":tropical_fish:", ":turtle:", ":shrimp:" };

void feed() 
{
  StepMotor stepMotor(D1, D2, D3, D4);
  stepMotor.stepDegree(180);
  delay(5000);
  stepMotor.stepDegree(180);
}

void notify(String message) 
{
  http.sendMessage(message, "192-168-1-3.simdat.direct.quickconnect.to", 5001, 
    "/webapi/entry.cgi?api=SYNO.Chat.External&method=incoming&version=2&token=%22ELv0mYDDbxtxW5Q1GgFQ8oEvjGBOitzadyA4R3FgMMqPreKGBmPTxg7CEiVQymrX%22");
}

String getDayName(unsigned long day) {
  switch(day) {
    case 1:
      return "Sonntag";
    case 2:
      return "Montag";
    case 3:
      return "Dienstag";
    case 4:
      return "Mittwoch";
    case 5:
      return "Donnerstag";
    case 6:
      return "Freitag";
    case 7:
      return "Samstag";
  }

  return "<Fehler: Wochentag konnte nicht ermittelt werden>";
}

void loop() 
{
  while(!ntp.update()) 
  {
    notify("Verbindung zum Zeitserver fehlgeschlagen. Nächster Versuch in 5 Minuten..");
    delay(3e5);
  }

  //notify("Bin soeben aufgewacht. Es ist " + ntp.getFormattedTime() + " Uhr.");  
  // get the next feed day (0: if no deepSleep interrupt)
  uint32_t nextFeedDay = memory.read(0);
  // So = 1, Sa = 7
  unsigned long today = ntp.getDay() + 1;
  auto hours = ntp.getHours();
  if(nextFeedDay == 0 || (nextFeedDay == today && hours >= 15 && hours <= 17))
  {
    // feed
    digitalWrite(LED_BUILTIN, LOW);
    feed();
    // feed daily
    nextFeedDay = (today % 7) + 1;
    notify("Die "+FISH_ICONS[today - 1]+" wurden um "+ntp.getFormattedTime()+" Uhr gefüttert! Nächste Fütterung am " + getDayName(nextFeedDay) + ".");
    digitalWrite(LED_BUILTIN, HIGH);

    memory.write(0, nextFeedDay);
  }

  ESP.deepSleep(FIFTEEEN_MINUTES, RF_DEFAULT);
}


void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);

  // motor pins
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  // connect to wifi
  http.connect(WIFI_SSID, WIFI_PASSWORD);
  // start ntp-client
  ntp.begin();
}