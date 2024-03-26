#include <Arduino.h>
#include <WiFi.h>

#include <OneWire.h>
#include <DallasTemperature.h>


#include <Firebase_ESP_Client.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

#define WIFI_SSID "Ali"
#define WIFI_PASSWORD "16385245"
#define SENSOR_PIN 18 
// Insert Firebase project API Key
#define API_KEY "AIzaSyCeVkSnOVDvCdxP49_FIJHph3IbvELYm2s"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://coba-17953-default-rtdb.firebaseio.com/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

//unsigned long sendDataPrevMillis = 0;
//int count = 0;
bool signupOK = false;

OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);

int tempC;

void setup() {
  Serial.begin(9600);
  DS18B20.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}



void loop() {
    DS18B20.requestTemperatures();
    tempC = DS18B20.getTempCByIndex(0);


    if (Firebase.ready() && signupOK ) {
    
      if (Firebase.RTDB.setInt(&fbdo, "WQMS/temperature",tempC)){
  //      Serial.println("PASSED");
         Serial.print("temperature : ");
         Serial.println(tempC);
      }
  }
    delay(1000);

}
