// Arduino Mega

const int forwardPin = 8;
const int backwardPin = 12;
const int delayTime = 2000; 
const int but1pin = 2;
const int but2pin =3;
int but1;
int but2;

void setup() {
  // put your setup code here, to run once:
  pinMode(forwardPin, OUTPUT);
  pinMode(backwardPin, OUTPUT);
  pinMode(but1pin, INPUT_PULLUP);
  pinMode(but2pin, INPUT_PULLUP);
}

void loop() {
  but1 = digitalRead(but1pin);
  but2 = digitalRead(but2pin);

  if(but1 == HIGH) {
    digitalWrite(forwardPin,LOW);
  }
  else {
    digitalWrite(forwardPin,HIGH);
  }
  
  if(but2 == HIGH) {
    digitalWrite(backwardPin,LOW);
  }
  else {
    digitalWrite(backwardPin,HIGH);
  }
}
