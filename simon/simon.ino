#include <Hashtable.h>
#include <Arduino.h>

long randNumber;
int highScore;
int score;

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
  score = 0;
  int* LEDchoices = new int[1];
  Hashtable<String, int> colorToPin;
  colorToPin.put("green", grBtnOutp);
  colorToPin.put("red", redBtnOutp);

  while (true) {
    int LEDchoice;

    //random LED BLINK logic
    randNumber = random(2);
    if(randNumber == 0) LEDchoice = grBtnOutp;
    else LEDchoice = redBtnOutp;
    //random LED BLINK logic

    //Current game LEDs are lit
    LEDchoices[score] = LEDchoice;

    for(int i = 0; i < score + 1; i++) 
    {
      blink(LEDchoices[i], 600);
    }
    //Current game LEDs are lit

    //User response
    for(int i = 0; i < score + 1; i++) 
    {
      // Wait until button is clicked is available
      while (digitalRead(grBtnInp) == LOW && digitalRead(redBtnInp) == LOW) {
        // Do nothing, just wait
      }
        
      if(digitalRead(grBtnInp) == HIGH)
      {
        blink(grBtnOutp, 300);
        if(LEDchoices[i] != grBtnOutp)
        {
          gameOver();
          return;
        }         
      }
      else  
      {
        blink(redBtnOutp, 300);
        if(LEDchoices[i] != redBtnOutp) 
        {
          gameOver();
          return;
        } 
      }
        
      while (digitalRead(grBtnInp) == HIGH || digitalRead(redBtnInp) == HIGH) {
        // Do nothing, just wait
      }
    }
    //User response
    
    score++;
    reportScore();

    //modify array by dynamically allocating memory
    int newLength = score + 1;
    int* LEDchoicesTmp = new int[newLength];

    for(int i = 0; i < newLength - 1; i++) LEDchoicesTmp[i] = LEDchoices[i];

    LEDchoicesTmp[newLength - 1] = LEDchoice;

    delete[] LEDchoices;
    LEDchoices = LEDchoicesTmp;
    //modify array by dynamically allocating memory
  }
}

void gameOver() {
    reportScore();

    for(int i = 0; i < 3; i++){
    digitalWrite(grBtnOutp, HIGH);
    digitalWrite(redBtnOutp, HIGH);
    delay(200);
    digitalWrite(grBtnOutp, LOW);
    digitalWrite(redBtnOutp, LOW);
    delay(200);
  }
  delay(1000);
}

void reportScore() {
  Serial.print("Score: ");
  Serial.println(score);

  if(score > highScore) highScore = score;

  Serial.print("Highest: ");
  Serial.println(highScore);
}

void blink(int outputPin, int delayInt) {
  digitalWrite(outputPin, HIGH);
  delay(delayInt);
  digitalWrite(outputPin, LOW);
  delay(delayInt);
}