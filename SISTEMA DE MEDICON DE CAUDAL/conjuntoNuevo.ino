#include <SPI.h>    // incluye libreria interfaz SPI
#include <SD.h>     // incluye libreria para tarjetas SD
#include <LiquidCrystal_I2C.h> //DESCARGAR LIBRERÍA:https://github.com/ELECTROALL/Codigos-arduino/blob/master/LiquidCrystal_I2C.zip
#include <Keypad.h>; // Con esta linea llamamos a la librería Keypad para que arduino reconozca el teclado
#include <SoftwareSerial.h>
//#include define miBT Serial1
#include <String.h>

#define SSpin 53    // Slave Select en pin digital 10
#define sensorPin A0 //distancia
#define ANALOGPILA 1 //lectura de bateria


float analogValor = 0;
float voltaje = 0;
char contrasena[]="2222"; // En esta linea creamos la constante de cadena llamada contraseña (el numero 2222 puede ser cambiado)
char codigo[5];// Creamos otra constante, en esta se guardaran los caracteres que presionemos en nuestro teclado matricial 4x4
char cambio[5];
char conjunto[2];
char palabra1;
char palabra2;
char palabra3;
int digito1=0;
int digito2=0;
int digitoreinicio=0;
int minuto=60000;
int contadorMinuto=1;

int x=0;
int y=0;
int cont=0; // Esta es una variable que nos servirá más adelante
int distance = 0;
float ca=0;
unsigned long tiempo = 0;
//unsigned long tiempo = millis();
unsigned long reinicio=600000;//600000;
int crono=1;
int analogica=0; // dato que se va a neviar a la pagina ( se cambia por el dato del sensor)

const byte rowsCount = 4;
const byte columsCount = 3;

byte pinesFilas[] = {9, 10, 11, 12};
byte pinesColumnas[] = {2, 3, 4};

SoftwareSerial miBT(0, 1);  // pin 10 como RX, pin 11 como TX
//SoftwareSerial Serial1(18, 19);//Configuración de los pines serial por software ( modulo sim)
File archivo;     // objeto archivo del tipo File

char keys[rowsCount][columsCount] = {
  { '1', '2', '3', },
  { '4', '5', '6', },
  { '7', '8', '9', },
  { '*', '0', '#', }
};


Keypad customKeypad = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, rowsCount, columsCount);

 //En este punto el teclado se inicia y realiza el mapeo de sus teclas con respecto a la matriz colocada arriba

LiquidCrystal_I2C lcd(0x3f,16,2); // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2) 


void read_battery(){
  

 //  analogValor = analogRead(ANALOGPILA);
 
  // Obtenemos el voltaje
//  voltaje = 0.0048 * analogValor;
  //Serial.print("Voltaje: ");
  //Serial.println(voltaje);
  //lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print("Voltaje");
  //lcd.setCursor(0,1);
//  lcd.print(voltaje);
  
}

void read_sensor() {
 distance = (620-(analogRead(sensorPin) * 5))*10;
 ca = ((distance*distance*0.0658)+(distance*0.0271)-0.303);
// delay(1000);
}
void print_data() {
 Serial.print("distance = ");
 Serial.print(distance);
 Serial.println(" L/seg");
}
void escritura() {
  
  if (archivo) {  
    //for (int i=1; i < 100; i++){     // bucle repite 30 veces

      read_sensor();
  

      archivo.print(ca);       // escribe en tarjeta el valor del indice
      archivo.print(" ");     // escribe en tarjeta una coma
      archivo.print("L/seg");
      archivo.print("--- minuto");
      archivo.println(tiempo/60000);// escribe en tarjeta el valor de humedad y salto de linea

      //Serial.print(distance);        // escribe en monitor el valor del indice
      //Serial.print(" ");      // escribe en monitor una coma
      //Serial.println("mm");      // escribe en monitor el valor de humedad y salto de linea

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" Dato guardado ");
      lcd.setCursor(0,1);
      lcd.print(" correctamente ");
      delay(3000);

      //delay(1000);        // demora de 1 segundo
      
    //archivo.close();        // cierre de archivo
    Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie
    //return;
  }
  else {
    Serial.println("error en apertura de datos.txt"); // texto de falla en apertura de archivo
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ErrorMicroSD");
    delay(3000);
    
  }return;
}


