void HalGPIO::update() {
  _injectedWasPressed = 0;
  inputMgr.update();
  const bool connected = isUsbConnected();
  usbStateChanged = (connected != lastUsbConnected);
  lastUsbConnected = connected;
}

bool HalGPIO::wasUsbStateChanged() const { return usbStateChanged; }

bool HalGPIO::isPressed(uint8_t buttonIndex) const { return inputMgr.isPressed(buttonIndex); }

bool HalGPIO::wasPressed(uint8_t buttonIndex) const {
  if (buttonIndex < 8 && (_injectedWasPressed & (1u << buttonIndex))) return true;
  return inputMgr.wasPressed(buttonIndex);
}

bool HalGPIO::wasAnyPressed() const {
  if (_injectedWasPressed != 0) return true;
  return inputMgr.wasAnyPressed();
}

bool HalGPIO::wasReleased(uint8_t buttonIndex) const { return inputMgr.wasReleased(buttonIndex); }

bool HalGPIO::wasAnyReleased() const { return inputMgr.wasAnyReleased(); }

unsigned long HalGPIO::getHeldTime() const { return inputMgr.getHeldTime(); }

void HalGPIO::injectButton(uint8_t buttonIndex) {
  if (buttonIndex < 8) _injectedWasPressed |= (1u << buttonIndex);
}
