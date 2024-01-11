
int captLum = A2; //declaration du pin du capteur
int valeurLue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);            // Mise en place de bibliothèque série à 9600 bps 
  Serial.println( "test du lum!" );
  
  pinMode(captLum,INPUT); //declaration du capteur comme entrée LUM
}

void loop() {
  // put your main code here, to run repeatedly:
  valeurLue = analogRead(captLum);
  Serial.print("\n valeurLue = ");
  Serial.println(valeurLue);
  delay(500);

}
