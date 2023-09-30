#ifndef FIREBASE_HANDLER_HPP
#define FIREBASE_HANDLER_HPP

#include <Firebase_ESP_Client.h>
#include <ArduinoJson.h>
#include "configData.hpp"

#define FIREBASE_PROB_PATH "/prob"
#define FIREBASE_START_TIME_PATH "startTime/"

class FirebaseHandler
{
public:
    static FirebaseHandler &getInstance(ConfigData &configData);

    void begin();

    bool update(StaticJsonDocument<512> &doc) const;
    // bool updateTemperature(uint8 probId, float temperature) const;
    // bool updateTime(uint8 probId, unsigned long time) const;

    void updateTemperature(uint8 probId, float temperature, unsigned long time);

    void updateTime(const char *probTimePath, unsigned long time);

    // void updateTemperature(float temperature, unsigned long time)
    // {
    //     for (uint i = 0; i < 4; i++)
    //     {
    //         if (!Firebase.ready())
    //         {
    //             // DEBUG_MODE_PRINT_VALUES("Firebase.ready()=false");
    //             return;
    //         }

    //         if (Firebase.RTDB.setFloat(&firebaseData, databasePath.c_str(), temperature))
    //         {
    //             // DEBUG_MODE_PRINT_VALUES("Writing value: ", temperature, " TYPE: " + firebaseData.dataType() + " on the following path: ", databasePath, ", PASSED");
    //         }
    //         else
    //         {
    //             // DEBUG_MODE_PRINT_VALUES(databasePath, "FAILED: " + firebaseData.errorReason());
    //         }
    //         // updateTime(FIREBASE_CURRENT_TIME_PATH, time);
    //     }
    // }

private:
    FirebaseData firebaseData;
    FirebaseAuth firebaseAuth;
    FirebaseConfig firebaseConfig;
    String databasePath;
    const ConfigData &configData;
    static FirebaseHandler *instance;

    FirebaseHandler(const ConfigData &configData);

    // Private copy constructor and assignment operator to prevent copying
    FirebaseHandler(const FirebaseHandler &) = delete;
    FirebaseHandler &operator=(const FirebaseHandler &) = delete;
};

#endif //  FIREBASE_HANDLER_HPP