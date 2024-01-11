#include <SoftwareSerial.h>


const int seuil = 300; 
const int moteur = 3;
const int vitesseMoteur = 50;

int captfdc1 = 0; //declaration de la variable 0 ou 1 soit ouvert ou fermée
int captfdc2 = 0; //declaration de la variable 0 ou 1 soit ouvert ou fermée

int capteurfdc1 = 7; // capteur fin de course haut
int capteurfdc2 = 8; // capteur fin de course bas



void setup() {
  // put your setup code here, to run once:
pinMode(12,OUTPUT); 
//direction 
  pinMode(moteur,OUTPUT); 
//setup capteurs 

pinMode(capteurfdc1,INPUT); 
pinMode(capteurfdc2,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  captfdc1 = digitalRead(capteurfdc1);
  captfdc2 = digitalRead(capteurfdc2);
  
  if(captfdc2 ==1){
    digitalWrite(12,HIGH);
    analogWrite(moteur,250);
  }
  captfdc1 = digitalRead(capteurfdc1);
  captfdc2 = digitalRead(capteurfdc2);
  
  if(captfdc2 ==0){
    digitalWrite(12,LOW);
    analogWrite(moteur,0);
  }
  captfdc1 = digitalRead(capteurfdc1);
  captfdc2 = digitalRead(capteurfdc2);

  if(captfdc1 ==1){
    digitalWrite(12,HIGH);
    analogWrite(moteur,100);
  }
  captfdc1 = digitalRead(capteurfdc1);
  captfdc2 = digitalRead(capteurfdc2);
  
  if(captfdc1 ==0){
    digitalWrite(12,LOW);
    analogWrite(moteur,0);
  }
  
    
}
