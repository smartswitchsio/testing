
void onRequest(AsyncWebServerRequest *request){
    request->send(404);
    //request->send(404, "text/plain", "Not found");
}

void onBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
 //Handle body
}

void onUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
  //Handle upload

}

//void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
 void ICACHE_FLASH_ATTR onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
 {
  //Handle WebSocket event, onEvent
   if(type == WS_EVT_CONNECT){
  
   // Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
  
    //client->printf("Hello Client %u :)", client->id());
    //client->ping();
   // sendclk.attach(1,senddtime);
   dtdisplay = true;
  } else if(type == WS_EVT_DISCONNECT){
    
    //Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
   
    dtdisplay = false;
  } else if(type == WS_EVT_ERROR){
 
   // Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
 
  } else if(type == WS_EVT_PONG){
  
   // Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");

  } else if(type == WS_EVT_DATA){
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    String msg = "";
    if(info->final && info->index == 0 && info->len == len){
      //the whole message is in a single frame and we got all of it's data
    
     // Serial.printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT)?"text":"binary", info->len);

      if(info->opcode == WS_TEXT){
        for(size_t i=0; i < info->len; i++) {
          msg += (char) data[i];
        }
      } else {
        char buff[3];
        for(size_t i=0; i < info->len; i++) {
          sprintf(buff, "%02x ", (uint8_t) data[i]);
          msg += buff ;
        }
      }
    
      //Serial.printf("%s\n",msg.c_str());
      
      splitdata(msg.c_str(),client);
      
     }
  }
}


void startserver(){
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

    server.on("/icomoon.woff", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "font/woff", icomoon_woff_gz, icomoon_woff_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  
    server.on("/ediys.min.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/css", ediys_min_css_gz, ediys_min_css_gz_len);//SIZE
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  
  server.on("/ediys.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/javascript", ediys_min_js_gz, ediys_min_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  
  server.on("/server.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/javascript", server_js_gz, server_js_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html_gz, index_html_gz_len);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

 server.onNotFound(onRequest);
 server.onFileUpload(onUpload);
 server.onRequestBody(onBody);

 MDNS.begin(hostName);
 server.begin();
 MDNS.addService("http", "tcp", 80);
}
