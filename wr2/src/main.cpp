#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "9f46b94c-9574-4f6c-bd1b-ddc3a7a83a43"
#define CHARACTERISTIC_UUID "afe8ef56-902f-4b38-a6a2-0eade0aca572"

void setup() {
  Serial.begin(115200);

  BLEDevice::init("MyESP32");
 esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P9); 
 esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9);
 esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_SCAN ,ESP_PWR_LVL_P9);


  Serial.println("Power Settings: (ADV,SCAN,DEFAULT)");         //all should show index7, aka +9dbm
  Serial.println(esp_ble_tx_power_get(ESP_BLE_PWR_TYPE_ADV));
  Serial.println(esp_ble_tx_power_get(ESP_BLE_PWR_TYPE_SCAN));
  Serial.println(esp_ble_tx_power_get(ESP_BLE_PWR_TYPE_DEFAULT));
  
  BLEServer *pServer = BLEDevice::createServer();
  pServer->getAdvertising()->setScanFilter(1,0);
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  BLEDevice::startAdvertising();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}