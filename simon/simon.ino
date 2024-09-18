long randNumber;
int highScore;
int score;

int grBtnInp = 2;
int grBtnOutp = 8;

int redBtnInp = 3;
int redBtnOutp = 9;

int ylBtnInp = 4;
int ylBtnOutp = 10;

void setup() {
  Serial.begin(9600);
  pinMode(grBtnInp, INPUT);
  pinMode(grBtnOutp, OUTPUT);
  pinMode(redBtnInp, INPUT);
  pinMode(redBtnOutp, OUTPUT);
  pinMode(ylBtnInp, INPUT);
  pinMode(ylBtnOutp, OUTPUT);

  delay(1000);
}

void loop() {
  score = 0;
  int* LEDoutputs = new int[1];

  while (true) {
    int LEDoutput;

    //random LED BLINK logic
    randNumber = random(3);
    if(randNumber == 0) LEDoutput = grBtnOutp;
    else if (randNumber == 1) LEDoutput = redBtnOutp;
    else if(randNumber == 2) LEDoutput = ylBtnOutp;
    //random LED BLINK logic

    //Current game LEDs are lit
    LEDoutputs[score] = LEDoutput;

    for(int i = 0; i < score + 1; i++) 
    {
      blink(LEDoutputs[i], 600);
    }
    //Current game LEDs are lit

    //User response
    for(int i = 0; i < score + 1; i++) 
    {
      // Wait until button is clicked is available
      while (digitalRead(grBtnInp) == LOW && digitalRead(redBtnInp) == LOW && digitalRead(ylBtnInp) == LOW) {
        // Do nothing, just wait
      }
        
      if(digitalRead(grBtnInp) == HIGH)
      {
        blink(grBtnOutp, 300);
        if(LEDoutputs[i] != grBtnOutp)
        {
          gameOver();
          return;
        }         
      }
      else if(digitalRead(redBtnInp) == HIGH)
      {
        blink(redBtnOutp, 300);
        if(LEDoutputs[i] != redBtnOutp) 
        {
          gameOver();
          return;
        } 
      }
      else if(digitalRead(ylBtnInp) == HIGH) {
        blink(ylBtnOutp, 300);
        if(LEDoutputs[i] != ylBtnOutp)
        {
          gameOver();
          return;
        }     
      }
        
      while (digitalRead(grBtnInp) == HIGH || digitalRead(redBtnInp) == HIGH || digitalRead(ylBtnInp) == HIGH) {
        // Do nothing, just wait
      }
    }
    //User response
    
    score++;
    reportScore();

    //modify array by dynamically allocating memory
    int newLength = score + 1;
    int* LEDoutputsTmp = new int[newLength];

    for(int i = 0; i < newLength - 1; i++) LEDoutputsTmp[i] = LEDoutputs[i];

    LEDoutputsTmp[newLength - 1] = LEDoutput;

    delete[] LEDoutputs;
    LEDoutputs = LEDoutputsTmp;
    //modify array by dynamically allocating memory
  }
}

void gameOver() {
    reportScore();

    for(int i = 0; i < 3; i++){
    digitalWrite(grBtnOutp, HIGH);
    digitalWrite(ylBtnOutp, HIGH);
    digitalWrite(redBtnOutp, HIGH);
    delay(200);
    digitalWrite(grBtnOutp, LOW);
    digitalWrite(ylBtnOutp, LOW);
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