/*
 *  mastiff.ino
 */

// Included libraries
#include <SoftwareSerial.h>

SoftwareSerial hc06(2,3);

// Constants
// #define DELAY 1000 // Delay between two measurements in ms
// Parameters
// const int sensorPin = A0; // Pin connected to sensor
// Variables
// float voltage, temperature;

void setup(void) {
    //Initialize Serial Monitor
    Serial.begin(9600);
    Serial.println("ENTER AT Commands:");
    //Initialize Bluetooth Serial Port
    hc06.begin(9600);
}

void loop(void) {
    // voltage= analogRead(sensorPin) * (5.0 / 1023.0); // Convert digital value to voltage
    // temperature=100*voltage; // conversion from V to °C

    // Serial.print("Sensor reading = ");
    // Serial.println(temperature); // the temperature reading
    // Send voltage and temperature value to app
    // HC06.print(voltage);
    // HC06.print("x");
    // HC06.print(temperature);

    // delay(DELAY);

    //Write data from HC06 to Serial Monitor
    if (hc06.available()) {
        Serial.write(hc06.read());
    }

    //Write from Serial Monitor to HC06
    if (Serial.available()) {
        hc06.write(Serial.read());
    }
}

/* EOF */
