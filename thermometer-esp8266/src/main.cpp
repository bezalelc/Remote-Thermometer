#include <Arduino.h>
#include "network.hpp"
#include "debugUtils.hpp"
#include "ntc.hpp"

// delay for update firebase
#define DELAY 5000U
#define FIREBASE_START_TIME_PATH "startTime/"

Network *network;

void setup()
{
  DEBUG_MODE_SERIAL_BEGIN;
  network = new Network();
  // update start time
  network->updateTime(FIREBASE_START_TIME_PATH, millis());
}

void loop()
{
  // Send new readings to database
  delay(DELAY);
  network->updateTemperature(Ntc::readTemperature(), millis());
}