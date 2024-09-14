long randNumber;

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
  //random LED BLINK logic
  randNumber = random(2);
  if(randNumber == 0) {
    digitalWrite(grBtnOutp, HIGH);
    delay(1000);
    digitalWrite(grBtnOutp, LOW);
  }
  else {
    digitalWrite(redBtnOutp, HIGH);
    delay(1000);
    digitalWrite(redBtnOutp, LOW);
  }
  delay(500);
  //random LED BLINK logic

  btnToLEDmap(grBtnInp, grBtnOutp);
  btnToLEDmap(redBtnInp, redBtnOutp);
}

void btnToLEDmap(int inputPin, int outputPin) {
  if(digitalRead(inputPin) == HIGH) digitalWrite(outputPin, HIGH);
  else digitalWrite(outputPin, LOW);
}
