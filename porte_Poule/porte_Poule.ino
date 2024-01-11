#include <AFMotor.h>

  AF_DCMotor motor(2, MOTOR12_8KHZ); // Création du moteur n ° 2 , 8KHz pwm

  int seuil = 300; //seuil luminosité modifiable ici ou avec la vis sur le capteur
  int captfdc1; //declaration de la variable 0 ou 1 soit ouvert ou fermée
  int captfdc2; //declaration de la variable 0 ou 1 soit ouvert ou fermée

  const int VMotor = 45; // changer ce parametre permet de changer la vitesse du moteur

  int captLum = A2; //declaration du pin du capteur
  int FDC1 = A3;    //declaration du pin du capteur
  int FDC2 = A4;    //declaration du pin du capteur

  // pour l'heure

  unsigned int heurereinitialisation;
  unsigned int fermeturesoir;
  unsigned int ouverturematin;
  unsigned int t;
  unsigned int t1;
  unsigned int t2;


void setup() 
{
  Serial.begin(9600);            // Mise en place de bibliothèque série à 9600 bps 
  Serial.println( "test du moteur!" );
        

  //setup capteurs
  pinMode(captLum,INPUT); //declaration du capteur comme entrée LUM
  pinMode(FDC1,INPUT);    //declaration du capteur comme entrée FDC1
  pinMode(FDC2,INPUT);    //declaration du capteur comme entrée FDC2
  
  // syst heure
  fermeturesoir=22;          //fermeturesoir correspond à l'heure ou la porte se fermera(heure en heure)
  ouverturematin=7;          //ouverturematin correspond à l'heure ou la porte se fermera(heure en heure)
  heurereinitialisation=22;  //heurereinitialisation correpond à l'heure à laquelle vous téléverser le programme sur la carte,
                           //Vous devez changez ce paramètre à chaque fois que téléverser le programme(heure en heure)
  ouverturematin=24-heurereinitialisation+ouverturematin;
  fermeturesoir=fermeturesoir-heurereinitialisation;
  fermeturesoir=fermeturesoir+1;
  ouverturematin=ouverturematin+1;
  
}

void loop() 
{  
  t2=0;

  while (t2 < 24)
  {
    t2=t2+1;
    t1=0;
    
    if (t2==ouverturematin)
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

    if (t2==fermeturesoir || (analogRead(captLum)<seuil))
    {
      captfdc2 = digitalRead(FDC2);
    
      while(captfdc2 == 0)
      {
        Serial.print ("fermeture Soir \n");
        motor.setSpeed(VMotor);
        motor.run(FORWARD);
        captfdc2 = digitalRead(FDC2);
      }
      motor.run(RELEASE);      
    }

    while (t1 < 3600 )
    {
      t1=t1+1;
      t=0;
      
      while (t < 2 )
      {
        t=t+1;
        delay(500);
      }
    }
    
  }
  
}
