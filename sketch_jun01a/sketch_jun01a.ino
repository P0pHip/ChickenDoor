#include <AFMotor.h>

AF_DCMotor motor(2, MOTOR12_8KHZ); // Création du moteur n ° 2 , 64KHz pwm

int seuil = 300; //seuil luminosité modifiable ici ou avec la vis sur le capteur
int captfdc1; //declaration de la variable 0 ou 1 soit ouvert ou fermée
int captfdc2; //declaration de la variable 0 ou 1 soit ouvert ou fermée

const int VMotor = 45; // changer ce parametre permet de changer la vitesse du moteur

int captLum = A2; //declaration du pin du capteur
int FDC1 = A3;    //declaration du pin du capteur
int FDC2 = A4;    //declaration du pin du capteur

void  setup() {
  
  Serial.begin(9600);            // Mise en place de bibliothèque série à 9600 bps 
  Serial.println( "test du moteur!" );
        

  //setup capteurs
  pinMode(captLum,INPUT); //declaration du capteur comme entrée LUM
  pinMode(FDC1,INPUT);    //declaration du capteur comme entrée FDC1
  pinMode(FDC2,INPUT);    //declaration du capteur comme entrée FDC2
  
}

void loop() {

  captfdc1 = digitalRead(FDC1); // lecture du signal du capteur
  captfdc2 = digitalRead(FDC2); // lecture du signal du capteur
  
  
  motor.run(RELEASE);       // le moteur ne tourne pas 
  
  
  while(captfdc1 == 1)  // Quand capteur FDC1 est activé
  {
    Serial.print ( "FDC1 \n" ); // affiché FDC1 sur la console(petite loupe en haut)
    motor.setSpeed(VMotor);      
    motor.run (BACKWARD);       // marche arrière
    captfdc1 = digitalRead(FDC1);
  }
  
  
  while(captfdc2 == 1)   // Quand capteur FDC2 est activé
  {
    Serial.print ( "FDC2 \n" ); // affiché FDC2 sur la console(petite loupe en haut)
    motor.setSpeed(VMotor);
    motor.run (FORWARD);        // marche avant
    captfdc2 = digitalRead(FDC2);
  }
  
  /*  
  while(analogRead(captLum)>seuil) // Quand le capteur Lum change de mode selon le seuil
  {
    Serial.print (" LUM \n");
    motor.setSpeed(50);
    motor.run (FORWARD);
    delay(1000);

    motor.setSpeed(120);
    motor.run (FORWARD);
    delay(1000);

    motor.setSpeed(250);
    motor.run (FORWARD);
    delay(1000);

    motor.run (RELEASE);
    delay(1000);

    motor.setSpeed(250);
    motor.run (BACKWARD);
    delay(1000);

    motor.setSpeed(120);
    motor.run (BACKWARD);
    delay(1000);

    motor.setSpeed(50);
    motor.run (BACKWARD);
    delay(1000);
  }
  */
  
}
