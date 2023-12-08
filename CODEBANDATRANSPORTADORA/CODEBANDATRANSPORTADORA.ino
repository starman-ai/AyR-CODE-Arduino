int i= 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  // Reinicia el ciclo de movimiento de la banda
  for (i = 1; i <= 4; i += 1){
    digitalWrite(2, LOW);
    digitalWrite(5, HIGH);
    delay(8000); //Espera por 8 segundos
    digitalWrite(2, HIGH);
    digitalWrite(5, LOW);
    delay(15000); //Espera por 15 segundos
  }
}
