#pragma once

// BleManager.h
// Thin wrapper um BluetoothHIDManager für CrossInk main.cpp Integration.
// Nur aktiv wenn ENABLE_BLE_HID definiert ist (ble build environment).

#ifdef ENABLE_BLE_HID

#include "hal/BluetoothHIDManager.h"
#include <HalGPIO.h>

namespace BleManager {

// Muss einmal in setup() aufgerufen werden, nach Storage.begin()
inline void begin() {
  auto& ble = BluetoothHIDManager::getInstance();
  ble.loadState();

  // Button-Injector: simuliert physische Tastendrücke über HalGPIO
  ble.setButtonInjector([](uint8_t buttonIndex) {
    gpio.injectButton(buttonIndex);
  });
}

// Muss jeden loop()-Durchlauf aufgerufen werden
inline void update(bool userInputDetected) {
  auto& ble = BluetoothHIDManager::getInstance();
  if (!ble.isEnabled()) return;
  ble.updateActivity();
  ble.checkAutoReconnect(userInputDetected);
}

// Gibt true zurück wenn BLE gerade aktiv ist (verhindert Auto-Sleep)
inline bool hasRecentActivity() {
  return BluetoothHIDManager::getInstance().hasRecentActivity();
}

}  // namespace BleManager

#endif  // ENABLE_BLE_HID
