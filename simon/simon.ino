int btn1In = 2;
int LEDout1 = 8;

int btn2In = 7;
int LEDout2 = 12;

void setup() {
    pinMode(LEDout1, OUTPUT);
    pinMode(LEDout2, OUTPUT);
    pinMode(btn1In, INPUT);
    pinMode(btn2In, INPUT);
}

void loop() {
  if(digitalRead(btn1In) == HIGH) {
    digitalWrite(LEDout1, HIGH);
  }
  else {
    digitalWrite(LEDout1, LOW);
  }

  if(digitalRead(btn2In) == HIGH) {
    digitalWrite(LEDout2, HIGH);
  }
  else {
    digitalWrite(LEDout2, LOW);
  }
}
