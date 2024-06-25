#include <Wire.h>
#include <Keypad.h>

#define filas_teclado 4
#define columnas_teclado 4
char TECLA;

byte filas[4] = {11, 10, 9, 8}; 
byte columnas[4] = {7, 6, 5, 4}; 

char teclas[filas_teclado][columnas_teclado]={
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}};

Keypad teclado(makeKeymap(teclas), filas, columnas, filas_teclado, columnas_teclado);

void setup() {
  Wire.begin();
  Serial.begin(9600); 
}

void loop() {
  TECLA = teclado.getKey();
  
  if (TECLA) { 
    Wire.beginTransmission(2);  
    Wire.write(TECLA);
    Wire.endTransmission();
    delay(100); 
  }
}
