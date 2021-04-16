void switchin(){
if(acs0 != digitalRead(buttonPin0)){
digitalWrite(relay0, acs0 ? HIGH : LOW);
acs0 = digitalRead(buttonPin0);
sw0 = !acs0;
EEPROM.write(0,sw0);
EEPROM.commit();
loadeeprom();
}
if(acs1 != digitalRead(buttonPin1)){
digitalWrite(relay1, acs1 ? HIGH : LOW);
acs1 = digitalRead(buttonPin1);
sw1 = !acs1;
EEPROM.write(1,sw1);
EEPROM.commit();
loadeeprom();
}
if(acs2 != digitalRead(buttonPin2)){
digitalWrite(relay2, acs2 ? HIGH : LOW);
acs2 = digitalRead(buttonPin2);
sw2 = !acs2;
EEPROM.write(2,sw2);
EEPROM.commit();
loadeeprom();
}
}
