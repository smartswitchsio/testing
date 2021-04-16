/*
Memory Locations
Max address 512
Switch status 0,1,2,3,4,5

For https update 290
*/

void loadeeprom(){
sw0 = EEPROM.read(0);
sw1 = EEPROM.read(1);
sw2 = EEPROM.read(2);


digitalWrite(relay0, sw0 ? HIGH : LOW);
digitalWrite(relay1, sw1 ? HIGH : LOW);
digitalWrite(relay2, sw2 ? HIGH : LOW);

const size_t capacity = JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(2) + 50; // + 50
DynamicJsonDocument doc(capacity);

doc["id"] = "status";

JsonArray swsts = doc.createNestedArray("swsts");
swsts.add(String(sw0));
swsts.add(String(sw1));
swsts.add(String(sw2));
String data;
serializeJson(doc, data);
ws.textAll(data);
//Serial.print(data);
}

void relaysts(const char* sw){ //Send & Store switch status

if (strcmp(sw, "on0")  == 0) {
sw0 = 1;
EEPROM.write(0,sw0);
digitalWrite(relay0, sw0 ? HIGH : LOW);
}
else if (strcmp(sw, "off0")  == 0) {
sw0 = 0;
EEPROM.write(0,sw0);
digitalWrite(relay0, sw0 ? HIGH : LOW);
}

if (strcmp(sw, "on1")  == 0) {
sw1 = 1;
EEPROM.write(1,sw1);
digitalWrite(relay1, sw1 ? HIGH : LOW);
}
else if (strcmp(sw, "off1")  == 0) {
sw1 = 0;
EEPROM.write(1,sw1);
digitalWrite(relay1, sw1 ? HIGH : LOW);
}

if (strcmp(sw, "on2")  == 0) {
sw2 = 1;
EEPROM.write(2,sw2);
digitalWrite(relay2, sw2 ? HIGH : LOW);
}
else if (strcmp(sw, "off2")  == 0) {
sw2 = 0;
EEPROM.write(2,sw2);
digitalWrite(relay2, sw2 ? HIGH : LOW);
}

EEPROM.commit();
loadeeprom();
}