void setup() {
  Serial1.begin(115200);//Arduino se comunica con el SIM900 a una velocidad de 19200bps   
  miBT.begin(9600);
  Serial.begin(9600);   // inicializa monitor serie a 9600 bps
  Serial.println("ATZ");
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bienvenido"); 
  lcd.setCursor (0,1);
  lcd.print("Pulse un comando");
  Serial.println("iniciando pantalla");
  delay(3000);

  Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("FAllO SD");
    delay(3000);
    //return;         // se sale del setup() para finalizar el programa
  }
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("datos.txt", FILE_WRITE); // apertura para lectura/escritura de archivo datos.txt

}



void loop() {
 {
 read_sensor();
 char customKey = customKeypad.getKey(); //esta linea indica que el carácter presionado se guardara en la variable customKey

//unsigned long reinicio=30000;
//char palabra1;
//char palabra2;
//char palabra3;
//int x=0;
//int y=0;
//int cont=0;
//int crono=1;


  if(millis()-tiempo> reinicio){
    //TCNT0=0;
    tiempo = millis();
    //lcd.backlight();
    escritura();

    Sim800();
    crono=crono+1;

//    if(millis()>minuto*contadorMinuto){
//      contadorMinuto=contadorMinuto+1;
//      Serial.println(contadorMinuto);
//    }
    //reinicio=(digito1*600000+digito2*60000);//600000;
    //reinicio=reinicio*crono;
    //delay(3000);
  }


 if(customKey==NO_KEY && y!=1){     
      //Serial.println("codigo 1");
      lcd.noBacklight();
      read_sensor();
      print_data();
      //lcd.clear();
      //lcd.setCursor(0,0);
      //lcd.print("Modo transmision");
      //delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(ca); 
      lcd.setCursor(5,0);
      lcd.print("mL/seg");
      cont=0;
      //codigo[0]='7';
      //delay(3000);
 }
        
 if (customKey != NO_KEY) //Con este ciclo preguntamos si se presiono una tecla, si se presiono entonce el ciclo continua
 {
 lcd.backlight(); 
 y=1; 
 codigo[cont]=customKey; //se guardaran los caracteres presionados en codigo[cont]
 Serial.print(codigo[cont]); //Se imprime en nuestro monitor serial lo que este guardado en codigo[cont]
 Serial.print(',');
 Serial.println(cont);


    if(codigo[0]=='1'){

      Serial.println("codigo 1");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("presione *"); 
      cont=cont+1;
      codigo[0]=0;
      delay(3000);
    }
        
    if(codigo[1]=='*'){
      Serial.println("Cambio tiempo de muestreo");
            lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("pulse un digito"); 
      x=1;
      codigo[1]=0;
      cont=cont+1;

     }

    if(codigo[2]!= NO_KEY && x==1){
      Serial.println("Para terminar pulse *");
      Serial.println("o escriba un segundo numero");
            lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Para finalizar"); 
      lcd.setCursor(0,1);
      lcd.print("Pulse *");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("o pulse un");
      lcd.setCursor(0,1);
      lcd.print("digito mas");
      palabra1=codigo[2];
      digito1=String(palabra1).toInt();
      digito2=0;
      codigo[2]=0;
      x=2;
      cont=cont+1;
      }

    if(codigo[3]!= NO_KEY && x==2 && codigo[3]=='*'){
      Serial.print("AT+TDC=");
      Serial.print(digito1*60000);
      Serial.println(" milisegundos");
      //Serial.print(
            lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Tiempo de envio"); 
      lcd.setCursor(0,1);
      lcd.print("Cambiado a ");
      delay(2000);
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(digito1);
      lcd.setCursor(3,0);
      lcd.print("minutos");  
      //palabra2=codigo[3];
      codigo[3]=0;
      //cont=cont+1;
      //x=3;
      y=0;
      reinicio=(digito1*60000);
      delay(3000);
      digito2=digito1;
      digito1=0;
      Serial.println("ATZ");
      }      


      if(codigo[3]!= NO_KEY && x==2 && codigo[3]!='*'){
        palabra2=codigo[3];
        digito2=String(palabra2).toInt();
        
      Serial.print("AT+TDC=");
      Serial.print((digito1*600000)+(digito2*60000));
      reinicio=((digito1*600000)+(digito2*60000));
     
            lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Tiempo de envio"); 
      lcd.setCursor(0,1);
      lcd.print("Cambiado a");
      delay(2000); 
      //palabra2=codigo[3];
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(digito1);
      lcd.setCursor(1,0);
      lcd.print(digito2);
      lcd.setCursor(3,0);
      lcd.print("minutos");
      codigo[3]=0;
     // cont=cont+1;
      //x=3;
      y=0;
      delay(3000);
      Serial.println("ATZ");
      }      

    if(codigo[4]!= NO_KEY && x==3){
      Serial.println("pulse un * ");
            lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("pulse un *"); 
      palabra3=codigo[4];
      codigo[4]=0;
      cont=cont+1;
      }

     if(codigo[5]== '*'){
      Serial.print("AT+CAMBIO= ");
      //Serial.print(palabra1);
      //Serial.print(palabra2);
      //Serial.print(palabra3);
      //Serial.print("0");
      //Serial.print("0");
      //Serial.print("0");
      conjunto[0]=palabra1;
      conjunto[1]=palabra2;
      conjunto[2]=palabra3;
      conjunto[3]='0';
      conjunto[4]='0';
      conjunto[5]='0';
      

            lcd.clear();
      lcd.setCursor( 0,0);
      lcd.print("Muestreo a");
      lcd.setCursor(0,1);
      lcd.print(conjunto);
      //lcd.print(palabra1);
      //lcd.setCursor(1,1);
      //lcd.print(palabra2);
      //lcd.setCursor(2,1);
      //lcd.print(palabra3);
      //lcd.setCursor(3,1);
      //lcd.print("0");
      //lcd.setCursor(4,1);
      //lcd.print("0");
      //lcd.setCursor(5,1);
      //lcd.print("0");
      lcd.setCursor(7,1);
      lcd.print(" seg");
      Serial.println(conjunto); 
      delay(3000);
      codigo[2]=0;
      cont=0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("pulse un comando");
      }


     if(codigo[0]=='4'){
      read_sensor();
      Serial.println("codigo 1");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Caudal");
      lcd.setCursor(0,1);
      lcd.print(ca);
      lcd.setCursor(6,1);
      lcd.print("mL/seg"); 
      //cont=cont+1;
      cont=0;
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("pulse un comando");
      }

       if(codigo[0]=='7'){
      //read_sensor();
      Serial.println("codigo 1");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Modo transmision");
      cont=0;
      delay(3000);
      y=0;
      }

      if(codigo[0]=='*'){
        read_battery();
        delay(3000);
        cont=0;
        y=0;
      }
      if(codigo[0]=='2'){
        escritura();
        delay(3000);
        cont=0;
        y=0;
      }
      if(cont<1 && codigo[0]!='1' && codigo[0]!='2' && codigo[0]!='4' && codigo[0]!='5' && codigo[0]!='7' && codigo[0]!='*' ){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("comando");
        lcd.setCursor(0,1);
        lcd.print("invalido");
        y=0;
        delay(3000);
        }

      if(codigo[0]=='5'){
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Tiempo de envio");
        lcd.setCursor(0,1);
        lcd.print(reinicio/60000);
        lcd.setCursor(3,1);
        lcd.print("minutos");
        y=0;
        delay(3000);
        
        }
       
  }

 
 }
 }

 void Sim800(){ 
//lcd.backlight();  
lcd.clear();
lcd.setCursor(1,0);
lcd.println("Subiendo Datos");
lcd.setCursor(1,1);
lcd.println("Thing Speak");
  
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

void grados() {//Función para la lectura del sensor de temepratura
  analogica=ca;
  Serial.print("El valor de la senal analogica 0 es: ");
  Serial.println(analogica);//Imprime la temperatura
}
