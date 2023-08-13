#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <Firebase_ESP_Client.h>
// #include <ArduinoJson.h>

class Network
{
private:
    FirebaseData firebaseData;
    FirebaseAuth firebaseAuth;
    FirebaseConfig firebaseConfig;
    // StaticJsonDocument<200> jsonDocument;
    // DynamicJsonDocument jsonDocument;
    String databasePath;

    void initFirebase();
    void initWifi();
    void setFirebasePath();

public:
    // static Network *getInstance();
    Network();

    void updateTemperature(float temperature, unsigned long time);
    void updateTime(const char *timePath, unsigned long time);
};

#endif
