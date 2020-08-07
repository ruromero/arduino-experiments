#include <LiquidCrystal.h>

int factor1;
int factor2;
int total = 10;
int maxVal = 10;
int aciertos = 0;
int actual = 0;
// PIN control
int brightness_pin = 6;
int ok_pin = 15;
int ko_pin = 16;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  Serial.begin(9600);
  while(!Serial) {
    ;
  }
  
  digitalWrite(brightness_pin, LOW);
  pinMode(brightness_pin, OUTPUT);
  pinMode(ok_pin, OUTPUT);
  pinMode(ko_pin, OUTPUT);
  
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  reset();
  if(actual >= total) {
    imprimeResultado();
    waitForInput();
    actual = 0;
    aciertos = 0;
    reset();
  }
  actual++;
  preparaOperacion();
  imprimePregunta();
  int respuesta = leeRespuesta();
  imprimeRespuesta(respuesta);
  delay(2000);
}

void preparaOperacion() {
  factor1 = (int)random(maxVal + 1);
  factor2 = (int)random(maxVal + 1);
}

int leeRespuesta() {
  int valor = 0;
  String resultado = "";
  while(valor != '\n') {
    valor = Serial.read();
    if(isDigit(valor)) {
      resultado += (char)valor;
    }
  }
  lcd.print(resultado);
  return resultado.toInt(); 
}

void imprimePregunta() {
  String p = "";
  p.concat(actual);
  p.concat(": ");
  p.concat(factor1);
  p.concat(" + ");
  p.concat(factor2);
  p.concat(" = ");
  lcd.print(p);
}

void imprimeResultado() {
  String aciertosTxt = "Aciertos: ";
  aciertosTxt.concat(aciertos);
  aciertosTxt.concat("/");
  aciertosTxt.concat(total);
  lcd.print(aciertosTxt);
}

void imprimeRespuesta(int actual) {
  int expected = getExpected();
  lcd.setCursor(0, 1);
  if(actual == expected) {
    aciertos++;
    lcd.print("Bien");
    digitalWrite(ok_pin, HIGH);
  } else {
    lcd.print("Mal: ");
    lcd.print(expected);
    digitalWrite(ko_pin, HIGH);
  }
}

int getExpected() {
  return factor1 + factor2;
}

void reset() {
  lcd.clear();
  digitalWrite(ok_pin, LOW);
  digitalWrite(ko_pin, LOW);
  lcd.setCursor(0, 0);
}

void waitForInput() {
  int valor = 0;
  while(valor != '\n') {
    valor = Serial.read();
  }
}
