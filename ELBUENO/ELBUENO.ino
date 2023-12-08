
#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11 ); //RX TX



String estado[5] = {
  "Avanzar",
  "Retroceder",
  "Derecha",
  "Izquierda",
  "Detener"
};

int matrizDireccion[5][4] = {
  {1,	0,	1,	0},
  {0,	1,	0,	1},
  {1,	0,	0,	1},
  {0,	1,	1,	0},
  {0,	0,	0,	0}
};

int matrizVelocidad[5][2] = {
  {255,	255},
  {255,	255},
  {255,	127},
  {127,	255},
  {0,	0}
};

int inputs[4] = { 8, 7, 12, 13}; //in1, in2, in3, in4 --pines digitales
int enables[2] = {5, 6}; // pines para PWM ... Enable A - Enable B
int i,j;

void SetDireccion(int estado){
  for(i = 0;  i<4; i++){
    digitalWrite(inputs[i],matrizDireccion[estado][i]);
    Serial.print(String(matrizDireccion[estado][i]) + " ");
  }
  Serial.print(" -- ");
  for(i = 0;  i<2; i++){
    analogWrite(enables[i],matrizVelocidad[estado][i]);
    Serial.print(String(matrizVelocidad[estado][i]) + " ");
  }
  Serial.println();
}

void setup() {

  Serial.begin(9600);
  BT.begin(9600);

  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(100); //ms

  for(int i = 0 ; i < 4; i++){
    pinMode(inputs[i], OUTPUT);
  }

}
String s = "";



void loop() {

  if(BT.available()>0){ 
    Serial.write(BT.read());
 } 

 if(Serial.available()>0){ 
    BT.write(Serial.read());
 } 



  // put your main code here, to run repeatedly:
    if(BT.available()>0){
      int val = Serial.parseInt(); 
      SetDireccion(val);
      Serial.println("Estado Aplicado: " + estado[val]);            
    }
}
