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

void led_blink(void* args){
    pinMode(LED,HIGH);
    vTaskDelay(500/portTICK_PERIOD_MS);
    pinMode(LED,LOW);

}

void loop() {
    BLEScan* scan = BLEDevice::getScan();
    scan->setActiveScan(true);
    BLEScanResults results = scan->start(1);
    int count = results.getCount();
    if (count == 0){
        Serial.println("No devices found.");
    }
    for (size_t i = 0; i < count; i++)
    {
        BLEAdvertisedDevice device = results.getDevice(i);

        Serial.printf("%i %s\n", device.getRSSI(),device.getName());
        xTaskCreate(led_blink,"led blink", 512,NULL,1,NULL);

    }

  // put your main code here, to run repeatedly:
}