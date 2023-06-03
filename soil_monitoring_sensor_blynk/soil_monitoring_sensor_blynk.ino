#include <FS.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h> 
#include <WiFiManager.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define BLYNK_PRINT Serial

char blynk_token[34] = "BLYNK_TOKEN";

bool shouldSaveConfig = false;

BlynkTimer timer;

void myTimeEvent()
{
  int adc = analogRead(A0); 
  int persen = (100-((adc/1023.00))*100);
  Blynk.virtualWrite(V0, persen);
}

void setup() {
  initialize();
  Blynk.begin(blynk_token, WiFi.SSID().c_str(), WiFi.psk().c_str());
  timer.setInterval(1000L, myTimeEvent);
}

void loop() 
{
  int adc2 = analogRead(A0);
  int persen2 = (100-((adc2/1023.00))*100);
  Serial.println(persen2);
  String persen3 = ""+String(persen2)+" % ";
  lcd.setCursor(6,0);
  lcd.print(persen3);
  delay(1000);
  lcd.clear();
  
  if (analogRead(A0) >= 0 && analogRead(A0) <= 339){
    lcd.setCursor(2,1);
    lcd.print("TANAH BASAH");
  }
  else if (analogRead(A0) >= 340 && analogRead(A0) <= 475){
    lcd.setCursor(2,1);
    lcd.print("TANAH LEMBAB");
  }
  else{
    lcd.setCursor(2,1);
    lcd.print("TANAH KERING");
  }
  Blynk.run();
  timer.run();
}
