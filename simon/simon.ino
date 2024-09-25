long randNumber;
int highScore;
int score;

//LED wiring
int grBtnInp = 2;
int grBtnOutp = 7;

int redBtnInp = 3;
int redBtnOutp = 8;

int ylBtnInp = 4;
int ylBtnOutp = 9;

int blBtnInp = 5;
int blBtnOutp = 10;
//LED wiring

//4 digit segment display wiring
#define TABLE_SIZE 11

String charAsStrs[TABLE_SIZE] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "-"};
unsigned char values[TABLE_SIZE] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x40};

int latch=12;  //orange wire
int clock=13; //green wire
int data=11;   //yellow wire
//4 digit segment display wiring

void setup() {
  Serial.begin(9600);

  //LED wiring
  pinMode(grBtnInp, INPUT);
  pinMode(grBtnOutp, OUTPUT);
  pinMode(redBtnInp, INPUT);
  pinMode(redBtnOutp, OUTPUT);
  pinMode(ylBtnInp, INPUT);
  pinMode(ylBtnOutp, OUTPUT);
  pinMode(blBtnInp, INPUT);
  pinMode(blBtnOutp, OUTPUT);
  //LED wiring

  //4 digit segment display
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);
  //4 digit segment display

  segmentedDisplay("-");
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
        
      int requiredPin = LEDoutputs[i];

      if(digitalRead(grBtnInp) == HIGH)
      {
        if(!validInput(grBtnOutp, requiredPin)) return;       
      }
      else if(digitalRead(redBtnInp) == HIGH)
      {
        if(!validInput(redBtnOutp, requiredPin)) return;       
      }
      else if(digitalRead(ylBtnInp) == HIGH) {
        if(!validInput(ylBtnOutp, requiredPin)) return;       
      }
      else {
        if(!validInput(blBtnOutp, requiredPin)) return;       
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

//methods related to 4 digit segmented display
int getCharAsHex(String charAsStr) {
  for (int i = 0; i < sizeof(charAsStrs) / sizeof(charAsStrs[0]); i++) {
    if(charAsStrs[i] == charAsStr) return values[i];
  }
  return -1;
}

void segmentedDisplay(String charAsStr)
{
  unsigned char charAsHex;

  for (int i = 0; i < sizeof(charAsStrs) / sizeof(charAsStrs[0]); i++) {
    if(charAsStrs[i] == charAsStr) charAsHex = values[i];
  }

  digitalWrite(latch,LOW);
  shiftOut(data,clock,MSBFIRST, charAsHex);
  digitalWrite(latch,HIGH);
}
//methods related to 4 digit segmented display

bool validInput(int chosenPin, int requiredPin) {
  blink(chosenPin, 150);
  if(chosenPin != requiredPin)
  {
    gameOver();
    return false;
  }  
  return true;
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
  delay(delayInt / 2);
}