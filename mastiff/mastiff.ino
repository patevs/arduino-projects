/*
 *  mastiff.ino
 */

// LIBRARIES //

#include <SoftwareSerial.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// CONSTANTS //

// Digital pin connected to the DHT sensor
#define DHTPIN 13

// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE)

SoftwareSerial hc06(2,3);

uint32_t delayMS;

void setup(void) {
    //Initialize Serial Monitor
    Serial.begin(9600);
    // Serial.println("ENTER AT Commands:");
    //Initialize Bluetooth Serial Port
    hc06.begin(9600);
    // Initialize dht sensor
    dht.begin();
    Serial.println("");
    Serial.println(F(" DHT11 Humidity & Temperature Sensor"));
    sensor_t sensor;
    // Print temperature sensor details
    dht.temperature().getSensor(&sensor);
    Serial.println(F(" -----------------------------------"));
    Serial.println(F(" Temperature Sensor"));
    Serial.print  (F("  Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
    Serial.print  (F("  Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
    Serial.print  (F("  Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
    Serial.println(F(" -----------------------------------"));
    // Print humidity sensor details.
    dht.humidity().getSensor(&sensor);
    Serial.println(F(" Humidity Sensor"));
    Serial.print  (F("  Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
    Serial.print  (F("  Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
    Serial.print  (F("  Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
    Serial.println(F(" -----------------------------------"));
    // Set delay between sensor readings based on sensor details.
    delayMS = sensor.min_delay / 1000;
}

void loop(void) {
    // Delay between measurements.
    delay(delayMS);

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
