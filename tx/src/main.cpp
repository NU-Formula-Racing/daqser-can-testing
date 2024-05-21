#include <Arduino.h>
// #include <daqser.hpp>
#include <daqser_can_test.hpp>
#include <virtualTimer.h>
#include <CAN.h>

#define VERSION_ARGS(major, minor, patch) major, minor, patch

#define SCHEMA_NAME "test_schema_v1.0.0.drive"
#define SCHEMA_VERSION VERSION_ARGS(1, 0, 0)

// Listen to boards
// #define RX_BMS
// #define RX_IMD

VirtualTimerGroup timerGroup;
// Function to record and send data
// Called every 100ms
void recordData()
{
  std::cout << "Recording data" << std::endl;
  daqser::sendSignals();
  daqser::g_canBus.Tick();
}

void setup()
{
  Serial.begin(9600);
  daqser::g_canBus.Initialize(ICAN::BaudRate::kBaud1M);
  // Initialize the timer group
  daqser::g_timerGroup.AddTimer(100, recordData);
}

void loop()
{
  daqser::g_timerGroup.Tick(millis());
}