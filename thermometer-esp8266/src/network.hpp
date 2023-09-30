#ifndef NETWORKN_HPP
#define NETWORKN_HPP

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "configData.hpp"

class Network
{
public:
    static bool getConfigMode();

    void APMode();

    void connectToWifi();

    static Network &getInstance(ConfigData &configData);

    static bool configMode;

    // typedef enum CONFIG_MODE
    // {
    //     CONFIG_MODE_THERMOMETER,
    //     CONFIG_MODE_AP,

    // }CONFIG_MODE;

private:
    ESP8266WebServer server;
    ConfigData &configData;
    static Network *instance;

    Network(ConfigData &configData);

    static void IRAM_ATTR setAP();

    void handleUpdate();

    // Private copy constructor and assignment operator to prevent copying
    Network(const Network &) = delete;
    Network &operator=(const Network &) = delete;
};

#endif