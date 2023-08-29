#ifndef NETWORKN_HPP
#define NETWORKN_HPP

#include <ESP8266WiFi.h>
#include "configData.hpp"

class Network
{
public:
    bool getConfigMode();

    void APMode();

    void connectToWifi();

    static Network &getInstance(ConfigData &configData);

    static bool configMode;
private:
    WiFiServer server;
    ConfigData &configData;
    static Network *instance;

    Network(ConfigData &configData);

    static void IRAM_ATTR setAP();

    // Private copy constructor and assignment operator to prevent copying
    Network(const Network &) = delete;
    Network &operator=(const Network &) = delete;
};

#endif