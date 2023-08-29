#include <ESP8266WiFi.h>
#include "network.hpp"
#include "debugUtils.hpp"

#define MAX_CONNECTION 1
#define CONFIG_INPUT_PIN D2
#define SERVER_PORT 12345

Network *Network::instance = nullptr; // Initialize to nullptr or an appropriate value
bool Network::configMode = false;     // Initialize to nullptr or an appropriate value

Network::Network(ConfigData &configData) : server(SERVER_PORT), configData(configData)
{

    pinMode(CONFIG_INPUT_PIN, INPUT_PULLUP);
    // attachInterruptArg(digitalPinToInterrupt(CONFIG_INPUT_PIN), &Network::setAP, this, CHANGE);
    configMode = digitalRead(CONFIG_INPUT_PIN);
    attachInterrupt(digitalPinToInterrupt(CONFIG_INPUT_PIN), &Network::setAP, CHANGE);
}

Network &Network::getInstance(ConfigData &configData)
{
    if (!instance)
    {
        instance = new Network(configData);
    }
    return *instance;
}

bool Network::getConfigMode()
{
    return configMode;
}

void Network::APMode()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(configData.apSSID, configData.apPassword, 1, false, MAX_CONNECTION);
    server.begin();
    int numDevices = WiFi.softAPgetStationNum();
    DEBUG_MODE_PRINT_VALUES("AP IP address: ", WiFi.softAPIP(), ", Number of connected devices: ", numDevices);

    WiFiClient client;
    // DEBUG_MODE_SERIAL_PRINT("waiting to client ");
    while (!(client = server.accept()))
    {
        if (!configMode)
        {
            connectToWifi();
            return;
        }
        delay(100);
    }

    char buff[BUFF_MAX_LEN];
    uint8_t buffLen = 0;

    while (configMode)
    {
        if (client.available() && buffLen < BUFF_MAX_LEN)
        {
            char c = client.read();

            if (c == '\n')
            {

#ifdef DEBUG_MODE
                Serial.print("[config] receivedData=|");
                for (int i = 0; i < buffLen; i++)
                {
                    Serial.print(buff[i]);
                }
                Serial.println("|");
#endif
                buff[buffLen++] = 0;
                configData.updateConfig((ConfigData::CONFIG_DATA_TYPE)(buff[0] - '0'), buff + 1, buffLen - 1);
                buffLen = 0;
            }
            else
            {
                buff[buffLen++] = c;
            }
        }
    }

    DEBUG_MODE_PRINT_VALUES("[config] AP mode shut down, pin input=", digitalRead(CONFIG_INPUT_PIN), ", client connected=", client.connected());

    client.stop();
    WiFi.softAPdisconnect();
}

void Network::connectToWifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(configData.wifiSSID, configData.wifiPassword);
    DEBUG_MODE_PRINT_VALUES("Connecting to ", configData.wifiSSID);
    DEBUG_MODE_PRINT_NAMES_VALUES(configData.wifiSSID, configData.wifiPassword);
    while (!configMode && WiFi.status() != WL_CONNECTED)
    {
        DEBUG_MODE_SERIAL_PRINT(".");
        delay(300);
    }
    DEBUG_MODE_SERIAL_PRINTLN(" Connected!");
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);

    DEBUG_MODE_PRINT_VALUES("IP address for network ", configData.wifiSSID, ": ", WiFi.localIP());
}

void IRAM_ATTR Network::setAP()
{
    // Network *network = static_cast<Network *>(instance);
    instance->configMode = digitalRead(CONFIG_INPUT_PIN);
}