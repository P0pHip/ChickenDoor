

#include <AFMotor.h>

AF_DCMotor motor(2, MOTOR12_64KHZ); // Création du moteur n ° 2 , 64KHz pwm

int captfdc1 = 0; //declaration de la variable 0 ou 1 soit ouvert ou fermée
int captfdc2 = 0; //declaration de la variable 0 ou 1 soit ouvert ou fermée

//const int moteur = 3;
int capteurfdc1 = 7; // capteur fin de course haut
int capteurfdc2 = 8; // capteur fin de course bas

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Motor test!");
  motor.setSpeed(200);

 // pinMode(12,OUTPUT); 
//direction 
 // pinMode(moteur,OUTPUT); 
//setup capteurs 

  pinMode(capteurfdc1,INPUT); 
  pinMode(capteurfdc2,INPUT);
}

void loop() {

  
  // put your main code here, to run repeatedly:
  captfdc1 = digitalRead(capteurfdc1);
  captfdc2 = digitalRead(capteurfdc2);
  
  if(captfdc2 ==1){
    Serial.print("captf2 pin8 \n");
    //motor.setSpeed(255);
    motor.run(FORWARD);
  }
  //captfdc1 = digitalRead(capteurfdc1);
  //captfdc2 = digitalRead(capteurfdc2);
  
  if(captfdc2 ==0){
    motor.run(RELEASE);
  }
  //captfdc1 = digitalRead(capteurfdc1);
  //captfdc2 = digitalRead(capteurfdc2);

  if(captfdc1 ==1){
    Serial.print("je suis a 1 ");
    Serial.print("captf1 pin7 \n");
    motor.run(BACKWARD);
    Serial.print("je tourne en backward \n"); 
  }
  //captfdc1 = digitalRead(capteurfdc1);
  //captfdc2 = digitalRead(capteurfdc2);
  
  if(captfdc1 ==0){    
    motor.run(RELEASE);
    
    
  }
/*  
Serial.print("tick");
motor.run(FORWARD);
delay(1000);
Serial.print("tack");
motor.run(RELEASE);
delay(1000);
Serial.print("tock");
motor.run(BACKWARD);
delay(1000);
*/

}
