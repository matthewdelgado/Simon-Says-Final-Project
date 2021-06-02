// number of rounds
const int ROUNDS = 3;
int randomSequence[ROUNDS];
int userSequence[ROUNDS];
int level = 1;

// tone variables
const int buzzerPin = 3;
unsigned int redTone = 440;
unsigned int yellowTone = 784;
unsigned int blueTone = 587;
unsigned int greenTone = 880;
unsigned int errorTone1 = 250;
unsigned int errorTone2 = 150;
unsigned long toneDuration = 150;
unsigned long errorDuration = 250;

// light variables/arrays
const int NUM_LIGHTS = 4;
const int ledPin[NUM_LIGHTS] = {12, 11, 10, 9};

// game speed
int velocity = 900;
unsigned long blinkTime = 200;
unsigned long blinkTime2 = 400;
bool gameOver;

// function declarations
void MypinMode(uint8_t pin, bool isOutput);
void MydigitalWrite(uint8_t pin, bool isOn);
bool MydigitalRead(uint8_t pin);
void Mydelay(unsigned long ms);
void delayOneMs();

int generateRandSequence();
void showRandSequence();
void getUserSequence();
void incorrectSequence();
void correctSequence();

// delay variables
unsigned int ticks = 0;
int pin;
bool delayFlag = false;

void setup() 
{
  // set button input pins
  for(int i = 4; i < 8; i++)
  {
    MypinMode(i, INPUT);
  }

  // set led output pins
  for(int i = 9; i < 13; i++)
  {
    MypinMode(i, OUTPUT);
  }

  // set buzzer output pin
  MypinMode(buzzerPin, OUTPUT);

  // turn all leds off
  for(int i = 9; i < 13; i++)
  {
    MydigitalWrite(i, LOW);
  }
}

void loop()
{
  // game starts when program is run or arduino is reset
  do
  {
    // if user is starting the game
    if (level == 1)
    {
      // generaten a random sequence
      generateRandSequence();
    }

    // if button has not been pressed or player is winning
    if (MydigitalRead(4) == LOW || level != 1)
    {
      showRandSequence();    //show the random sequence
      getUserSequence();     //wait for the user to input their sequence
    }
  }
  while(gameOver = false);
}

int generateRandSequence()
{ 
  // analog reading an unconnected pin ensures random values
  randomSeed(analogRead(A0));

  // create random values based on the number of rounds specified in the ROUNDS variable
  for (int i = 0; i < ROUNDS; i++)
  {
    // randomly generates values of pin number 9-12
    randomSequence[i] = round(random(9, 13));
  }
}

void showRandSequence()
{
  // turn all leds off
  for(int i = 9; i < 13; i++)
  {
    MydigitalWrite(i, LOW);
  }

  // play corresponding led tone
  for (int i = 0; i < level; i++)
  {
    if (randomSequence[i] == 9)
    {
      // play green tone
      Mytone(buzzerPin, greenTone, toneDuration);
      Mydelay(.568);
      Mytone(buzzerPin, greenTone, toneDuration);
    }
    else if (randomSequence[i] == 10)
    {
      // play yellow tone
      Mytone(buzzerPin, yellowTone, toneDuration);
      Mydelay(.638);
      Mytone(buzzerPin, yellowTone, toneDuration);
    }
    else if (randomSequence[i] == 11)
    {
      // play red tone
      Mytone(buzzerPin, redTone, toneDuration);
      Mydelay(1.136);
      Mytone(buzzerPin, redTone, toneDuration);
    }
    else if (randomSequence[i] == 12)
    {
      // play blue tone
      Mytone(buzzerPin, blueTone, toneDuration);
      Mydelay(.851);
      Mytone(buzzerPin, blueTone, toneDuration);
    }
    // blink corresponding led
    MydigitalWrite(randomSequence[i], HIGH);
    Mydelay(velocity);
    MydigitalWrite(randomSequence[i], LOW);
    Mydelay(blinkTime);
    noTone(buzzerPin);
   }
}

