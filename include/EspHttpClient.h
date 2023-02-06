#include "Microcontroller.h"

#ifndef ESPHTTPCLIENT_H
#define ESPHTTPCLIENT_H

class EspHttpClient
{
private:
    bool _connected;
    String _getPayload(String message);
    bool _sendPayload(String url, short port, String path, String payload);
    
public:
    EspHttpClient();
    bool connect(String ssid, String password);
    bool sendMessage(String message, String host, short port, String chatPath);
};

#endif