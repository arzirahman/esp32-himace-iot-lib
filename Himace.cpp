#include "Himace.h"

Himace::Himace(){}

void Himace::setWifi(char* ssid, char* password){
    wifiName = ssid;
    wifiPassword = password;
}

void Himace::setServerName(String server){
    serverName = server;
}

void Himace::setToken(String token){
    authToken = token;
}

void Himace::reconnect(bool enable){
    isReconnect = enable;
}

void Himace::wifiConnect(){
    WiFiClass wifi;
    wifi.begin(wifiName, wifiPassword);
    Serial.print("Connecting");
    while(wifi.status() != 3) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println(" ");
    Serial.println(" ");
    Serial.println("Connected");
    Serial.println(" ");
    delay(1000);
}

void Himace::connectionCheck(){
    WiFiClass wifi;
    if(wifi.status() != 3){
        wifi.begin(wifiName, wifiPassword);
        Serial.print("Connecting");
        while(wifi.status() != 3) {
            delay(1000);
            Serial.print(".");
        }
        Serial.println(" ");
        Serial.println(" ");
        Serial.println("Connected");
        Serial.println(" ");
        delay(1000);
    }
}

String Himace::get(String path){
    if(isReconnect) connectionCheck();
    HTTPClient http;
    String payload;
    http.begin((serverName + path).c_str());
    http.addHeader("api_key",authToken);
    int httpResponseCode = http.GET();
    if (httpResponseCode>0) {
        payload = http.getString();
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        payload = httpResponseCode;
    }
    http.end();
    return payload;
}

void Himace::post(String path, String data, String type){
    if(isReconnect) connectionCheck();
    HTTPClient http;
    http.begin((serverName + path));
    http.addHeader("Content-Type", type);
    http.addHeader("api_key",authToken);
    int httpResponseCode = http.POST(data);
    if (httpResponseCode>0) {
        if(httpResponseCode == 200){
            Serial.println("Response Status: OK");
        }
        else{
            Serial.print("Response Status: ");
            Serial.println(httpResponseCode);
        }
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    http.end();
}

void Himace::setInteger(String variableName, int value){
    if(isReconnect) connectionCheck();
    JSONVar payload;
    HTTPClient http;
    http.begin((serverName + "/iot/device/variable/set"));
    http.addHeader("Content-Type", "application/json");
    http.addHeader("api_key",authToken);
    int httpResponseCode = http.POST("{\"variableName\":\"" + variableName + "\",\"value\":" + String(value) + "}");
    if (httpResponseCode>0) {
        payload = JSON.parse(http.getString());
        if(JSON.stringify(payload["code"]) == "\"HMC180\"") Serial.println("ok");
        else if(JSON.stringify(payload["code"]) == "\"HMC191\"") Serial.println("data type doesn't match");
        else Serial.println(JSON.stringify(payload["code"]));
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    http.end();
}

void Himace::setFloat(String variableName, float value){
    if(isReconnect) connectionCheck();
    JSONVar payload;
    HTTPClient http;
    http.begin((serverName + "/iot/device/variable/set"));
    http.addHeader("Content-Type", "application/json");
    http.addHeader("api_key",authToken);
    int httpResponseCode = http.POST("{\"variableName\":\"" + variableName + "\",\"value\":" + String(value) + "}");
    if (httpResponseCode>0) {
        payload = JSON.parse(http.getString());
        if(JSON.stringify(payload["code"]) == "\"HMC180\"") Serial.println("ok");
        else if(JSON.stringify(payload["code"]) == "\"HMC191\"") Serial.println("data type doesn't match");
        else Serial.println(JSON.stringify(payload["code"]));
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    http.end();
}

void Himace::setBoolean(String variableName, bool value){
    if(isReconnect) connectionCheck();
    JSONVar payload;
    String strValue;
    if(value) strValue = "true";
    else if(!value) strValue = "false";
    HTTPClient http;
    http.begin((serverName + "/iot/device/variable/set"));
    http.addHeader("Content-Type", "application/json");
    http.addHeader("api_key",authToken);
    int httpResponseCode = http.POST("{\"variableName\":\"" + variableName + "\",\"value\":" + strValue + "}");
    if (httpResponseCode>0) {
        payload = JSON.parse(http.getString());
        if(JSON.stringify(payload["code"]) == "\"HMC180\"") Serial.println("ok");
        else if(JSON.stringify(payload["code"]) == "\"HMC191\"") Serial.println("data type doesn't match");
        else Serial.println(JSON.stringify(payload["code"]));
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    http.end();
}

void Himace::setString(String variableName, String value){
    if(isReconnect) connectionCheck();
    JSONVar payload;
    HTTPClient http;
    http.begin((serverName + "/iot/device/variable/set"));
    http.addHeader("Content-Type", "application/json");
    http.addHeader("api_key",authToken);
    int httpResponseCode = http.POST("{\"variableName\":\"" + variableName + "\",\"value\":\"" + value + "\"}");
    if (httpResponseCode>0) {
        payload = JSON.parse(http.getString());
        if(JSON.stringify(payload["code"]) == "\"HMC180\"") Serial.println("ok");
        else if(JSON.stringify(payload["code"]) == "\"HMC191\"") Serial.println("data type doesn't match");
        else Serial.println(JSON.stringify(payload["code"]));
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    http.end();
}