#ifndef Himace_H
#define Himace_H
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

class Himace
{
private:
    char* wifiName;
    char* wifiPassword;
    String serverName;
    bool isReconnect;
    String authToken = "";
    void connectionCheck();
public:
    Himace();
    void setWifi(char* ssid, char* password);
    void wifiConnect();
    void setServerName(String server);
    void setToken(String token);
    void reconnect(bool enable);
    String get(String path);
    void post(String path, String data, String type);
    void setFloat(String variableName, float value);
    void setInteger(String variableName, int value);
    void setBoolean(String variableName, bool value);
    void setString(String variableName, String value);
};


#endif