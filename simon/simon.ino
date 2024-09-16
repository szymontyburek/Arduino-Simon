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

  while (true) {
    String LEDchoice;

    //random LED BLINK logic
    randNumber = random(2);
    if(randNumber == 0) {
      LEDchoice = "green";
    }
    else {
      LEDchoice = "red";
    }
    //random LED BLINK logic

    LEDchoices[score] = LEDchoice;

      for(int i = 0; i < score + 1; i++) 
      {
        Serial.println(LEDchoices[i]);  
        blink(colorToPin.getElement(LEDchoices[i]), 600);
      }

      for(int i = 0; i < score + 1; i++) 
      {
        // Wait until button is clicked is available
        while (digitalRead(grBtnInp) == LOW && digitalRead(redBtnInp) == LOW) {
          // Do nothing, just wait
        }

        if(digitalRead(grBtnInp) == HIGH)
          {
            blink(grBtnOutp, 300);
            if(LEDchoices[i] == "green") Serial.println("Good");
            else Serial.println("Bad");
          }
        else  {
          blink(redBtnOutp, 300);
          if(LEDchoices[i] == "red") Serial.println("Good");
          else Serial.println("Bad");
        }
        
        while (digitalRead(grBtnInp) == HIGH || digitalRead(redBtnInp) == HIGH) {
          // Do nothing, just wait
        }
      }

            //expand LEDchoices by 1 element
      score++;
      int newLength = score + 1;
      String* LEDchoicesTmp = new String[newLength];

      for(int i = 0; i < newLength - 1; i++) LEDchoicesTmp[i] = LEDchoices[i];

      LEDchoicesTmp[newLength - 1] = LEDchoice;

      delete[] LEDchoices;
      LEDchoices = LEDchoicesTmp;
      //expand LEDchoices by 1 element


    // if(validChoice(LEDchoice)) {


    // }
    // else break;
    
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