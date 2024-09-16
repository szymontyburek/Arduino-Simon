#include <Hashtable.h>
#include <Arduino.h>

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
  String* LEDchoices = new String[1];
  Hashtable<String, int> colorToPin;
  colorToPin.put("green", grBtnOutp);
  colorToPin.put("red", redBtnOutp);

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

    if(validChoice(LEDchoice)) {
      score++;

      //expand LEDchoices by 1 element
      int newLength = score + 1;
      String* LEDchoicesTmp = new String[newLength];

      for(int i = 0; i < newLength - 1; i++) LEDchoicesTmp[i] = LEDchoices[i];

      LEDchoicesTmp[newLength - 1] = LEDchoice;

      delete[] LEDchoices;
      LEDchoices = LEDchoicesTmp;

      for(int i = 1; i < newLength; i++) //for some unknown reason, there exists an extra element. That is why i equal 1, and not 0, at the start of the for loop
      {
        Serial.println(LEDchoices[i]);  
        blink(colorToPin.getElement(LEDchoices[i]), 600);
      }
    }
    else score = 0;
    
    Serial.print("Score: ");
    Serial.println(score);
  }
}

void blink(int outputPin, int delayInt) {
  digitalWrite(outputPin, HIGH);
  delay(delayInt);
  digitalWrite(outputPin, LOW);
  delay(delayInt);
}

bool validChoice(String LEDchosen) {
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
  
  return correct;
}