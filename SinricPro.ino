
bool onPowerState1(const String &deviceId, bool &state) {
 // Serial.printf("Device 1 turned %s\r\n", state?"on":"off");
  sw0 = state;
  EEPROM.write(0,sw0);
  EEPROM.commit();
  digitalWrite(relay0, sw0? LOW:HIGH);
  return true; // request handled properly
}

bool onPowerState2(const String &deviceId, bool &state) {
 // Serial.printf("Device 2 turned %s\r\n", state?"on":"off");
  sw1 = state;
  EEPROM.write(1,sw1);
  EEPROM.commit();
  digitalWrite(relay1, sw1? LOW:HIGH);
  return true; // request handled properly
}

bool onPowerState3(const String &deviceId, bool &state) {
 // Serial.printf("Device 3 turned %s\r\n", state?"on":"off");
  sw2 = state;
  EEPROM.write(2,sw2);
  EEPROM.commit();
  digitalWrite(relay2, sw2? LOW:HIGH);
  return true; // request handled properly
}

// setup function for SinricPro
void setupSinricPro() {
  // add devices and callbacks to SinricPro
  SinricProSwitch& mySwitch1 = SinricPro[SWITCH_ID_1];
  mySwitch1.onPowerState(onPowerState1);

  SinricProSwitch& mySwitch2 = SinricPro[SWITCH_ID_2];
  mySwitch2.onPowerState(onPowerState2);

  SinricProSwitch& mySwitch3 = SinricPro[SWITCH_ID_3];
  mySwitch3.onPowerState(onPowerState3);

  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

