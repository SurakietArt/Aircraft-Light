#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "**************";
char ssid[] = "****";
char pass[] = "*************";
WidgetLED Strobe(D6);
WidgetLED Beacon(D7);
const int Wing = D1;
const int Nav = D5;
const int Landing = D4;
const int Nose = D3;
const int Beacon_Blinking = D7;
const int Strobe_Blinking = D6;
int t1_beacon;
int t1_strobe;
BlynkTimer timer;

void blinkLedWidget()
{
  if (Beacon.getValue()) {
    Beacon.off();
    Serial.println("Beacon on D7: off");
  } else {
    Beacon.on();
    Serial.println("Beacon on D7: on");
  }
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, blinkLedWidget);
  pinMode(Beacon_Blinking, OUTPUT);
  pinMode(Strobe_Blinking, OUTPUT);
  pinMode(Nose, OUTPUT);
  pinMode(Nav, OUTPUT);
  pinMode(Landing, OUTPUT);
  pinMode(Wing, OUTPUT);
  t1_beacon = timer.setInterval(1000, ledBlynk);
  t1_strobe = timer.setInterval(1000, ledBlynk1);
  timer.disable(t1_beacon);
  timer.disable(t1_strobe);
}

BLYNK_WRITE(V1)
{
  if (param.asInt()) {
    timer.enable(t1_beacon);
  } else {
    timer.disable(t1_beacon);
    digitalWrite(Beacon_Blinking, LOW);
  }
}
BLYNK_WRITE(V2)
{
  if (param.asInt()) {
    timer.enable(t1_strobe);
  } else {
    timer.disable(t1_strobe);
    digitalWrite(Strobe_Blinking, LOW);
  }
}

BLYNK_WRITE(V3){
  if(param.asInt()){
    digitalWrite(Nose, HIGH);
  }
  else{
    digitalWrite(Nose, LOW);
  }
}

BLYNK_WRITE(V4){
  if(param.asInt()){
    digitalWrite(Landing, HIGH);
  }
  else{
    digitalWrite(Landing, LOW);
  }
}

BLYNK_WRITE(V5){
  if(param.asInt()){
    digitalWrite(Nav, HIGH);
  }
  else{
    digitalWrite(Nav, LOW);
  }
}

BLYNK_WRITE(V6){
  if(param.asInt()){
    digitalWrite(Wing, HIGH);
  }
  else{
    digitalWrite(Wing, LOW);
  }
}

void ledBlynk()
{
  digitalWrite(Beacon_Blinking, !digitalRead(Beacon_Blinking));
}
void ledBlynk1()
{
  digitalWrite(Strobe_Blinking, !digitalRead(Strobe_Blinking));
}
void loop()
{
  Blynk.run();
  timer.run();
}

