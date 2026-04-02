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
  pinMode(FDC1, INPUT_PULLUP);      // Définir FDC1 comme entrée
  pinMode(FDC2, INPUT_PULLUP);      // Définir FDC2 comme entrée

  Serial.println("=== Démarrage du système ===");
  Serial.println("Test du moteur avec capteurs et luminosité...");
  Serial.println("Seuil de luminosité : " + String(seuil));
  Serial.println("Vitesse moteur : " + String(VMotor));
  Serial.println("Délai de confirmation : " + String(delaiEnMinutes) + " min");
}

// Fonction de contrôle du moteur
void controlMotor(bool ouverture) {
  if (ouverture) {
    Serial.println("Ouverture du mécanisme (Matin)");
    motor.pwm = VMotor;
    motor.front();  // Rotation avant pour ouverture
    Serial.println("En attente de FDC1...");
    while (digitalRead(FDC1) == 1) {}  // Attendre que FDC1 soit atteint
    Serial.println("FDC1 atteint !");
    Serial.println("FDC1 : " + String(digitalRead(FDC1)));
  } else {
    Serial.println("Fermeture du mécanisme (Soir)");
    motor.pwm = VMotor;
    motor.back();   // Rotation arrière pour fermeture
    Serial.println("En attente de FDC2...");
    while (digitalRead(FDC2) == 1) {}  // Attendre que FDC2 soit atteint
    Serial.println("FDC2 atteint !");
    Serial.println("FDC2 : " + String(digitalRead(FDC2)));
  }
  motor.stop();  // Arrêt du moteur après l'action
  Serial.println("Arrêt du moteur");
}

// Fonction pour vérifier la condition de lumière après un délai
bool checkLuminosite(int seuil, bool inferieur) {
  Serial.println("Attente de confirmation de luminosité...");
  delay(delaiEnMinutes * 60000UL);  // Attendre 'delaiEnMinutes' minutes
  int luminosite = analogRead(captLum);  // Relecture de la luminosité après le délai
  Serial.println("Luminosité après délai : " + String(luminosite));
  return inferieur ? luminosite < seuil : luminosite > seuil;
}

void loop() {
  int luminosite = analogRead(captLum);  // Lire la luminosité actuelle
  Serial.println("Luminosité actuelle : " + String(luminosite));
  Serial.println("FDC1 : " + String(digitalRead(FDC1)) + " | FDC2 : " + String(digitalRead(FDC2)));

  // Si la luminosité est inférieure au seuil (matin), on tente d'ouvrir
  if (luminosite < seuil && checkLuminosite(seuil, true)) {
    Serial.println("Condition d'ouverture validée !");
    if (digitalRead(FDC1) == 1) {  // Si le capteur de fin de course 1 n'est pas atteint
      controlMotor(true);           // Ouvrir le mécanisme
    } else {
      Serial.println("FDC1 déjà atteint, ouverture ignorée");
    }
  }

  // Si la luminosité est supérieure au seuil (soir), on tente de fermer
  if (luminosite > seuil && checkLuminosite(seuil, false)) {
    Serial.println("Condition de fermeture validée !");
    if (digitalRead(FDC2) == 1) {  // Si le capteur de fin de course 2 n'est pas atteint
      controlMotor(false);          // Fermer le mécanisme
    } else {
      Serial.println("FDC2 déjà atteint, fermeture ignorée");
    }
  }
}
