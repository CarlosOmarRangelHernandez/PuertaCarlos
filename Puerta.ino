
#include <avr/sleep.h>                    //Se utiliza la libreria sleep

int contacto = 2;                         //variable donde el pin sera el sensor y donde se utilizara la interrrupcion
int led = 13;                             //variable del pin donde se coloca la alarma visual
int contador = 0;                         //Variable para contar cuanta veces ah sido abierta
const int pinBuzzer = 9;

//Metodp para para quitar el modo sleep del arduino
void despertar () {
  sleep_disable();                         //desactiva el modos sleep del arduino
  detachInterrupt (2);                     //Desactiva la interrupcion
}



void setup () {
  Serial.begin(9600);                       //Habilita el puerto serial para enviar informacion a la pc
  pinMode(contacto, INPUT);                 //variable contacto sera de entrada
  pinMode(led, OUTPUT);                     //Variable led sera de salida
  ADCSRA = 0;                               //Minimiza el consumo de energia
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);     //Modo en el que dormira el aduino
  sleep_enable();                           //Pone a dormir el arduino
  attachInterrupt (contacto, despertar, RISING); //Activa la interrupcion con la variable contacto, llama al metodo despertar y enciende los pines
  interrupts ();
}

void loop() {
  if (digitalRead(contacto) == HIGH) {       //Se envia un pulso alto al contacto
    contador++;
    Serial.print(contador);
    Serial.print("\n");
    digitalWrite(led, HIGH);                    //Apaga el led

  } else {
    digitalWrite(led, LOW);                //Enciende el led
    buzer();
  }
}

void buzer() {
  tone(pinBuzzer, 440);
  delay(1000);

  //detener tono durante 500ms
  noTone(pinBuzzer);
  delay(500);

  //generar tono de 523Hz durante 500ms, y detenerlo durante 500ms.
  tone(pinBuzzer, 523, 300);
  delay(500);
}
