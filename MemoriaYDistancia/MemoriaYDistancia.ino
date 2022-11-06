#include <SPI.h>    // incluye libreria interfaz SPI
#include <SD.h>     // incluye libreria para tarjetas SD

#define SSpin 53    // Slave Select en pin digital 10
#define sensorPin A0
int distance = 0;

File archivo;     // objeto archivo del tipo File
void read_sensor() {
 distance = analogRead(sensorPin) * 5;
}

void print_data() {
 Serial.print("distance = ");
 Serial.print(distance);
 Serial.println(" mm");
}

void setup() {
  Serial.begin(9600);   // inicializa monitor serie a 9600 bps
  Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("datos.txt", FILE_WRITE); // apertura para lectura/escritura de archivo datos.txt

  if (archivo) {  
    for (int i=1; i < 100; i++){     // bucle repite 30 veces

      read_sensor();
  

      archivo.print(distance);       // escribe en tarjeta el valor del indice
      archivo.print(" ");     // escribe en tarjeta una coma
      archivo.println("mm");     // escribe en tarjeta el valor de humedad y salto de linea

      Serial.print(distance);        // escribe en monitor el valor del indice
      Serial.print(" ");      // escribe en monitor una coma
      Serial.println("mm");      // escribe en monitor el valor de humedad y salto de linea

      delay(1000);        // demora de 1 segundo
      }
    archivo.close();        // cierre de archivo
    Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie
  } else {
    Serial.println("error en apertura de datos.txt"); // texto de falla en apertura de archivo
  }
}

void loop() {     // funcion loop() obligatoria de declarar pero no utilizada
  // nada por aqui
}
