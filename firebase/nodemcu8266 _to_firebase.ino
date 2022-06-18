// tweak to your taste 
//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
 


#define FIREBASE_HOST "emeter-afca8-default-rtdb.firebaseio.com" //replace with your URL Without http:// or https:// schemes
#define FIREBASE_AUTH "QANtx1aGg8IBwJxcVfGp9H18Axxxxxxxxxxxxxxx" ////replace with your authentication key
#define WIFI_SSID "Prumwire"         // change to your network name
#define WIFI_PASSWORD "22580540aaa"   // change to your network password

  #include <SoftwareSerial.h>
  
  
 SoftwareSerial serial1(D1,D2);//(RX, Tx) declare your serial pins on the node mcu
char c;
String datain;
int8_t indexOfA,indexOfB,indexOfC,indexOfD;  
String sdata1,sdata2, sdata3, sdata4;  
  
int light1 = D6;      // // Connect relays here.or you redefine your pins 
int light2 = D5;  
int socket = D7;  
 

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData light1Data;
FirebaseData light2Data;
FirebaseData socketData ;

 

 

void setup()
{

  Serial.begin(9600); //serial monitor
  serial1.begin(9600); //data transfer pins
  
  
 while (!Serial) continue;
  pinMode(socket ,OUTPUT);
    pinMode(light1 ,OUTPUT);
      pinMode(light2 ,OUTPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void sensorUpdate(){
 
 
 readata();
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h =  sdata1.toFloat() ; //power
  float t =  sdata2.toFloat(); //voltage
  float f =  sdata3.toFloat() ;// current
  float g =  sdata4.toFloat();// usage

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)|| isnan(g)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Power: "));
  Serial.print(h);
  Serial.print(F("Voltage: "));
  Serial.print(t);
  Serial.print(F("current: "));
  Serial.print(f);
  Serial.println(F("usage/hour:  "));
  Serial.print(g);

  if (Firebase.setFloat(firebaseData, "/eMeter/voltage", t))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  if (Firebase.setFloat(firebaseData, "/eMeter/power", h))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

 if (Firebase.setFloat(firebaseData, "/eMeter/current", f))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

 if (Firebase.setFloat(firebaseData, "/eMeter/usage",g))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
  
}

void loop() {
  
  sensorUpdate();
  
  
  if (Firebase.getString(light1Data, "/eMeter/light1")){
    Serial.println(light1Data.stringData());
    if (light1Data.stringData() == "1") {
    digitalWrite(light1, HIGH);
    }
  else if (light1Data.stringData() == "0"){
    digitalWrite(light1, LOW);
    }
  }
  
    if (Firebase.getString(light2Data, "/eMeter/light2")){
    Serial.println(light2Data.stringData());
    if (light2Data.stringData() == "1") {
    digitalWrite(light2, HIGH);
    }
  else if (light2Data.stringData() == "0"){
    digitalWrite(light2, LOW);
    }
  }
    if (Firebase.getString(socketData, "/eMeter/socket")){
    Serial.println(socketData.stringData());
    if (socketData.stringData() == "1") {
    digitalWrite(socket,LOW );
    }
  else if (socketData.stringData() == "0"){
    digitalWrite(socket,HIGH );
    }
  }
 
}
