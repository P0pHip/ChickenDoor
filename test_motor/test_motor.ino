#include <BTS7960.h>

#define Rpwm    9     // Moteur Soleil
#define Lpwm    10
#define Len     11
#define Ren     12

BTS7960 motor(Len, Ren, Lpwm, Rpwm);  //declaration motor



void setup() {
  Serial.begin(9600);      // Initialisation de la communication série
  motor.begin();        // setup des pins du motor EST-OUEST    
  
  Serial.println("Test du moteur en cours...");
  motor.enable();

  //vitMotor(0);*
  motor.pwm = 200;
  
  delay(1000);             // Petit délai pour initialiser
}

void loop() {
  // Rotation avant
  Serial.println("Moteur tourne vers l'avant");
  motor.front();
  delay(2000);             // Laisse tourner pendant 2 secondes

  // Arrêt
  Serial.println("Moteur s'arrête");
  motor.stop();            // Arrête le moteur
  delay(1000);             // Pause d'une seconde

  // Rotation arrière
  Serial.println("Moteur tourne vers l'arrière");
  motor.back();
  delay(2000);             // Laisse tourner pendant 2 secondes

  // Arrêt
  Serial.println("Moteur s'arrête");
  motor.stop();            // Arrête le moteur
  delay(1000);             // Pause d'une seconde
}
