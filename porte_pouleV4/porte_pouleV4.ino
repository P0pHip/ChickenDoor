#include <BTS7960.h>

#define Rpwm 9   // Pin pour le moteur (Rotation arrière)
#define Lpwm 10  // Pin pour le moteur (Rotation avant)
#define Len 11   // Activation moteur vers l'avant
#define Ren 12   // Activation moteur vers l'arrière

BTS7960 motor(Len, Ren, Lpwm, Rpwm);  // Déclaration du moteur avec les pins

int seuil = 300;          // Seuil de luminosité modifiable ici
int captfdc1;             // Variable pour le capteur de fin de course 1 (ouvert)
int captfdc2;             // Variable pour le capteur de fin de course 2 (fermé)

const int VMotor = 200;   // Vitesse du moteur

int captLum = A2;         // Pin du capteur de luminosité
int FDC1 = A3;            // Pin du capteur de fin de course 1 (ouvert)
int FDC2 = A4;            // Pin du capteur de fin de course 2 (fermé)

void setup() {
  Serial.begin(9600);       // Initialisation de la communication série
  motor.begin();            // Configuration des pins du moteur

  Serial.println("Test du moteur avec capteurs et luminosité...");
  motor.enable();           // Activation du moteur
}

void loop() {
  // Lecture de la luminosité
  int luminosite = analogRead(captLum);
  
  // Si la luminosité est inférieure au seuil (matin), ouverture du mécanisme
  if (luminosite < seuil) {
    // Vérification si après 15 minutes la luminosité est toujours inférieure au seuil
    for (byte h = 0; h < 15; h++) { 
      delay(60000UL);  // Attente de 1 minute
    }
    if (analogRead(captLum) < seuil) {
      captfdc1 = digitalRead(FDC1);  // Lecture du capteur de fin de course 1 (ouvert)
      
      // Tant que le capteur de fin de course 1 est à 0, on ouvre le mécanisme
      while (captfdc1 == 0) {
        Serial.println("Ouverture du mécanisme (Matin)");
        motor.pwm = VMotor;   // Réglage de la vitesse du moteur
        motor.front();        // Ouverture (rotation avant)
        captfdc1 = digitalRead(FDC1);  // Relecture du capteur
      }
      motor.stop();  // Arrêt du moteur une fois ouvert
    }
  }

  // Si la luminosité est supérieure au seuil (soir), fermeture du mécanisme
  if (luminosite > seuil) {
    // Vérification si après 15 minutes la luminosité est toujours supérieure au seuil
    for (byte j = 0; j < 15; j++) {
      delay(60000UL);  // Attente de 1 minute
    }
    if (analogRead(captLum) > seuil) {
      captfdc2 = digitalRead(FDC2);  // Lecture du capteur de fin de course 2 (fermé)

      // Tant que le capteur de fin de course 2 est à 0, on ferme le mécanisme
      while (captfdc2 == 0) {
        Serial.println("Fermeture du mécanisme (Soir)");
        motor.pwm = VMotor;  // Réglage de la vitesse du moteur
        motor.back();        // Fermeture (rotation arrière)
        captfdc2 = digitalRead(FDC2);  // Relecture du capteur
      }
      motor.stop();  // Arrêt du moteur une fois fermé
    }
  }
}
