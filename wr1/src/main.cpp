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
    digitalWrite(LED,LOW);
    for (size_t i = 0; i < results.getCount(); i++)
    {
        BLEAdvertisedDevice device = results.getDevice(i);

        if (!strcmp(device.getServiceDataUUID().toString().c_str(), "9f46b94c-9574-4f6c-bd1b-ddc3a7a83a43")){
            digitalWrite(LED, HIGH);
        }
        //Serial.printf("%i %s %s\n", device.getRSSI(),device.getName().c_str(), device.getServiceUUID().toString().c_str());
    }
    //digitalWrite(LED, (best>CUTOFF) ? HIGH : LOW);

  // put your main code here, to run repeatedly:
}