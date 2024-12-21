#include <Arduino.h>
#include "BLEScan.h"
#include "BLEAdvertisedDevice.h"
#include "BLEDevice.h"

#define LED 2
#define CUTOFF -60


void setup() {
    Serial.begin(115200);
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
        Serial.printf("%i %s\n", device.getRSSI(),device.getName());
    }
    digitalWrite(LED, (best>CUTOFF) ? HIGH : LOW);

  // put your main code here, to run repeatedly:
}