#include "firebaseHandler.hpp"
// Provide the token generation process info.
#include "addons/TokenHelper.h"
#include "config.h"
#include "debugUtils.hpp"
#include "network.hpp"
// #include <Firebase_ESP_Client.h>

// firebase project API Key
#define FIREBASE_MAIN_PATH "/UsersData/"
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
    databasePath = FIREBASE_MAIN_PATH + userId + "/";
}

bool FirebaseHandler::update(StaticJsonDocument<512> &doc) const
{
    if (!Firebase.ready())
    {
        DEBUG_MODE_PRINT_VALUES("Firebase.ready()=false");
        return false;
    }

    // FirebaseJson json;
    // json.setDoubleDigits(3);
    // json.add("value", 9);

    // FirebaseJsonArray arr;
    // arr.setDoubleDigits(3);
    // arr.setJsonArrayData("[1,2,3]");
    // arr.toString(Serial, true);

    // String p = "/k/";
    // firebaseData.;
    // firebaseData.setJSON(json);
    // Firebase.RTDB.set(&firebaseData, p.c_str());
    // Firebase.RTDB.setJSON(&firebaseData, p.c_str(), &json);

    // Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&firebaseData, "/test/json", &json) ? "ok" : firebaseData.errorReason().c_str());

    return true;
}

// bool FirebaseHandler::updateTemperature(uint8 probId, float temperature) const
// {
//     if (!Firebase.ready())
//     {
//         DEBUG_MODE_PRINT_VALUES("Firebase.ready()=false");
//         return false;
//     }

//     if (Firebase.RTDB.setFloat(&firebaseData, (databasePath + probId + "/" + FIREBASE_TEMPERATURE_PATH).c_str(), temperature))
//     {
//         DEBUG_MODE_PRINT_VALUES("Writing value: ", temperature, " TYPE: " + firebaseData.dataType() + " on the following path: ", databasePath, ", PASSED");
//     }
//     else
//     {
//         DEBUG_MODE_PRINT_VALUES(databasePath, "FAILED: " + firebaseData.errorReason());
//     }
//     return true;
// }

void FirebaseHandler::updateTemperature(uint8 probId, float temperature, unsigned long time)
{

    if (!Firebase.ready())
    {
        DEBUG_MODE_PRINT_VALUES("Firebase.ready()=false");
        return;
    }

    if (Firebase.RTDB.setFloat(&firebaseData, (databasePath + FIREBASE_PROB_PATH + (probId + 1) + "/" + FIREBASE_TEMPERATURE_PATH).c_str(), temperature))
    {
        DEBUG_MODE_PRINT_VALUES("Writing value: ", temperature, " TYPE: " + firebaseData.dataType() + " on the following path: ", databasePath, ", PASSED");
    }
    else
    {
        DEBUG_MODE_PRINT_VALUES(databasePath, "FAILED: " + firebaseData.errorReason());
    }
    String tmp = "";
    updateTime((tmp + FIREBASE_PROB_PATH + (probId + 1) + "/" + FIREBASE_CURRENT_TIME_PATH).c_str(), time);
}

void FirebaseHandler::updateTime(const char *probTimePath, unsigned long time)
{
    if (Firebase.RTDB.setFloat(&firebaseData, (databasePath + probTimePath).c_str(), time))
    {
        DEBUG_MODE_PRINT_VALUES("Writing value: ", time, " TYPE: ", firebaseData.dataType(), " on the following path: ", databasePath, ", PASSED");
    }
    else
    {
        DEBUG_MODE_PRINT_VALUES(databasePath, "FAILED: ", firebaseData.errorReason());
    }
}
