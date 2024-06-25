#include <Wire.h>
#include <LiquidCrystal.h>

const int pinRojo = 13;
const int pinVerde = 11;
const int pinAzul = 12;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
String input = ""; 
String result = ""; 

void setup() {
  Wire.begin(2);
  Wire.onReceive(receiveEvent);
  lcd.begin(16, 2);
  
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);

  
  digitalWrite(pinRojo, HIGH);
  digitalWrite(pinVerde, HIGH);
  digitalWrite(pinAzul, LOW);
  delay(1000);
  
  
  digitalWrite(pinRojo, LOW);
  digitalWrite(pinVerde, LOW);
  digitalWrite(pinAzul, LOW);
  
  lcd.clear();
}

void loop() {
  delay(100); 
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    char c = Wire.read();
    
   
    digitalWrite(pinRojo, HIGH);
    delay(100);
    digitalWrite(pinRojo, LOW);
    
    if (c == '=') {
      result = calculate(input); 
      lcd.setCursor(0, 1); 
      lcd.print(result); 
      
      
      digitalWrite(pinVerde, HIGH);
      digitalWrite(pinAzul, HIGH);
    } else if (c == 'C') {
      
      input = "";
      result = "";
      lcd.clear();
      
      
      digitalWrite(pinVerde, LOW);
      digitalWrite(pinAzul, LOW);
    } else {
      input += c; 
      lcd.setCursor(0, 0); 
      lcd.print(input); 
    }
  }
}

String calculate(String expr) {
  int len = expr.length();
  char oper = 0;
  String operand1Str = "", operand2Str = "";
  bool firstOperand = true;
  
  for (int i = 0; i < len; i++) {
    char c = expr[i];
    if (isDigit(c)) {
      if (firstOperand) {
        operand1Str += c;
      } else {
        operand2Str += c;
      }
    } else {
      if (c == '+' || c == '-' || c == '*' || c == '/') {
        oper = c;
        firstOperand = false;
      }
    }
  }
  
  float operand1 = operand1Str.toFloat();
  float operand2 = operand2Str.toFloat();
  float result = 0;
  String resultStr = "";

  switch (oper) {
    case '+': 
      result = operand1 + operand2; 
      resultStr = String((int)result); 
      break;
    case '-': 
      result = operand1 - operand2; 
      resultStr = String((int)result); 
      break;
    case '*': 
      result = operand1 * operand2; 
      resultStr = String((int)result); 
      break;
    case '/': 
      if (operand2 != 0) {
        result = operand1 / operand2; 
        resultStr = String(result, 2); 
      } else {
        resultStr = "Err"; 
      }
      break;
  }
  return resultStr;
}


