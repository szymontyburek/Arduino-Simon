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
  // randNumber = random(2);
  // if(randNumber == 0) {
  //   digitalWrite(grBtnOutp, HIGH);
  //   delay(1000);
  //   digitalWrite(grBtnOutp, LOW);
  // }
  // else {
  //   digitalWrite(redBtnOutp, HIGH);
  //   delay(1000);
  //   digitalWrite(redBtnOutp, LOW);
  // }
  // delay(500);
  // //random LED BLINK logic

  //  // Wait for user input
  // while (Serial.available() == 0) {
  //   // Do nothing (wait until input is available)
  // }
  // userInput = Serial.parseInt();

  if(digitalRead(grBtnInp) == HIGH) {
    digitalWrite(grBtnOutp, HIGH);
    delay(500);
    digitalWrite(grBtnOutp, LOW);
  }
  else if(digitalRead(redBtnInp) == HIGH) {
    digitalWrite(redBtnOutp, HIGH);
    delay(500);
    digitalWrite(redBtnOutp, LOW);
  }
}

void btnToLEDmap(int inputPin, int outputPin) {
  if(digitalRead(inputPin) == HIGH) digitalWrite(outputPin, HIGH);
  else digitalWrite(outputPin, LOW);
}
