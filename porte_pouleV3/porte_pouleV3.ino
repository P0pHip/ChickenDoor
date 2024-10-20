#include <AFMotor.h>

  AF_DCMotor motor(3, MOTOR34_8KHZ); // Création du moteur n ° 3 , 8KHz pwm

  int seuil = 300; //seuil luminosité modifiable ici ou avec la vis sur le capteur
  int captfdc1; //declaration de la variable 0 ou 1 soit ouvert ou fermée
  int captfdc2; //declaration de la variable 0 ou 1 soit ouvert ou fermée

  const int VMotor = 250; // changer ce parametre permet de changer la vitesse du moteur

  int captLum = A2; //declaration du pin du capteur
  int FDC1 = A3;    //declaration du pin du capteur
  int FDC2 = A4;    //declaration du pin du capteur


void setup() 
{
  Serial.begin(9600);            // Mise en place de bibliothèque série à 9600 bps 
  Serial.println( "test du moteur!" );
        

  //setup capteurs
  pinMode(captLum,INPUT); //declaration du capteur comme entrée LUM
  pinMode(FDC1,INPUT);    //declaration du capteur comme entrée FDC1
  pinMode(FDC2,INPUT);    //declaration du capteur comme entrée FDC2
}

void loop() 
{  
 
  if (analogRead(captLum)<seuil)
  {
    for(byte h=0; h<15; h++) // h = 60 represente 60 min
    { 
      delay(60000UL);  //ceci motre une pause de 1 min 
    }
    if (analogRead(captLum)<seuil)
    {
      captfdc1 = digitalRead(FDC1); // lecture du signal du capteur
      while(captfdc1 == 0)
      {
        Serial.print ("ouverture Matin \n");
        motor.setSpeed(VMotor);
        motor.run(BACKWARD);
        captfdc1 = digitalRead(FDC1); // lecture du signal du capteur
      }   
      motor.run(RELEASE); // le moteur s'arrête
    }
  }

    
  if (analogRead(captLum)>seuil)
  {
    for(byte j=0; j<15; j++) // j = 60 represente 60 min
    { 
      delay(60000UL);  //ceci motre une pause de 1 min 
    }
    if (analogRead(captLum)>seuil)
    {
      captfdc2 = digitalRead(FDC2); //lectur de capteur fdc2
      while(captfdc2 == 0) //tant qu'il est a 0 faire les instructions
      {
        Serial.print ("fermeture Soir \n");
        motor.setSpeed(VMotor);
        motor.run(FORWARD); // moteur en marche
        captfdc2 = digitalRead(FDC2);
      }
      motor.run(RELEASE);      // arret moteur
    }
  }    
}
  
