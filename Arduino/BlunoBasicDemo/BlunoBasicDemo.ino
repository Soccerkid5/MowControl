void setup() {
  int i;
  for (i = 4; i <= 7; i++)
    pinMode(i, OUTPUT);
    Serial.begin(115200);               //initial the Serial
}

void loop()
{
    if(Serial.available())
    {
      char val = Serial.read();
      if (val != -1)
      {
      switch (val)
        {
        case 'a'://Turn Left
          Serial.println("turning left");
          turnLeft (255, 255);  
          delay (1000);
          stop();
          break;
        case 'd'://Turn Right
          Serial.println("turning right");
          turnRight (255, 255);  
          delay (1000);
          stop();
          break;
        case 'w'://Move Forwards
          Serial.println("going forward");
          advance (255, 255);
          delay (1000);
          stop();
          break;
        case 's'://Move Backwards
          Serial.println("going backwards");
          reverse (255, 255);
          delay (1000);
          stop();
          break;
        case 'x':
          Serial.println("stopping");
          stop();
          break;
        }
    }
    else stop();
  }
        //Serial.write(Serial.read());    //send what has been received
  
}

//Motor Definitions
int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;     //M1 Direction Control
int M2 = 7;     //M2 Direction Control

//DIRECTIONS

//STOP
void stop(void)
{
  digitalWrite(E1, 0);
  digitalWrite(M1, LOW);
  digitalWrite(E2, 0);
  digitalWrite(M2, LOW);
}

//TURN LEFT
void turnLeft (char a, char b)
{
  analogWrite (E1, a);
  digitalWrite(M1, HIGH);
  analogWrite (E2, b);
  digitalWrite(M2, HIGH);
}

//TURN RIGHT
void turnRight (char a, char b)
{
  analogWrite (E1, a);
  digitalWrite(M1, LOW);
  analogWrite (E2, b);
  digitalWrite(M2, LOW);
}

//GOES FORWARD
void advance (char a, char b)
{
  analogWrite (E1, a);
  digitalWrite(M1, LOW);
  analogWrite (E2, b);
  digitalWrite(M2, HIGH);
}

//GOES BACK
void reverse (char a, char b)
{
  analogWrite (E1, a);
  digitalWrite(M1, HIGH);
  analogWrite (E2, b);
  digitalWrite(M2, LOW);
}
