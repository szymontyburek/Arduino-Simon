// void loop() {

// }
long randNumber;
int LEDchoices[1];

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
  delay(500);
  //random LED BLINK logic

  Serial.println(readBtnClick());
}

void blink(int outputPin, int delayInt) {
  digitalWrite(outputPin, HIGH);
  delay(delayInt);
  digitalWrite(outputPin, LOW);
}

String readBtnClick() {
  // Wait until green button is clicked is available
  while (digitalRead(grBtnInp) == LOW && digitalRead(redBtnInp) == LOW) {
    // Do nothing, just wait
  }

  String message;
  if(digitalRead(grBtnInp) == HIGH)
    {
      blink(grBtnOutp, 100);
      if(LEDchoices[0] == "green") Serial.println("correct!");
      else Serial.println("incorrect :(");
    }
  else  {
    blink(redBtnOutp, 100);
      if(LEDchoices[0] == "red") Serial.println("correct!");
      else Serial.println("incorrect :(");
  }
  
  while (digitalRead(grBtnInp) == HIGH || digitalRead(redBtnInp) == HIGH) {
    // Do nothing, just wait
  }
  
  delay(500);
  return message;
}