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

DHT_Unified dht(DHTPIN, DHTTYPE);

SoftwareSerial hc06(2,3); // RX, TX

uint32_t delayMS;

void setup(void) {
    pinMode(13, OUTPUT); // for LED status
    //Initialize Serial Monitor
    Serial.begin(9600);
    // Serial.println("ENTER AT Commands:");

    //Initialize Bluetooth Serial Port
    hc06.begin(9600); // start the bluetooth uart at 9600 which is its default
    // wait for voltage to stabilize
    delay(200);
    // hc06.print("AT+NAMEHC-06"); // place your name in here to configure the bluetooth name.
                                   // will require reboot for settings to take affect.
    // wait for settings to take affect
    // delay(3000);

    // Initialize dht sensor
    dht.begin();
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

    // Get temperature event and print its value.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        Serial.println(F(" Error reading temperature!"));
    } else {
        // get temperature
        int temp = event.temperature;
        // print temp to serial out
        // Serial.print(F("  Temperature: "));
        // Serial.print(temp);
        // Serial.println(F("°C"));
        // send temp to hc06 sensor
        // hc06.print(temp);
        // hc06.write(temp);
        // Serial.write(hc06.read());
    }

    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
        Serial.println(F(" Error reading humidity!"));
    } else {
        // get humidity
        int humidity = event.relative_humidity;
        // print humidity to serial out
        /*
        Serial.print(F("  Humidity: "));
        Serial.print(humidity);
        Serial.println(F("%"));
        Serial.println("");
        */
    }

    // Write data from HC06 to Serial Monitor
    if (hc06.available()) {
        Serial.write(hc06.read());
    }

    // Write from Serial Monitor to HC06
    if (Serial.available()) {
        hc06.write("TEST!");
        hc06.write(Serial.read());
    }
}

/* EOF */
