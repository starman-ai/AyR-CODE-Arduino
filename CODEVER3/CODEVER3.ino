#include <SoftwareSerial.h>
SoftwareSerial BT(10,11);

String estado[5] = {
  "Avanzar",
  "Retroceder",
  "Derecha",
  "Izquierda",
  "Detener"
};

int matrizDireccion[5][4] = {
 {0, 1, 1, 0},
 {1, 0, 0, 1},
 {0, 1, 0, 1},
 {1, 0, 1, 0},
 {0, 0, 0, 0}
};

int matrizVelocidad[5][2] = {
 {255, 255},
 {255, 255},
 {255, 127},
 {127, 255},
 {0, 0}
};

int inputs[4] = {2, 3, 4, 5}; // int1, int2, int3....
int enables[2] = {9, 6}; // pines para PWM
int sensorPines[4] = {A0, A1, A2, A3}; // Pines de los sensores
int i, j;
int command;

void setDireccion(int estado) {
  for (i = 0; i < 4; i++) {
    digitalWrite(inputs[i], matrizDireccion[estado][i]);
    Serial.print(String(matrizDireccion[estado][i]) + " ");
  }
  Serial.print(" -- ");
  for (i = 0; i < 2; i++) {
    analogWrite(enables[i], matrizVelocidad[estado][i]);
    Serial.print(String(matrizVelocidad[estado][i]) + " ");
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
  BT.begin(9600);

  for (int i = 0; i < 4; i++) {
    pinMode(inputs[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0) {
    int val = Serial.readString().toInt();
    setDireccion(val);
    Serial.println("Estado aplicado: " + estado[val]);
    BT.write(val);
  }

  if (BT.available() > 0) {
    command = BT.read() - 48; // Restar 48 para convertir el carácter numérico a un entero

    Serial.println("Estado aplicado: " + estado[command]);
    setDireccion(command);
  }

  // Lógica de seguimiento de línea
  int sensorValues[4];
  for (i = 0; i < 4; i++) {
    sensorValues[i] = analogRead(sensorPines[i]);
  }

  // Define umbrales para tus sensores (ajústalos según tu pista)
  int umbral = 511;

  // Verifica si los sensores de seguimiento están activados
  boolean activados = false;
  for (i = 0; i < 4; i++) {
    if (sensorValues[i] < umbral) {
      activados = true;
      break; // Un sensor activado es suficiente para considerarlos activados
    }
  }

  if (activados) {
    // Los sensores de seguimiento están activados
    if (sensorValues[0] < umbral) {
      // Avanzar recto
      setDireccion(0); // Estado de "Avanzar"
    } else {
      // Los otros sensores determinarán la dirección
      if (sensorValues[1] < umbral) {
        // Giro a la izquierda
        setDireccion(3); // Estado de "Izquierda"
      } else if (sensorValues[2] < umbral) {
        // Giro a la derecha
        setDireccion(2); // Estado de "Derecha"
      } else if (sensorValues[3] < umbral) {
        // Retroceder
        setDireccion(1); // Estado de "Retroceder"
      } else {
        // Si ninguno de los sensores detecta la línea, detener
        setDireccion(4); // Estado de "Detener"
      }
    }
  } else {
    // Los sensores de seguimiento no están activados
    // Aquí puedes agregar lógica adicional o mantener el carrito en su último estado conocido.
  }

  // Ajusta los umbrales según tus sensores y pista
}