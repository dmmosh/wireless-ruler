#include <Arduino.h>
#include "BLEScan.h"
#include "BLEAdvertisedDevice.h"
#include "BLEDevice.h"

#define LED 2
#define CUTOFF -60


void setup() {
    pinMode(LED,OUTPUT);
    BLEDevice::init("");
}

void loop() {
    BLEScan* scan = BLEDevice::getScan();
    scan->setActiveScan(true);
    BLEScanResults results = scan->start(1);
    int best = CUTOFF;
    for (size_t i = 0; i < results.getCount(); i++)
    {
        BLEAdvertisedDevice device = results.getDevice(i);

        int rssi = device.getRSSI();
        if(rssi > best){
            best = rssi; 
        }
    }
    digitalWrite(LED, (best>CUTOFF) ? HIGH : LOW);
    Serial.print("cdsnljdksjckl");

  // put your main code here, to run repeatedly:
}