void getUserSequence()
{
  int flag = 0; // flag indicates if sequence is correct

  // user's sequence will take on values up to the level number
  for (int i = 0; i < level; i++)
  {
    // flag is init
    flag = 0;
   
    while(flag == 0)
    {
      // if green button is pushed
      if (MydigitalRead(4) == HIGH)
      {
        // turn on green led
        MydigitalWrite(9, HIGH);
        // set user's input sequence
        userSequence[i] = 9;
        flag = 1;
        Mydelay(200);
        // if user input is incorrect
        if (userSequence[i] != randomSequence[i])
        {
          // game over
          incorrectSequence();
          return;
        }
        else
        {
          // play green tone
          Mytone(buzzerPin, greenTone, toneDuration);
          Mydelay(.568);
          Mytone(buzzerPin, greenTone, toneDuration);
          Mydelay(300);
        }
        // turn off green led
        MydigitalWrite(9, LOW);
      }

      // if yellow button is pressed
      if (MydigitalRead(5) == HIGH)
      {  
        // turn on yellow led
        MydigitalWrite(10, HIGH);
        userSequence[i] = 10;
        flag = 1;
        Mydelay(300);
        // if user input is incorrect
        if (userSequence[i] != randomSequence[i])
        {
          // game over
          incorrectSequence();
          return;
        }
        else
        {
          // play yellow tone
          Mytone(buzzerPin, yellowTone, toneDuration);
          Mydelay(.638);
          Mytone(buzzerPin, yellowTone, toneDuration);
          Mydelay(300);
        }
        // turn off yellow led
        MydigitalWrite(10, LOW);
      }

      // if red button is pushed
      if (MydigitalRead(6) == HIGH)
      {
        // turn on red led
        MydigitalWrite(11, HIGH);
        userSequence[i] = 11;
        flag = 1;
        Mydelay(200);
        // if user input is incorrect
        if (userSequence[i] != randomSequence[i])
        {
          // game over
          incorrectSequence();
          return;
        }
        else
        {
          // play red tone
          Mytone(buzzerPin, redTone, toneDuration);
          Mydelay(1.136);
          Mytone(buzzerPin, redTone, toneDuration);
          Mydelay(300);
        }
        // turn off red led
        MydigitalWrite(11, LOW);
      }

      // if blue button is pushed
      if (MydigitalRead(7) == HIGH)
      {  
        // turn on blue led
        MydigitalWrite(12, HIGH);
        userSequence[i] = 12;
        flag = 1;
        Mydelay(200);
        // if user input is incorrect
        if (userSequence[i] != randomSequence[i])
        {
          // game over
          incorrectSequence();
          return;
        }
        else
        {
          // play blue tone
          Mytone(buzzerPin, blueTone, toneDuration);
          Mydelay(.851);
          Mytone(buzzerPin, blueTone, toneDuration);
          Mydelay(300);
        }
        // turn off blue led
        MydigitalWrite(12, LOW);
      }
      noTone(buzzerPin);
    }
  }
  correctSequence();
}

// game over
void incorrectSequence()
{
  // plays error tone
  Mytone(buzzerPin, errorTone1, errorDuration);
  Mydelay(250);
  Mytone(buzzerPin, errorTone2, errorDuration);
  
  // turn off all leds
  for(int i = 9; i < 13; i++)
  {
    MydigitalWrite(i, LOW);
  }
  
  // wait indefinitely until program is reset on arduino board
  for(int i = 0; i < 10; )
  {
    i++;
    i--;
  }
}

void correctSequence()
{
  // delay so the rounds are easily recognized
  Mydelay(1000);

  // turn all leds off
  for(int i = 9; i < 13; i++)
  {
    MydigitalWrite(i, LOW);
  }

  // check if there are more rounds to be played
  if (level < ROUNDS)
  {
    // increase the level
    level++;
  }
  else if (level = ROUNDS)
  {
    for (int j = 0; j < 1; )
    {
      // start indefinitely long led chase until program is reset on arduino board
      for (int i = 9; i < 13; i++)
      {
        MydigitalWrite(i, HIGH);
        Mydelay(100);
        MydigitalWrite(i, LOW);
      }
    }
  }
  // increase the velocity of the game
  velocity -= 50;
}

void MypinMode(uint8_t pin, bool isOutput)
{
  if(pin < 8)
  {
    char mask = 1 << pin;
    if(isOutput == 1)
    {
      DDRD |= mask;
    }
    else
    {
      DDRD &= ~mask;
    }
  }
  else
  {
    pin = pin - 8;
    char mask = 1 << pin;
    if(isOutput == 1)
    {
      DDRD |= mask;
    }
    else
    {
      DDRB &= ~mask;
    }
  }
}

void MydigitalWrite(uint8_t pin, bool isOn)
{
  if(pin < 8)
  {
    if(isOn == 1)
    {
      PORTD |= 1 << pin;
    }
    else
    {
      PORTD &= ~(1 << pin);
    }
  }
  else
  {
    {
      pin = pin - 8;
    }
    if(isOn == 1)
    {
      PORTB |= 1 << pin;
    }
    else
    {
      PORTB &= ~(1 << pin);
    }
  }
}

bool MydigitalRead(uint8_t pin)
{
  bool isOn = false;
  if(pin < 8)
  {
    isOn = (PIND & (1 << pin)) >> pin;
  }
  else
  {
    isOn = (PINB & (1 << (pin - 8))) >> (pin - 8);
  }
  return isOn;
}

// delays one milliseconds
void delayOneMs()
{
  uint8_t oldSREG = SREG;   
  cli();
  TCNT0 = 0x06;
  TCCR0A = 0x00;
  TCCR0B = 0x03;   

  while((TIFR0 & 0x01) == 0); 

  TCCR0B = 0x00;
  
  TIFR0 = 0x1;  
 
  SREG = oldSREG;
}

void Mydelay(unsigned long ms)
{
  // calls 1ms delay x amount of times
  for(int i = 0; i < ms; i++)
  {
    delayOneMs();
  }
}

void Mytone(int pin, unsigned int freq, unsigned long ms)
{
  tone(pin, freq, ms);
}
