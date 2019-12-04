#include "TestConstants.h"

void setup()
{
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU9250 connection successful" : "MPU9250 connection failed");
    filter.begin(25);
    
    delay(1000);
    Serial.println("     ");
}

void loop()
{
  setAngles();

  Serial.print(" Pitch: ");
  Serial.print(pitch);
  Serial.print(" Roll ");
  Serial.println(roll);
  }
