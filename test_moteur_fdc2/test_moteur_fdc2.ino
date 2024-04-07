#include <AFMotor.h>

  AF_DCMotor motor(2, MOTOR12_64KHZ); // Création du moteur n ° 2 , 8KHz pwm

  int seuil = 300; //seuil luminosité modifiable ici ou avec la vis sur le capteur
  int captfdc1; //declaration de la variable 0 ou 1 soit ouvert ou fermée
  int captfdc2; //declaration de la variable 0 ou 1 soit ouvert ou fermée

  const int VMotor = 255; // changer ce parametre permet de changer la vitesse du moteur

  int captLum = A2; //declaration du pin du capteur
  int FDC1 = A3;    //declaration du pin du capteur
  int FDC2 = A4;    //declaration du pin du capteur




void setup() {
 Serial.begin(9600);            // Mise en place de bibliothèque série à 9600 bps 
  Serial.println( "test du moteur!" );
        

  //setup capteurs
  pinMode(captLum,INPUT); //declaration du capteur comme entrée LUM
  pinMode(FDC1,INPUT);    //declaration du capteur comme entrée FDC1
  pinMode(FDC2,INPUT);    //declaration du capteur comme entrée FDC2
}

void loop() {
  // put your main code here, to run repeatedly:
  captfdc1 = digitalRead(FDC1);
  captfdc2 = digitalRead(FDC2);
  
  if(captfdc2 == 0){
     Serial.print ("ouverture Matin \n");
     motor.setSpeed(VMotor);
     motor.run(BACKWARD);    
  }
  captfdc1 = digitalRead(FDC1);
  captfdc2 = digitalRead(FDC2);
  
  if(captfdc1 == 0){
    Serial.print ("fermeture Soir \n");
    motor.setSpeed(VMotor);
    motor.run(FORWARD); // moteur en marche
  }
  captfdc1 = digitalRead(FDC1);
  captfdc2 = digitalRead(FDC2);

  captfdc1 = digitalRead(FDC1);
  captfdc2 = digitalRead(FDC2);
  
  if(captfdc1 == 1|| captfdc2==1){
    motor.run(RELEASE);
  }
  
    
}
