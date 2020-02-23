/*
 *  hc06.ino
 */

#include <SoftwareSerial.h>

SoftwareSerial hc06(2,3);

String cmd="";
float sensor_val=0;

void setup() {
    //Initialize Serial Monitor
    Serial.begin(9600);
    //Initialize Bluetooth Serial Port
    hc06.begin(9600);
}

void loop() {
    //Read data from HC06
    while(hc06.available()>0) {
        cmd+=(char)hc06.read();
    }
    //Select function with cmd
    if(cmd!="") {
        Serial.print("Command recieved : ");
        Serial.println(cmd);
    // We expect ON or OFF from bluetooth
        if(cmd=="ON") {
            Serial.println("Function is on");
        } else if(cmd=="OFF") {
            Serial.println("Function is off");
        } else {
            Serial.println("Function is off by default");
        }
        cmd=""; //reset cmd
    }
    // Simulate sensor measurement
    sensor_val=(float)random(256); // random number between 0 and 255

    //Write sensor data to HC06
    hc06.print(sensor_val);
    delay(100);
}

/* EOF */
