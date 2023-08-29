#include "firebaseHandler.hpp"
// Provide the token generation process info.
#include "addons/TokenHelper.h"
#include "config.h"
#include "debugUtils.hpp"
#include "network.hpp"

// firebase project API Key
#define FIREBASE_MAIN_PATH "/UsersData/"
#define FIREBASE_PROB1_PATH "/prob1/"
#define FIREBASE_TEMPERATURE_PATH "temperature/"
#define FIREBASE_CURRENT_TIME_PATH "currentTime/"

FirebaseHandler *FirebaseHandler::instance = nullptr;

FirebaseHandler::FirebaseHandler(const ConfigData &configData) : configData(configData)
{

    firebaseConfig.api_key = FIREBASE_API_KEY;
    firebaseConfig.database_url = FIREBASE_DATABASE_URL;

    // Assign the callback function for the long running token generation task */
    firebaseConfig.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    // Assign the maximum retry of token generation
    firebaseConfig.max_token_generation_retry = 5;
}

FirebaseHandler &FirebaseHandler::getInstance(ConfigData &configData)
{
    if (!instance)
    {
        instance = new FirebaseHandler(configData);
    }
    return *instance;
}

void FirebaseHandler::begin()
{
    firebaseAuth.user.email = &configData.getUsername();
    firebaseAuth.user.password = &configData.getUserPassword();

    Firebase.reconnectWiFi(true);
    firebaseData.setResponseSize(4096);

    // Initialize the library with the Firebase authen and config
    Firebase.begin(&firebaseConfig, &firebaseAuth);

    // Getting the user UID might take a few seconds
    DEBUG_MODE_SERIAL_PRINT("Getting User UID ");
    while (!Network::configMode && (firebaseAuth.token.uid) == "")
    {
        DEBUG_MODE_SERIAL_PRINT('.');
        delay(1000);
    }

    String userId = firebaseAuth.token.uid.c_str();
    // Update database path
    databasePath = FIREBASE_MAIN_PATH + userId + FIREBASE_PROB1_PATH;
}

void FirebaseHandler::updateTemperature(float temperature, unsigned long time)
{
    if (!Firebase.ready())
    {
        return;
    }

    if (Firebase.RTDB.setFloat(&firebaseData, (databasePath + FIREBASE_TEMPERATURE_PATH).c_str(), temperature))
    {
        DEBUG_MODE_PRINT_VALUES("Writing value: ", temperature, " TYPE: " + firebaseData.dataType() + " on the following path: ", databasePath, ", PASSED");
    }
    else
    {
        DEBUG_MODE_PRINT_VALUES(databasePath, "FAILED: " + firebaseData.errorReason());
    }
    updateTime(FIREBASE_CURRENT_TIME_PATH, time);
}

void FirebaseHandler::updateTime(const char *timePath, unsigned long time)
{
    if (Firebase.RTDB.setFloat(&firebaseData, (databasePath + timePath).c_str(), time))
    {
        DEBUG_MODE_PRINT_VALUES("Writing value: ", time, " TYPE: ", firebaseData.dataType(), " on the following path: ", databasePath, ", PASSED");
    }
    else
    {
        DEBUG_MODE_PRINT_VALUES(databasePath, "FAILED: ", firebaseData.errorReason());
    }
}
