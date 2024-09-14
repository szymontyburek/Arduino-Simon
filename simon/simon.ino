int grBtnInp = 2;
int grBtnOutp = 8;

int redBtnInp = 7;
int redBtnOutp = 12;

void setup() {
    pinMode(grBtnOutp, OUTPUT);
    pinMode(redBtnOutp, OUTPUT);
    pinMode(grBtnInp, INPUT);
    pinMode(redBtnInp, INPUT);
}

void loop() {
  if(digitalRead(grBtnInp) == HIGH) {
    digitalWrite(grBtnOutp, HIGH);
  }
  else {
    digitalWrite(grBtnOutp, LOW);
  }

  if(digitalRead(redBtnInp) == HIGH) {
    digitalWrite(redBtnOutp, HIGH);
  }
  else {
    digitalWrite(redBtnOutp, LOW);
  }
}
