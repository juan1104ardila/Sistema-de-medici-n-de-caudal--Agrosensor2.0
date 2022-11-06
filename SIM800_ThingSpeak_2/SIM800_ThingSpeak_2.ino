#include <SoftwareSerial.h>
#include <String.h>
//SoftwareSerial Serial1(19, 18);//Configuración de los pines serial por software
int analogica=0;

void setup()
{
Serial1.begin(115200);//Arduino se comunica con el SIM900 a una velocidad de 19200bps   
Serial.begin(9600);//Velocidad del puerto serial de arduino
//Encendido del módulo por sofware
// Estas 3 lineas son necesarias para el modulo SIM900 no para el SIM800
//digitalWrite(7, HIGH);
//delay(1000);
//digitalWrite(7, LOW);
Serial.println("Empezando");
delay(20000);//Tiempo prudencial para el escudo inicie sesión de red con tu operador
}

void loop(){  
comandosAT();//Llama a la función comandosAT  
if(Serial1.available())//Verificamos si hay datos disponibles desde el SIM900
Serial.write(Serial1.read());//Escribir datos
}

void comandosAT(){
Serial1.println("AT+CIPSTATUS");//Consultar el estado actual de la conexión
delay(2000);
Serial1.println("AT+CIPMUX=0");//comando configura el dispositivo para una conexión IP única o múltiple 0=única
delay(3000);
mostrarDatosSeriales();
Serial1.println("AT+CSTT=\"web.colombiamovil.com.co\",\"Tigo Web\",\"\"");//comando configura el APN, nombre de usuario y contraseña."gprs.movistar.com.ar","wap","wap"->Movistar Arg.
delay(1000);
mostrarDatosSeriales();
Serial1.println("AT+CIICR");//REALIZAR UNA CONEXIÓN INALÁMBRICA CON GPRS O CSD
delay(3000);
mostrarDatosSeriales();
Serial1.println("AT+CIFSR");// Obtenemos nuestra IP local
delay(2000);
mostrarDatosSeriales();
Serial1.println("AT+CIPSPRT=0");//Establece un indicador '>' al enviar datos
grados();
delay(3000);
mostrarDatosSeriales();
Serial1.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//Indicamos el tipo de conexión, url o dirección IP y puerto al que realizamos la conexión
delay(6000);
mostrarDatosSeriales();
Serial1.println("AT+CIPSEND");//ENVÍA DATOS A TRAVÉS DE una CONEXIÓN TCP O UDP
delay(4000);
mostrarDatosSeriales();
String datos="GET https://api.thingspeak.com/update?api_key=VMKWQF2XCXIZNHAA&field1=" + String(analogica);
Serial1.println(datos);//Envía datos al servidor remoto
delay(4000);
mostrarDatosSeriales();
Serial1.println((char)26);
delay(5000);//Ahora esperaremos una respuesta pero esto va a depender de las condiones de la red y este valor quizá debamos modificarlo dependiendo de las condiciones de la red
Serial1.println();
mostrarDatosSeriales();
Serial1.println("AT+CIPSHUT");//Cierra la conexión(Desactiva el contexto GPRS PDP)
delay(5000);
mostrarDatosSeriales();
} 

void mostrarDatosSeriales()//Muestra los datos que va entregando el sim900
{
while(Serial1.available()!=0)
Serial.write(Serial1.read());
}

void grados(){//Función para la lectura del sensor de temepratura
  analogica=analogica+1;
  Serial.print("El valor de la senal analogica 0 es: ");
  Serial.println(analogica);//Imprime la temperatura
}
