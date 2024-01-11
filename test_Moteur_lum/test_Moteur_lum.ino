#include <SoftwareSerial.h>

const int capteurLum = A2;
int captLum = analogRead(capteurLum);
const int seuil = 300; 
const int moteur = 3;
const int vitesseMoteur = 50;




void setup() {
  // put your setup code here, to run once:
pinMode(12,OUTPUT); 
//direction 
  pinMode(moteur,OUTPUT); 
//setup capteurs 

pinMode(capteurLum,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  captLum = analogRead(capteurLum);
  
  while(captLum>seuil){
  
    digitalWrite(12,HIGH);
    analogWrite(moteur,255);
    captLum = analogRead(capteurLum);
  }
  digitalWrite(12,LOW);
  analogWrite(moteur,0);
}
