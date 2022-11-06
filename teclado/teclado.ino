#include <Keypad.h>

const byte rowsCount = 4;
const byte columsCount = 3;

byte pinesFilas[] = {9, 10, 11, 12};
byte pinesColumnas[] = {2, 3, 4};

char keys[rowsCount][columsCount] = {
  { '1', '2', '3', },
  { '4', '5', '6', },
  { '7', '8', '9', },
  { '*', '0', '#', }
};


Keypad teclado1 = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, rowsCount, columsCount);

void setup() {
  Serial.begin(9600);
  Serial.println("Teclado 4x3 con Biblioteca Keypad");
  Serial.println();
}
void loop() {
  //Verifica si alguna tecla fue presionada
  char tecla_presionada = teclado1.getKey();

  //Monitor Serial
  if (tecla_presionada)
  {
    Serial.print("Tecla: ");
    Serial.println(tecla_presionada);
  }
}
