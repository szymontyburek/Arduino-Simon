long randNumber;
int highScore;
int score;

int grBtnInp = 2;
int grBtnOutp = 8;

int redBtnInp = 3;
int redBtnOutp = 9;

int ylBtnInp = 4;
int ylBtnOutp = 10;

int blBtnInp = 5;
int blBtnOutp = 10;

void setup() {
  Serial.begin(9600);
  pinMode(grBtnInp, INPUT);
  pinMode(grBtnOutp, OUTPUT);
  pinMode(redBtnInp, INPUT);
  pinMode(redBtnOutp, OUTPUT);
  pinMode(ylBtnInp, INPUT);
  pinMode(ylBtnOutp, OUTPUT);
  pinMode(blBtnInp, INPUT);
  pinMode(blBtnOutp, OUTPUT);

  delay(1000);
}

void loop() {
  score = 0;
  int* LEDoutputs = new int[1];

  while (true) {
    int LEDoutput;

    //random LED BLINK logic
    randNumber = random(4);
    if(randNumber == 0) LEDoutput = grBtnOutp;
    else if (randNumber == 1) LEDoutput = redBtnOutp;
    else if(randNumber == 2) LEDoutput = ylBtnOutp;
    else LEDoutput = blBtnOutp;
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
      while (digitalRead(grBtnInp) == LOW && digitalRead(redBtnInp) == LOW && digitalRead(ylBtnInp) == LOW && digitalRead(blBtnInp) == LOW) {
        // Do nothing, just wait
      }
        
      if(digitalRead(grBtnInp) == HIGH)
      {
        blink(grBtnOutp, 150);
        if(LEDoutputs[i] != grBtnOutp)
        {
          gameOver();
          return;
        }         
      }
      else if(digitalRead(redBtnInp) == HIGH)
      {
        blink(redBtnOutp, 150);
        if(LEDoutputs[i] != redBtnOutp) 
        {
          gameOver();
          return;
        } 
      }
      else if(digitalRead(ylBtnInp) == HIGH) {
        blink(ylBtnOutp, 150);
        if(LEDoutputs[i] != ylBtnOutp)
        {
          gameOver();
          return;
        }     
      }
      else {
        blink(blBtnOutp, 150);
        if(LEDoutputs[i] != blBtnOutp)
        {
          gameOver();
          return;
        }  
      }
        
      while (digitalRead(grBtnInp) == HIGH || digitalRead(redBtnInp) == HIGH || digitalRead(ylBtnInp) == HIGH || digitalRead(blBtnInp) == HIGH) {
        // Do nothing, just wait
      }
    }
    //User response
    
    delay(300);
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
    digitalWrite(redBtnOutp, HIGH);
    digitalWrite(ylBtnOutp, HIGH);
    digitalWrite(blBtnOutp, HIGH);
    delay(200);
    digitalWrite(grBtnOutp, LOW);
    digitalWrite(redBtnOutp, LOW);
    digitalWrite(ylBtnOutp, LOW);
    digitalWrite(blBtnOutp, LOW);
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