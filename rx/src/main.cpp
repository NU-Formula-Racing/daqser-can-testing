#include <Arduino.h>
#include <daqser.hpp>
#include <daqser_can.hpp>
#include <virtualTimer.h>

#define VERSION_ARGS(major, minor, patch) major, minor, patch

#define SCHEMA_NAME "esp32dev_test"
#define SCHEMA_VERSION VERSION_ARGS(1, 0, 0)

VirtualTimerGroup timerGroup;
// Function to record and send data
// Called every 100ms
void recordData()
{
  //  Prepare data from the CAN bus for serialization
  daqser::updateSignals();
  // Serialize the data, and get the raw bytes
  std::vector<std::uint8_t> byteData = daqser::serializeFrame();
  // send the data over lora or something
  // send(byteData);
  // print out the bytes
  std::cout << "Data(length:" << byteData.size() << "): ";
  for (std::uint8_t byte : byteData)
  {
    Serial.print(byte, HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void setup()
{
  Serial.begin(9600);
  // Initialize the daqser library
  daqser::initialize();
  // Tell daqser what schema we are using to serialize the data
  daqser::setSchema(SCHEMA_NAME, SCHEMA_VERSION);
  // Tell daqser to record/send data from these boards
  timerGroup.AddTimer(100, recordData);
}

void loop()
{
  timerGroup.Tick(millis());
}