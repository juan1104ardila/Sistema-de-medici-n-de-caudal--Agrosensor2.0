#include <Keypad.h>; // Con esta linea llamamos a la librería Keypad para que arduino reconozca el teclado
char contrasena[]="2222"; // En esta linea creamos la constante de cadena llamada contraseña (el numero 2222 puede ser cambiado)
char codigo[5];// Creamos otra constante, en esta se guardaran los caracteres que presionemos en nuestro teclado matricial 4x4
char cambio[5];
char palabra1;
char palabra2;
char palabra3;
int x=0;
int cont=0; // Esta es una variable que nos servirá más adelante

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


Keypad customKeypad = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, rowsCount, columsCount);

 //En este punto el teclado se inicia y realiza el mapeo de sus teclas con respecto a la matriz colocada arriba
  
void setup()
{
 pinMode(13, OUTPUT); //El pin 13 sera nuestra salida digital (así aprovecharemos el led que pose)
 Serial.begin(9600); //Se inicia el puerto serial
}
  
void loop()
{
 char customKey = customKeypad.getKey(); //esta linea indica que el carácter presionado se guardara en la variable customKey
 if (customKey != NO_KEY) //Con este siclo preguntamos si se presiono una tecla, si se presiono entonce el ciclo continua
 {
 codigo[cont]=customKey; //se guardaran los caracteres presionados en codigo[cont]
 Serial.print(codigo[cont]); //Se imprime en nuestro monitor serial lo que este guardado en codigo[cont]
 Serial.print(',');
 Serial.println(cont);
 

    if(codigo[0]=='1'){

      Serial.println("codigo 1");
      cont=cont+1;
      codigo[0]=0;
      
        }
    if(codigo[1]=='*'){
      Serial.println("pulse un numero1");
      x=1;
      codigo[1]=0;
      cont=cont+1;

     }

    if(codigo[2]!= NO_KEY && x==1){
      Serial.println("pulse un numero2");
      palabra1=codigo[2];
      codigo[2]=0;
      x=2;
      cont=cont+1;
      }

    if(codigo[3]!= NO_KEY && x==2){
      Serial.println("pulse un numero 2");
      palabra2=codigo[3];
      codigo[3]=0;
      cont=cont+1;
      x=3;
      }      

    if(codigo[4]!= NO_KEY && x==3){
      Serial.println("pulse un * ");
      palabra3=codigo[4];
      codigo[4]=0;
      cont=cont+1;
      }

     if(codigo[5]== '*'){
      Serial.print("AT+CAMBIO= ");
      Serial.print(palabra1);
      Serial.print(palabra2);
      Serial.println(palabra3);
      codigo[2]=0;
      cont=cont+1;
      } 
      }
  
  }
  
  
 
