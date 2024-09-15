// long randNumber;
// int userInput;

// int grBtnInp = 2;
// int grBtnOutp = 8;

// int redBtnInp = 7;
// int redBtnOutp = 12;

// void setup() {
//     pinMode(grBtnOutp, OUTPUT);
//     pinMode(redBtnOutp, OUTPUT);
//     pinMode(grBtnInp, INPUT);
//     pinMode(redBtnInp, INPUT);
// }

// void loop() {
//   // //random LED BLINK logic
//   // randNumber = random(2);
//   // if(randNumber == 0) {
//   //   blink(grBtnOutp, 1000);
//   // }
//   // else {
//   //   blink(redBtnOutp, 1000);
//   // }
//   // delay(500);
//   // //random LED BLINK logic

//   if(digitalRead(grBtnInp) == HIGH) {
//     blink(grBtnOutp, 50);
//   }
//   else if(digitalRead(redBtnInp) == HIGH) {
//     blink(redBtnOutp, 50);
//   }
// }

// void blink(int outputPin, int delayInt) {
//   digitalWrite(outputPin, HIGH);
//   delay(delayInt);
//   digitalWrite(outputPin, LOW);
// }

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(readUserInput());
}

void blink(int outputPin, int delayInt) {
  digitalWrite(outputPin, HIGH);
  delay(delayInt);
  digitalWrite(outputPin, LOW);
}

String readUserInput() {
  // Wait until green button is clicked is available
  while (digitalRead(2) == LOW ) {
    // Do nothing, just wait
  }

  while (digitalRead(2) == HIGH ) {
    // Do nothing, just wait
  }
  
  return "Green is clicked";
}