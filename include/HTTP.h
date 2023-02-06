#include "Microcontroller.h"

#ifndef HTTP_H
#define HTTP_H

class HTTP
{
private:
    bool _connected;
    String _getPayload(String message);
    bool _sendPayload(String url, short port, String path, String payload);
    
public:
    HTTP();
    bool connect(String ssid, String password);
    bool sendMessage(String message, String host, short port, String chatPath);
};

#endif