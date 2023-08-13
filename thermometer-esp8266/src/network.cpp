#include <ESP8266WiFi.h>
// Provide the token generation process info.
#include "addons/TokenHelper.h"
#include "network.hpp"
#include "config.h"
#include "debugUtils.hpp"

// firebase project API Key
#define FIREBASE_MAIN_PATH "/UsersData/"
#define FIREBASE_PROB1_PATH "/prob1/"
#define FIREBASE_TEMPERATURE_PATH "temperature/"
#define FIREBASE_CURRENT_TIME_PATH "currentTime/"

Network::Network()
{
    initWifi();
    initFirebase();
    setFirebasePath();
}

void Network::initFirebase()
{
    firebaseConfig.api_key = FIREBASE_API_KEY;
    firebaseConfig.database_url = FIREBASE_DATABASE_URL;
    firebaseAuth.user.email = USER_EMAIL;
    firebaseAuth.user.password = USER_PASSWORD;

    // Assign the RTDB URL (required)
    Firebase.reconnectWiFi(true);
    firebaseData.setResponseSize(4096);

    // Assign the callback function for the long running token generation task */
    firebaseConfig.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    // Assign the maximum retry of token generation
    firebaseConfig.max_token_generation_retry = 5;

    // Initialize the library with the Firebase authen and config
    Firebase.begin(&firebaseConfig, &firebaseAuth);
}

void Network::initWifi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    DEBUG_MODE_SERIAL_PRINT("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED)
    {
        DEBUG_MODE_SERIAL_PRINT('.');
        delay(1000);
    }
    DEBUG_MODE_SERIAL_PRINTLN(WiFi.localIP());
    DEBUG_MODE_SERIAL_PRINTLN();
}

void Network::setFirebasePath()
{
    // Getting the user UID might take a few seconds
    DEBUG_MODE_SERIAL_PRINTLN("Getting User UID");
    while ((firebaseAuth.token.uid) == "")
    {
        DEBUG_MODE_SERIAL_PRINT('.');
        delay(1000);
    }
    // Print user UID
    String userId = firebaseAuth.token.uid.c_str();
    DEBUG_MODE_SERIAL_PRINT("User UID: ");
    DEBUG_MODE_SERIAL_PRINTLN(userId);

    // Update database path
    databasePath = FIREBASE_MAIN_PATH + userId + FIREBASE_PROB1_PATH;
}

void Network::updateTemperature(float temperature, unsigned long time)
{
    if (!Firebase.ready())
    {
        return;
    }

    if (Firebase.RTDB.setFloat(&firebaseData, (databasePath + FIREBASE_TEMPERATURE_PATH).c_str(), temperature))
    {
        DEBUG_MODE_SERIAL_PRINT("Writing value: ");
        DEBUG_MODE_SERIAL_PRINT(temperature);
        DEBUG_MODE_SERIAL_PRINT(" TYPE: " + firebaseData.dataType() + " on the following path: ");
        DEBUG_MODE_SERIAL_PRINT(databasePath);
        DEBUG_MODE_SERIAL_PRINTLN(", PASSED");
    }
    else
    {
        DEBUG_MODE_SERIAL_PRINTLN(databasePath);
        DEBUG_MODE_SERIAL_PRINTLN("FAILED: " + firebaseData.errorReason());
    }
    updateTime(FIREBASE_CURRENT_TIME_PATH, time);
}

void Network::updateTime(const char *timePath, unsigned long time)
{
    if (Firebase.RTDB.setFloat(&firebaseData, (databasePath + timePath).c_str(), time))
    {
        DEBUG_MODE_SERIAL_PRINT("Writing value: ");
        DEBUG_MODE_SERIAL_PRINT(time);
        DEBUG_MODE_SERIAL_PRINT(" TYPE: " + firebaseData.dataType() + " on the following path: ");
        DEBUG_MODE_SERIAL_PRINT(databasePath);
        DEBUG_MODE_SERIAL_PRINTLN(", PASSED");
    }
    else
    {
        DEBUG_MODE_SERIAL_PRINTLN(databasePath);
        DEBUG_MODE_SERIAL_PRINTLN("FAILED: " + firebaseData.errorReason());
    }
}
