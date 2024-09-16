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

  delay(1000);
}

void loop() {
  int score = 0;
  String* LEDchoices = new String[score + 1];

  while (2 < 3) {
    String LEDchoice;

    //random LED BLINK logic
    randNumber = random(2);
    if(randNumber == 0) {
      blink(grBtnOutp, 600);
      LEDchoice = "green";
    }
    else {
      blink(redBtnOutp, 600);
      LEDchoice = "red";
    }
    //random LED BLINK logic

    if(readBtnClick(LEDchoice)) {
      score++;

      //expand LEDchoices by 1 element
      int newLength = score + 1;
      String* LEDchoicesTmp = new String[newLength];

      for(int i = 0; i < newLength - 1; i++) LEDchoicesTmp[i] = LEDchoices[i];

      LEDchoicesTmp[newLength - 1] = LEDchoice;

      delete[] LEDchoices;
      LEDchoices = LEDchoicesTmp;

      //print elements of LEDchoices
      for(int i = 0; i < newLength; i++) Serial.println(LEDchoices[i]);
    }
    else score = 0;
    
    Serial.print("Score: ");
    Serial.println(score);

    delay(500);
  }
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