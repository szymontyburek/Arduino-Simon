int output = 12;
int input = 2;

void setup() {
    pinMode(output, OUTPUT);
    pinMode(input, INPUT);
}

void loop() {
  if(digitalRead(input) == HIGH) { //read voltage of pin 2
    digitalWrite(output, HIGH);
  }
  else {
    digitalWrite(output, LOW);
  }
}
