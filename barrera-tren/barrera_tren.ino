//www.elegoo.com
//2018.12.19
#include <Servo.h>
/* After including the corresponding libraries,
   we can use the "class" like "Servo" created by the developer for us.
   We can use the functions and variables created in the libraries by creating 
   objects like the following "myservo" to refer to the members in ".".*/

Servo gate;
// PIN control
int servo_pin = 9;
int red_led = 10;
int yellow_led = 11;
int green_led = 12;
int button = 13;

// Servo positions
int gate_closed = 140;
int gate_opened = 40;

// Variables
int buttonState = LOW;
int gateState = HIGH;

//it created an object called myservo.
/*  you can see Servo as a complex date type(Including functions and various data types)
    and see myservo as variables.               */

void setup(){
  /*"attach" and "write" are both functions,
     and they are members contained in the complex structure of "Servo". 
     We can only use them if we create the object "myservo" for the complex structure of "Servo".
  */
  gate.attach(servo_pin);//connect pin 9 with the control line(the middle line of Servo) 
  gate.write(gate_opened);// center servo at opened position
  pinMode(button, INPUT);
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  
  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, HIGH);
} 

void loop(){
  buttonState = digitalRead(button);
  if(buttonState == HIGH) {
    if(gateState == HIGH) {
      closeGate();
      gateState = LOW;
    } else {
      openGate();
      gateState = HIGH;
    }
  }
}

void openGate() {
    digitalWrite(red_led, LOW);
    digitalWrite(yellow_led, HIGH);
    digitalWrite(green_led, LOW);
    for (int pos = gate_closed; pos >= gate_opened; pos-=1) {
      gate.write(pos);
      delay(15);
    }
    digitalWrite(red_led, LOW);
    digitalWrite(yellow_led, LOW);
    digitalWrite(green_led, HIGH);
}

void closeGate() {
    digitalWrite(red_led, LOW);
    digitalWrite(yellow_led, HIGH);
    digitalWrite(green_led, LOW);
    for (int pos = gate_opened; pos <= gate_closed; pos+=1) {
      gate.write(pos);
      delay(15);
    }
    digitalWrite(red_led, HIGH);
    digitalWrite(yellow_led, LOW);
    digitalWrite(green_led, LOW);
}
