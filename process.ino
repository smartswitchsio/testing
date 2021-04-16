
void senddtime(){ //send live date & time if client is connected
    DateTime now = rtc.now();
    long de = now.unixtime();
const size_t capacity = JSON_OBJECT_SIZE(2) + 30; // + 30;
DynamicJsonDocument doc(capacity);
    doc["id"] = "clk";
    doc["tm"] = de;
    String date;
    serializeJson(doc, date);
    ws.textAll(date);
}

void ICACHE_FLASH_ATTR splitdata(String msg, AsyncWebSocketClient * client)
{
 // Serial.println(msg); //testing
  DynamicJsonDocument root(1024);
  auto error = deserializeJson(root, msg);
  if (error) {
   // Serial.print(F("deserializeJson() failed with code "));
   // Serial.println(error.c_str());
    return;
}

    const char* id = root["id"];
    if (strcmp(id, "connected")  == 0) 
    {//After cliend connected send status
    loadeeprom(); 
    }
else if (strcmp(id, "swsts")  == 0) 
    { //Send & Store switch status
    const char* sw = root["sw"];
    relaysts(sw);
    }
          
else{
    Serial.print("undefinded msg");
    Serial.print(msg);
    }
}
