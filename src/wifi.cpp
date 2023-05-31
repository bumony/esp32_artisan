#include <WiFi.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>


bool shouldSaveConfig;
void saveConfigCallback () {
  shouldSaveConfig = true;
}

class WIFI {
    public:
        WIFI(char *AP_SSID, char* AP_PASS){ 
            ap_ssid = AP_SSID;
            ap_pass = AP_PASS;
        } 
        void init();
        void reset();
        void check();
    private:
        void readConfig();
        char *ap_ssid;
        char* ap_pass;
};


void WIFI::init() {
  readConfig();
  
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  WiFiManager wm;
  shouldSaveConfig = false;
  wm.setSaveConfigCallback(saveConfigCallback);

  WiFiManagerParameter custom_mqttServer("mqttServer", "mqtt server", mqttServer, 40);
  WiFiManagerParameter custom_mqttPort("mqttPort", "mqtt port", mqttPort, 6);
  WiFiManagerParameter custom_mqttUserName("mqttUserName", "mqtt user name", mqttUserName, 32);
  WiFiManagerParameter custom_mqttPwd("mqttPwd", "mqtt password", mqttPwd, 32);
  WiFiManagerParameter custom_DeviceId("DeviceId", "Device ID", DeviceId, 32);
  
  wm.addParameter(&custom_mqttServer);
  wm.addParameter(&custom_mqttPort);
  wm.addParameter(&custom_mqttUserName);
  wm.addParameter(&custom_mqttPwd);
  wm.addParameter(&custom_DeviceId);
  

  bool res;
  screen.drawAPmode();
  wm.setConfigPortalTimeout(180);//seconds
  res = wm.autoConnect(ap_ssid,ap_pass); // password protected ap
  if(!res) {
      Serial.println("Failed to connect, restart");
      ESP.restart();
  } 
  else {
      //if you get here you have connected to the WiFi    
      Serial.println("connected...yeey :)");
      screen.drawText("WiFi connected");
  }

  //save the custom parameters to FS
  if (shouldSaveConfig) {
    DynamicJsonDocument doc(1024);
    
    doc["mqttServer"]   = custom_mqttServer.getValue();
    doc["mqttPort"]     = custom_mqttPort.getValue();
    doc["mqttUserName"] = custom_mqttUserName.getValue();
    doc["mqttPwd"]      = custom_mqttPwd.getValue();
    doc["DeviceId"]     = custom_DeviceId.getValue();

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }
    
    serializeJsonPretty(doc, Serial);
    serializeJson(doc, configFile);
    configFile.close();
    //end save
    shouldSaveConfig = false;
    readConfig();
  }  
}

void WIFI::readConfig(){
  //clean FS, for testing
  // SPIFFS.format();
  //read configuration from FS json
  Serial.println("mounting FS...");

  if (SPIFFS.begin(true)) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonDocument doc(1024);
     
        deserializeJson(doc, buf.get(), DeserializationOption::NestingLimit(20));
        serializeJsonPretty(doc, Serial);

        if (!doc.isNull()) {
          Serial.println("\nparsed json");

          if (doc.containsKey("mqttServer")){
            strcpy(mqttServer, doc["mqttServer"]);  
          }
          if (doc.containsKey("mqttPort")){
            strcpy(mqttPort, doc["mqttPort"]);
          }
          if (doc.containsKey("mqttUserName")){
            strcpy(mqttUserName, doc["mqttUserName"]);
          }
          if (doc.containsKey("mqttPwd")){
            strcpy(mqttPwd, doc["mqttPwd"]);
          }
          if (doc.containsKey("DeviceId")){
            strcpy(DeviceId, doc["DeviceId"]);
          }
        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read
}


void WIFI::check()
{
  static unsigned long samplingTime = millis();
  static int countdown=5;
  
  if(millis()-samplingTime > 5000)
  {
      samplingTime=millis();
      
      if(WiFi.status()!= WL_CONNECTED) {
        countdown--;
        if(countdown==0){
            Serial.println("Failed to reconnect");
            ESP.restart();
        }
      }else{
        countdown=5;
      }
  }
}
