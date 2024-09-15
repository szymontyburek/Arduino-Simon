// void loop() {

// }
long randNumber;

int grBtnInp = 2;
int grBtnOutp = 8;

int redBtnInp = 7;
int redBtnOutp = 12;

void setup() {
  Serial.begin(9600);
  pinMode(grBtnOutp, OUTPUT);
  pinMode(redBtnOutp, OUTPUT);
  pinMode(grBtnInp, INPUT);
  pinMode(redBtnInp, INPUT);
}

void loop() {
  String LEDchoices[1];

  //random LED BLINK logic
  randNumber = random(2);
  if(randNumber == 0) {
    blink(grBtnOutp, 300);
    LEDchoices[0] = "green";
  }
  else {
    blink(redBtnOutp, 300);
    LEDchoices[0] = "red";
  }
  //random LED BLINK logic

  int score = 0;
  if(readBtnClick(LEDchoices[0])) score++;
  Serial.print("Score: ");
  Serial.println(score);
}

void blink(int outputPin, int delayInt) {
  digitalWrite(outputPin, HIGH);
  delay(delayInt);
  digitalWrite(outputPin, LOW);
}

bool readBtnClick(String LEDchosen) {
  // Wait until green button is clicked is available
  while (digitalRead(grBtnInp) == LOW && digitalRead(redBtnInp) == LOW) {
    // Do nothing, just wait
  }

  bool correct = false;
  if(digitalRead(grBtnInp) == HIGH)
    {
      blink(grBtnOutp, 300);
      if(LEDchosen == "green") correct = true;
    }
  else  {
    blink(redBtnOutp, 300);
      if(LEDchosen == "red") correct = true;
  }
  
  while (digitalRead(grBtnInp) == HIGH || digitalRead(redBtnInp) == HIGH) {
    // Do nothing, just wait
  }
  
  delay(500);
  return correct;
}