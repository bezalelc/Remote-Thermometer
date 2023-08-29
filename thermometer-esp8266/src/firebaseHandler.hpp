#ifndef FIREBASE_HANDLER_HPP
#define FIREBASE_HANDLER_HPP

#include <Firebase_ESP_Client.h>
#include "configData.hpp"

class FirebaseHandler
{
public:
    static FirebaseHandler &getInstance(ConfigData &configData);

    void begin();

    void updateTemperature(float temperature, unsigned long time);

    void updateTime(const char *timePath, unsigned long time);

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