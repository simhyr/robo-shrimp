#include "HTTP.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

HTTP::HTTP() 
{
    _connected = false;
}

bool HTTP::connect(String ssid, String password)
{
  WiFi.persistent(false);
  
  // only actively connect to wifi networks  
  WiFi.mode(WIFI_STA);
  // can not handle &String parameters -> must be char*
  WiFi.begin(ssid.c_str(), password.c_str());

  int counter = 1;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);

    if(counter >= 3600) {
        this->_connected = false;
        break;
    }

    counter++;
  }

  if(WiFi.status() == WL_CONNECTED)
    this->_connected = true;

  return this->_connected;
}

String HTTP::_getPayload(String message) {
    DynamicJsonDocument doc(1024);
    doc["text"] = message;

    String result;
    serializeJson(doc, result);

    return "payload=" + result;
}

bool HTTP::_sendPayload(String host, short port, String path, String payload) {
    WiFiClientSecure client;
    // certificate validation
    client.setInsecure();
    
    HTTPClient https;
    // HTTPC_ERROR_READ_TIMEOUT
    https.setTimeout((unsigned short) 60000);
    https.begin(client, host, port, path, true);
    //https.addHeader("Content-Type", String("application/json"));

    int httpCode = https.POST(payload);   
    https.end();

    return httpCode == HTTP_CODE_OK;
}

bool HTTP::sendMessage(String message, String host, short port, String chatPath)
{
    if(!this->_connected) return false;

    auto payload = _getPayload(message);

    return _sendPayload(host, port, chatPath, payload);
}