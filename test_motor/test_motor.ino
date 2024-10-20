//#include <AFMotor.h>
#include <BTS7960.h>

//AF_DCMotor motor(3);  // Création du moteur connecté à la sortie 3
//AF_DCMotor motor(1, MOTOR12_8KHZ); // Création du moteur n ° 3 , 8KHz pwm

#define Rpwm    9     // Moteur Soleil
#define Lpwm    10
#define Len     11
#define Ren     12

BTS7960 motor(Len, Ren, Lpwm, Rpwm);  //declaration motor

//#define ENAIH       10       // On associe la borne "ENA" du L298N à la pin D10 de l'arduino
//#define IN1IH       9        // On associe la borne "IN1" du L298N à la pin D9 de l'arduino
//#define IN2IH       8        // On associe la borne "IN2" du L298N à la pin D8 de l'arduino



void setup() {
  Serial.begin(9600);      // Initialisation de la communication série
  //pinMode(ENAIH, OUTPUT); // setup des pins du moteur INCLINAISON
  //pinMode(IN1IH, OUTPUT);
  //pinMode(IN2IH, OUTPUT);
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
