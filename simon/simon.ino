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
  btnToLEDmap(grBtnInp, grBtnOutp);
  btnToLEDmap(redBtnInp, redBtnOutp);
}

void btnToLEDmap(int inputPin, int outputPin) {
  if(digitalRead(inputPin) == HIGH) digitalWrite(outputPin, HIGH);
  else digitalWrite(outputPin, LOW);
}
