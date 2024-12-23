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

    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P9); 
    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9);
    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_SCAN ,ESP_PWR_LVL_P9);


  Serial.println("Power Settings: (ADV,SCAN,DEFAULT)");         //all should show index7, aka +9dbm
  Serial.println(esp_ble_tx_power_get(ESP_BLE_PWR_TYPE_ADV));
  Serial.println(esp_ble_tx_power_get(ESP_BLE_PWR_TYPE_SCAN));
  Serial.println(esp_ble_tx_power_get(ESP_BLE_PWR_TYPE_DEFAULT));
}

void loop() {
    BLEScan* scan = BLEDevice::getScan();
    scan->setActiveScan(true);
    BLEScanResults results = scan->start(1);
    bool other_esp = false;
    for (size_t i = 0; i < results.getCount(); i++)
    {   
        BLEAdvertisedDevice device = results.getDevice(i);

        if (!strcmp(device.getServiceUUID().toString().c_str(), "9f46b94c-9574-4f6c-bd1b-ddc3a7a83a43")){
            Serial.printf("Signal strength: %i\n", 100+device.getRSSI());
            other_esp = true;
        }
        //Serial.printf("%i %s %s\n", device.getRSSI(),device.getName().c_str(), device.getServiceUUID().toString().c_str());
    }
    digitalWrite(LED,(other_esp) ? HIGH : LOW);
    //digitalWrite(LED, (best>CUTOFF) ? HIGH : LOW);

  // put your main code here, to run repeatedly:
}