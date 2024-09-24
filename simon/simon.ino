#define TABLE_SIZE 10

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
String keys[TABLE_SIZE];
unsigned char values[TABLE_SIZE];

unsigned char hexChars[]=
{0x40,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};

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

  Display(0);
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
int hashFunction(String key) {
  int hash = 0;
  for (int i = 0; i < key.length(); i++) {
    hash += key[i];
  }
  return hash % TABLE_SIZE;
}

void insert(String key, int value) {
  int index = hashFunction(key);
  keys[index] = key;
  values[index] = value;
}

int get(String key) {
  int index = hashFunction(key);
  if (keys[index] == key) {
    return values[index];
  } else {
    return -1;  // Key not found
  }
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

void Display(unsigned char num)
{
  digitalWrite(latch,LOW);
  shiftOut(data,clock,MSBFIRST,hexChars[num]);
  digitalWrite(latch,HIGH);
}
