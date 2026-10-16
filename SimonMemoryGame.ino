#include <Arduino_AVRSTL.h>

using namespace std;

const int red = 2;
const int green = 3;
const int blue = 4;
const int yellow = 5;
int high = 0;
int highScore = 0;

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  pinMode(red, INPUT);
  pinMode(green, INPUT);
  pinMode(blue, INPUT);
  pinMode(yellow, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(yellow, OUTPUT);
}

void off()
{
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
}

void on()
{
  digitalWrite(red, HIGH);
  digitalWrite(blue, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(yellow, HIGH);
}

void flash() //wrong answer flash
{
  on();
  delay(200);
  off();
  delay(200);
  on();
  delay(200);
  off();
  delay(200);
  on();
  delay(200);
  off();
  delay(200);
}

void loop() 
{ 
  on();
  delay(1000);
  off();
  delay(200);

  bool correct = true; 
  int size = 1; //reset size to 1
  high = 0; //reset score
  vector<int> color(1); //reset vector size to 1
  vector<int> ans(1); //reset vector size to 1
  
  //random color generator
  while (correct == true) 
  {
    off();
    int rand = random(1, 5);
    color[size] = rand;
    for (int i = 1; i <= size; i++)
    { 
      if (size < 5)
      {
        delay(350); //on for 350
        off();
        delay(300); //off for 300
      }
      if (size >= 5 && size < 9)
      {
        delay(250); //on for 250
        off();
        delay(200); //off for 200
      }
      if (size >= 9)
      {
        delay(150); //on for 150
        off();
        delay(100); //off for 100
      }
      if (color[i] == 1)
      {
        digitalWrite(red, HIGH);
      }
      if (color[i] == 2)
      {
        digitalWrite(green, HIGH);
      }
      if (color[i] == 3)
      {
        digitalWrite(blue, HIGH);
      }
      if (color[i] == 4)
      {
        digitalWrite(yellow, HIGH);
      }
    }
    delay(350);
    off(); 
    
    //user input
    for (int i = 1; i <= size; i++)
    {
      while(true)
      {
        if (digitalRead(red) == HIGH)
        {
          ans[i] = 1;
          break;
        }
        if (digitalRead(green) == HIGH)
        {
          ans[i] = 2;
          break;
        }
        if (digitalRead(blue) == HIGH)
        {
          ans[i] = 3;
          break;
        }
        if (digitalRead(yellow) == HIGH)
        {
          ans[i] = 4;
          break;
        }
      }
      while (digitalRead(red) == HIGH || digitalRead(green) == HIGH || digitalRead(blue) == HIGH || digitalRead(yellow) == HIGH) //ensures button push doesn't count twice
      {
        delay(10);
      }
      if (ans[i] == color[i]) //correct
      {
        continue;
      }
      else //wrong
      {
        flash();
        correct = false;
        break;
      }
    }
    high = size - 1; //save score
    size++;
    on(); 
    delay(200);
    off();
  }
  Serial.print("Score: ");
  Serial.println(high);
  if (high >= highScore)
  {
    highScore = high;
  }
  Serial.print("Highscore: ");
  Serial.println(highScore);
}
