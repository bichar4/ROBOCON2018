

#include "Sensor.h"
#include "Bot.h"
#include "Setup.h"

Bot bot;
void setup() {

//parameter is in setup header.
Initializer::initializePins();
bot.initializeBotSensor();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
