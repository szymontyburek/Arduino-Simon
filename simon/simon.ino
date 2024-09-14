int LEDout = 12;
int btn1In = 2;
int btn2In = 7;

void setup() {
    pinMode(LEDout, OUTPUT);
    pinMode(btn1In, INPUT);
    pinMode(btn2In, INPUT);
}

void loop() {
  if(digitalRead(btn1In) == HIGH || digitalRead(btn2In) == HIGH) {
    digitalWrite(LEDout, HIGH);
  }
  else {
    digitalWrite(LEDout, LOW);
  }
}
