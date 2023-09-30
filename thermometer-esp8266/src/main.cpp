#include <Arduino.h>

#include "debugUtils.hpp"
#include "thermistorAdapter.hpp"
#include "configData.hpp"
#include "network.hpp"
#include "firebaseHandler.hpp"

// delay for update firebase
#define DELAY 3000U
#define PROBS_NUM 4

void restartConnection();

ConfigData configData;
Network *network;
FirebaseHandler *firebaseHandler;
ThermistorAdapter *thermistorAdapter;

void setup()
{
  DEBUG_MODE_SERIAL_BEGIN;

  network = &Network::getInstance(configData);
  firebaseHandler = &FirebaseHandler::getInstance(configData);
  thermistorAdapter = &ThermistorAdapter::getInstance();
  if (!network->getConfigMode())
  {
    restartConnection();
  }

  // update start time
  String tmp = "";
  for (uint8 probId = 0; probId < PROBS_NUM; probId++)
  {
    firebaseHandler->updateTime((tmp + FIREBASE_PROB_PATH + (probId + 1) + "/" + FIREBASE_START_TIME_PATH).c_str(), millis());
  }
}

void loop()
{
  if (network->getConfigMode())
  {
    network->APMode();
    restartConnection();
  }
  else
  {
    for (uint8 probId = 0; probId < PROBS_NUM; probId++)
    {
      firebaseHandler->updateTemperature(probId, thermistorAdapter->readTemperature(probId), millis());
    }
  }

  DEBUG_MODE_PRINT_MEMORY_USAGE;
  delay(DELAY);
}

void restartConnection()
{
  network->connectToWifi();
  firebaseHandler->begin();
}