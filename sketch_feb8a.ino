#include <WiFiNINA.h>

//librairie du kit
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;
char ssid[] = "TP-Link_F99E" ;
char pass[] = "05186150" ; 
IPAddress ipadd;

void printMacAddress(byte mac[]){
  for(int i=5; i>=0; i--){
    if(mac[i]<16){
      Serial.print("0");
    }
    Serial.print(mac[i],HEX);
    if(i>0){
      Serial.print(":");
    }
  }
  Serial.println();
}

void printCurrentNet(){
  Serial.print("SSID : ");
  Serial.println(WiFi.SSID());
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID : ");
  printMacAddress(bssid);
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

//methode ping 


// fonction initialisation
void ledFnct(){}
void setup() {
  carrier.begin();
  carrier.leds.setPixelColor(0,255,0,0);
  carrier.leds.setPixelColor(1,0,255,0);
  carrier.leds.setPixelColor(2,0,0,255);
  carrier.leds.setPixelColor(3,255,0,255);
  carrier.leds.setPixelColor(4,255,255,30);
  carrier.leds.show();
  // put your setup code here, to run once:
  //Serial.begin(9600);
  //while (!Serial){}
  //carrier.Buzzer.sound(500);
  // afficher l'ecran
  carrier.display.fillScreen(ST77XX_RED);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(2);
  carrier.display.setCursor(40,110);
  carrier.display.print("bienvenue");
  delay(2000);
  delay(2000);
  carrier.Buzzer.noSound();
  carrier.leds.setPixelColor(0,0,0,0);
  carrier.leds.setPixelColor(1,0,0,0);
  carrier.leds.setPixelColor(2,0,0,0);
  carrier.leds.setPixelColor(3,0,0,0);
  carrier.leds.setPixelColor(4,0,0,0);
  carrier.leds.show();
  Serial.println("fct setup terminé");




  delay(2000);

  ping();
  delay(2000);


  
}
void ping(){
  int pingResult = WiFi.ping("googlezzzzz.com");
  if(pingResult >=0){
    Serial.println("no rsp");
  }else{
    Serial.println("k");
  }
}

void loop() {

  float fTemp;
  float fHumdite;
  float fPressionAt;
  fTemp = carrier.Env.readTemperature();
  fHumdite = carrier.Env.readHumidity();
  fPressionAt = carrier.Pressure.readPressure()/100.0;
  int altitude = 294;

  fPressionAt += altitude / 0.8;

  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(2);
  carrier.display.setCursor(40,110);

  carrier.display.println("tempetature:\C");
  carrier.display.println(fTemp);
  carrier.display.println("humidite:");
  carrier.display.println(fHumdite);
  carrier.display.println("Pression:");
  carrier.display.println(fPressionAt);
  carrier.display.print(" hpa");
  // put your main code here, to run repeatedly:
  delay(1000);

//  Serial.println("Rct loop");
//wifi
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED){
    //Serial.print("Tentative de connexion au réseau ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(2000);
  }
    Serial.print("connecté");
    delay(2000);
    printCurrentNet();
  //adresse ip display
  
  
  carrier.display.fillScreen(ST77XX_RED);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(2);
  carrier.display.setCursor(40,110);
  carrier.display.println("Bienvenue");
  carrier.display.println("adIP: ");
  ipadd = WiFi.localIP();
  carrier.display.print(ipadd.toString());
  delay(2000);
  
}


