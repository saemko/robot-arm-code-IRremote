#include <IRremote.h>
#include <IRremoteInt.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27 
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin); 

int echo = 13 ;
int trig = 12;
long duration;
int distance;
int safetyDistance;
float distanceCm;



int RECV_PIN = 11; 
int gndIR=10; 
int powerIR=9;
IRrecv irrecv(RECV_PIN);

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int doprava = 90;
int dolava = 90;
int nula = 0;
int bill = 0;



decode_results results;

void setup(){
  irrecv.enableIRIn(); 
pinMode(gndIR, OUTPUT);
pinMode(powerIR, OUTPUT);
digitalWrite(gndIR, LOW); // pin 10 uzemnenie
digitalWrite(powerIR, 255); // Pin 9 - napätie
  servo1.attach(2); 
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);


   lcd.begin(16,2); 
           lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
           lcd.setBacklight(HIGH);

  
}

void sonar() {
  digitalWrite(trig, LOW);
  delay(80);
  digitalWrite(trig, HIGH);
  delay(80);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance=duration*0.034/2;
  safetyDistance = distance;
  Serial.print("Distance: ");
  Serial.println(distance);

}





void ok1() {
    servo3.write(90);
    delay(300);
    servo2.write(90);
    delay(300);
    servo1.write(90);
    delay(300);
    servo4.write(90);
    delay(300);
    servo5.write(90);
}


void ok() {
  if(results.value==0xFF38C7) {
    servo1.write(50);
    delay(200);
    servo2.write(60);
    delay(200);
    servo3.write(120);
    delay(300);  
    servo2.write(90);
    delay(300);
    servo1.write(90);
    delay(300);
    servo3.write(90);
    delay(300);
    servo4.write(90);
    delay(300);
    servo5.write(90);
  }
}


void displej() {
  lcd.clear(); 
          digitalWrite(trig, LOW); 
          delayMicroseconds(2);       
          digitalWrite(trig, HIGH);
          delayMicroseconds(10);     
          digitalWrite(trig, LOW); 
          duration = pulseIn(echo, HIGH); 
          distanceCm= duration*0.034/2;
          lcd.setCursor(0,0); 
          lcd.print("Distance: "); 
          lcd.setCursor(0,1);
          lcd.print(distanceCm); 
          lcd.print(" cm");
          delay(100);
}

void loop() {

  displej();
  sonar();

 if (irrecv.decode(&results)) {

     ok();

     
//čelusť tlačidlo 0
  if(results.value==0xFF9867) {
    servo5.write(170);
  }
  // tlačidlo 9
  if(results.value==0xFF906F) {
    servo5.write(90);
  }
//doprava
  if(results.value==0xFF5AA5) {
    
    for(doprava = 90; doprava >= 30; doprava -= 2) {
    servo1.write(doprava);
    delay(15);
    }
  }
//doľava
  if(results.value==0xFF10EF) {
    for(dolava = 90; dolava <= 150; dolava += 2) {
    servo1.write(dolava);
    delay(15);
    }
  }
//hore
  if(results.value==0xFF18E7) {
    servo2.write(30);
  }
//dole
  if(results.value==0xFF4AB5) {
    servo2.write(150);
    servo4.write(170);
  }
//hore 2
  if(results.value==0xFFA25D) {
    servo3.write(140);
  }
//dole 2
  if(results.value==0xFF22DD) {
    servo3.write(50);
  }
//hore 3
  if(results.value==0xFF629D) {
    servo4.write(170);
  }
//dole 3
  if(results.value==0xFF02FD) {
    servo4.write(30);
  }
//*
  if(results.value==0xFF6897) {
    servo2.write(150);
    servo4.write(140);
    servo3.write(110);
    delay(650);
    servo5.write(170);
    servo5.write(170);
    for(nula = 150; nula > 100; nula--)
    {
    servo2.write(nula);
    delay(50);  
    }
    for(nula = 90; nula > 20; nula-=3)
    {
    servo1.write(nula);
    delay(50);  
    }
    for(nula = 120; nula > 70; nula -=2)
    {
    servo3.write(nula);
    delay(50);  
    }
    for(nula = 140; nula > 120; nula -=3)
    {
    servo4.write(nula);
    delay(50);  
    }
    delay(300);
    servo5.write(90);
    delay(400);
    servo3.write(130);
    delay(300);
    servo2.write(70);
    delay(300);
    servo4.write(90);
    delay(300);
   for(nula = 30; nula < 150; nula +=2)
   {
    servo1.write(nula);
    delay(50);
   }
   delay(400);
   
   servo4.write(30);
   delay(400);
   for(nula = 70; nula < 150; nula +=2){
    servo2.write(nula);
    delay(50);
   }
   servo5.write(170);
   delay(400);
   servo2.write(110);
   for(nula = 150; nula > 30; nula -=2){
    servo1.write(nula);
    delay(50);
   }
   delay(100);
   servo2.write(130);
   delay(180);
   servo5.write(90);
  }
  
//#
  if(results.value==0xFFB04F) {
    bill = 0;
    servo4.write(170);
    servo2.write(150);
    while(bill <= 2) {
      sonar();
      displej();
    for(nula = 20; nula <= 150; nula +=2) {
      servo1.write(nula);
      delay(5);
      sonar();
      displej();
      
    }
    for(nula = 150; nula >= 20; nula-=2) {
      servo1.write(nula);
      delay(5);
      sonar();
      displej();
    }
    bill++;
    ok();
    }
  }
  
   
  irrecv.resume();
 
}


}
