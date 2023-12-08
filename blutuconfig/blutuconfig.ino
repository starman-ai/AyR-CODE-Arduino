#include <SoftwareSerial.h>


//HC05 - Maestro / Esclavo

//5*Terminales 
//5 v
//GND
//TX
//RX
//ENABLE
//STATE


SoftwareSerial BT(10, 11 ); //RX TX

//BT - ARDUINO
//5 v  5V
//GND  GND
//TX   RX
//RX   TX
//ENABLE NO SE CONECTA




void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  BT.begin(38400);
}
String s = "";
void loop() {
  // put your main code here, to run repeatedly:

 // HALF DUPLEX...

if(BT.available()>0){ 
    Serial.write(BT.read());
 } 

 if(Serial.available()>0){ 
    BT.write(Serial.read());
 } 

 
}
