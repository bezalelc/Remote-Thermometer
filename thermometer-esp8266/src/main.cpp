#include <Arduino.h>
#include "debugUtils.hpp"
#include "ntc.hpp"
#include "configData.hpp"
#include "network.hpp"
#include "firebaseHandler.hpp"

// delay for update firebase
#define DELAY 5000U
#define FIREBASE_START_TIME_PATH "startTime/"
#define PROPS_NUM 4

ConfigData configData;
Network *network;
FirebaseHandler *firebaseHandler;

void restartConnection()
{
  network->connectToWifi();
  firebaseHandler->begin();
}

void setup()
{
  DEBUG_MODE_SERIAL_BEGIN;
  // delay(1000);

  network = &Network::getInstance(configData);
  firebaseHandler = &FirebaseHandler::getInstance(configData);
  if (network->getConfigMode())
  {
    restartConnection();
  }

  // update start time
  firebaseHandler->updateTime(FIREBASE_START_TIME_PATH, millis());
}

void loop()
{
  // Serial.print()
  if (network->getConfigMode())
  {
    network->APMode();
    restartConnection();
  }
  else
  {
    // Send new readings to database
    firebaseHandler->updateTemperature(Ntc::readTemperature(), millis());
  }
  
  DEBUG_MODE_PRINT_MEMORY_USAGE;
  delay(2000);
}