/*
 *  example.ino
 */

// Included libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <LiquidCrystal.h>

// Digital pin connected to the DHT sensor
#define DHTPIN 13

// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

uint32_t delayMS;

void setup() {
    Serial.begin(9600);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    // lcd.print("hello, world!");
    // Initialize dht sensor.
    dht.begin();
    Serial.println("");
    Serial.println(F(" DHT11 Humidity & Temperature Sensor"));
    sensor_t sensor;
    // Print temperature sensor details.
    dht.temperature().getSensor(&sensor);
    Serial.println(F(" -----------------------------------"));
    Serial.println(F(" Temperature Sensor"));
    // Serial.print  (F("  Sensor Type: ")); Serial.println(sensor.name);
    // Serial.print  (F("  Driver Ver:  ")); Serial.println(sensor.version);
    // Serial.print  (F("  Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("  Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
    Serial.print  (F("  Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
    Serial.print  (F("  Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
    Serial.println(F(" -----------------------------------"));
    // Print humidity sensor details.
    dht.humidity().getSensor(&sensor);
    Serial.println(F(" Humidity Sensor"));
    // Serial.print  (F("  Sensor Type: ")); Serial.println(sensor.name);
    // Serial.print  (F("  Driver Ver:  ")); Serial.println(sensor.version);
    // Serial.print  (F("  Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("  Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
    Serial.print  (F("  Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
    Serial.print  (F("  Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
    Serial.println(F(" -----------------------------------"));
    // Set delay between sensor readings based on sensor details.
    delayMS = sensor.min_delay / 1000;
}

void loop() {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    // lcd.print(millis() / 1000);
    // Delay between measurements.
    delay(delayMS);
    // Get temperature event and print its value.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        Serial.println(F(" Error reading temperature!"));
    }
    else {
        lcd.print("Temp: ");
        lcd.print(event.temperature);
        lcd.print("C");

        Serial.print(F("  Temperature: "));
        Serial.print(event.temperature);
        Serial.println(F("°C"));
    }
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
        Serial.println(F(" Error reading humidity!"));
    }
    else {
        Serial.print(F("  Humidity: "));
        Serial.print(event.relative_humidity);
        Serial.println(F("%"));
        Serial.println("");
    }
}

/* EOF */
