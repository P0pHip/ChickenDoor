#include <BTS7960.h>

#define Rpwm 9   // Pin pour le moteur (Rotation arrière)
#define Lpwm 10  // Pin pour le moteur (Rotation avant)
#define Len 11   // Activation moteur vers l'avant
#define Ren 12   // Activation moteur vers l'arrière

BTS7960 motor(Len, Ren, Lpwm, Rpwm);  // Déclaration du moteur avec les pins

int seuil = 300;          // Seuil de luminosité
const int VMotor = 200;   // Vitesse du moteur
int delaiEnMinutes = 1;  // Durée d'attente de 15 minutes

int captLum = A2;         // Pin du capteur de luminosité
int FDC1 = A3;            // Pin du capteur de fin de course 1 (ouvert)
int FDC2 = A4;            // Pin du capteur de fin de course 2 (fermé)

void setup() {
  Serial.begin(9600);        // Initialisation de la communication série
  motor.begin();             // Configuration des pins du moteur
  motor.enable();            // Activation du moteur

  pinMode(captLum, INPUT);   // Définir le capteur de lumière comme entrée
  pinMode(FDC1, INPUT);      // Définir FDC1 comme entrée
  pinMode(FDC2, INPUT);      // Définir FDC2 comme entrée

  Serial.println("Test du moteur avec capteurs et luminosité...");
}

// Fonction de contrôle du moteur
void controlMotor(bool ouverture) {
  if (ouverture) {
    Serial.println("Ouverture du mécanisme (Matin)");
    motor.pwm = VMotor;
    motor.front();  // Rotation avant pour ouverture
    while (digitalRead(FDC1) == 0) {}  // Attendre que FDC1 soit atteint
  } else {
    Serial.println("Fermeture du mécanisme (Soir)");
    motor.pwm = VMotor;
    motor.back();   // Rotation arrière pour fermeture
    while (digitalRead(FDC2) == 0) {}  // Attendre que FDC2 soit atteint
  }
  motor.stop();  // Arrêt du moteur après l'action
}

// Fonction pour vérifier la condition de lumière après un délai
bool checkLuminosite(int seuil, bool inferieur) {
  delay(delaiEnMinutes * 60000UL);  // Attendre 'delaiEnMinutes' minutes
  int luminosite = analogRead(captLum);  // Relecture de la luminosité après le délai
  return inferieur ? luminosite < seuil : luminosite > seuil;
}

void loop() {
  int luminosite = analogRead(captLum);  // Lire la luminosité actuelle

  // Si la luminosité est inférieure au seuil (matin), on tente d'ouvrir
  if (luminosite < seuil && che
  ckLuminosite(seuil, true)) {
    if (digitalRead(FDC1) == 0) {  // Si le capteur de fin de course 1 n'est pas atteint
      controlMotor(true);           // Ouvrir le mécanisme
    }
  }

  // Si la luminosité est supérieure au seuil (soir), on tente de fermer
  if (luminosite > seuil && checkLuminosite(seuil, false)) {
    if (digitalRead(FDC2) == 0) {  // Si le capteur de fin de course 2 n'est pas atteint
      controlMotor(false);          // Fermer le mécanisme
    }
  }
}
