long randNumber;
int userInput;

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
  // //random LED BLINK logic
  randNumber = random(2);
  if(randNumber == 0) {
    blink(grBtnOutp);
  }
  else {
    blink(redBtnOutp);
  }
  delay(500);
  // //random LED BLINK logic

  // if(digitalRead(grBtnInp) == HIGH) {
  //   digitalWrite(grBtnOutp, HIGH);
  //   delay(500);
  //   digitalWrite(grBtnOutp, LOW);
  // }
  // else if(digitalRead(redBtnInp) == HIGH) {
  //   digitalWrite(redBtnOutp, HIGH);
  //   delay(500);
  //   digitalWrite(redBtnOutp, LOW);
  // }
}

void blink(int outputPin) {
  digitalWrite(outputPin, HIGH);
  delay(1000);
  digitalWrite(outputPin, LOW);
}
