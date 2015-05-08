#include <Adafruit_NeoPixel.h>
#define PIN 12
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
#include <Servo.h>
#include <SimpleTimer.h>

// the timer object
SimpleTimer timer;
int countDown;
Servo sapservo;

int light;
int lightsense = A3;
int servoHoek = 0;
int maxTijd = 60;
int rood;
int groen;

// a function to be executed periodically
void repeatMe() {
  Serial.print("Uptime (s): ");
  countDown = (millis() / 1000);
  Serial.println(countDown);
}

void setup() {
  Serial.begin(9600);
  timer.setInterval(1000, repeatMe);
  sapservo.attach(9); // servo aangesloten op pin 9
  strip.begin();
  strip.setBrightness(255);
  strip.show();
}

void loop() {
  light = analogRead(lightsense);
  rood = map(countDown, 0, maxTijd, 0, 255);
  groen = map(countDown, 0, maxTijd, 255, 0);
  rood = constrain(rood, 0, maxTijd);
  groen = constrain(groen, 0, maxTijd);
  
  timer.run();
  servoHoek = map(countDown, 0, maxTijd, 180, 0); //time is de functie die jullie hebben die telt. dus in 600 seconde (10x60) gaat de hoek van 0 tot 180.
  servoHoek = constrain(servoHoek, 0, 180); //hiermee voorkom je dat servoHoek groter dan 180 of kleiner dan 0 wordt. Ookals wordt timer wel groter dan 600 of kleiner dan 0.
  sapservo.write(servoHoek);
  Serial.println(servoHoek);
  delay(15);
  
  if (light > 10) {
    lightShow();
  } else {
    strip.setPixelColor(0, 0, 0, 0);
    strip.show();
  }
  
  if(countDown > maxTijd){
    sapservo.write(0);
    delay(1000);
    software_Reset() ;
  }
}

void lightShow() {
  strip.setPixelColor(0, rood, groen, 0);
  strip.show();
  delay(200);
}

void software_Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
  asm volatile ("  jmp 0");  
}  
