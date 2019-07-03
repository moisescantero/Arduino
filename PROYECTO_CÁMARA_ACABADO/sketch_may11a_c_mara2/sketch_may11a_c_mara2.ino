
//Librería que permite establecer comunicación serie en otros pins.
#include <SoftwareSerial.h>

//Aquí conectamos los pins RXD,TDX del módulo Bluetooth.
SoftwareSerial BT(10,11); //10 RX y 11 TX.



//Declaramos las patillas que vamos a usar como int:
int compresor= 2; int solenoide= 3; int evaporador= 4;
int presbaja= 5; int presalta= 6; int desescarche= 7;
int puerta= 8; const int sensorpin1= 0; int lectura= 0;


//Dentro de void setup se repite solo una vez y cada vez que le
//demos al reset.
void setup() {
  //Declaramos las patillas del arduino como entradas y pullup es
  //para poner la resistencia interna de cada entrada del arduino
  //a tensión positiva.
  pinMode(compresor, INPUT_PULLUP); 
  pinMode(solenoide, INPUT_PULLUP);
  pinMode(evaporador, INPUT_PULLUP); 
  pinMode(presbaja, INPUT_PULLUP);
  pinMode(presalta, INPUT_PULLUP); 
  pinMode(desescarche, INPUT_PULLUP);
  pinMode(puerta, INPUT_PULLUP); 
  pinMode(sensorpin1, INPUT_PULLUP);
  //Iniciamos la comunicación serie con el PC a 
  //9600 bits por segundo de velocidad.
  Serial.begin(9600);  
  //Iniciamos el módulo bluetooth a 9600 bits de velocidad.
  BT.begin(9600);
  
}

void loop() {
  
  if(Serial.available()>0)
  {
   if(Serial.read()=='A')
   { 
  //Las órdenes aquí contenidas se repiten en bucle
  //Declaramos las variables como entradas digitales
  //leyendo por el pin correspondiente
  int compresor= digitalRead(2); int solenoide= digitalRead(3);
  int evaporador= digitalRead(4); int presbaja= digitalRead(5);
  int presalta= digitalRead(6); int desescarche= digitalRead(7);
  int puerta= digitalRead(8); int sensorpin1= analogRead(0);
  
  int lectura=Serial.read();
  
  //Aquí comunicamos entre el módulo bluetooth y los pins 
  //correspondientes del arduino.
    if(BT.available())//Si el módulo bluetooth está habilitado.
   {
    //Los pins del arduino escriben el módulo bluetooth lee.
    Serial.write(BT.read());
   }
  if(Serial.available())//Si la comunicación serie está habilitada.
   {
    //El módulo Blue tooth escribe y la comunicación serie lee.
    BT.write(Serial.read());
   }
  
  //convertimos los valores de la resistencia a grados celsius.
  sensorpin1 = map(sensorpin1, 0, 1023, -30, +50);
  
  //Aquí colocamos los imprimir pantalla para que en el monitor
  //serie se muestren los resultados de todas las variables.
  Serial.print(compresor); Serial.print(",");
  Serial.print(solenoide); Serial.print(",");
  Serial.print(evaporador); Serial.print(",");
  Serial.print(presbaja); Serial.print(",");
  Serial.print(presalta); Serial.print(",");
  Serial.print(desescarche); Serial.print(",");
  Serial.print(puerta); Serial.print(",");
  Serial.print(sensorpin1);
  Serial.println();
  delay(2000);
   } 
  }

}

