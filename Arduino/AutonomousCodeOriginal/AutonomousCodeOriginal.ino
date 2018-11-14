#include <Servo.h>
#include <Metro.h>
 
Metro measureDistance = Metro(50);
Metro sweepServo = Metro(20);

int speed_M1 = 5;     //M1 Speed Control
int speed_M2 = 6;     //M2 Speed Control
int direction_M1 = 4;     //M1 Direction Control
int direction_M2 = 7;     //M2 Direction Control
unsigned long actualDistance = 0;

Servo myservo;  // create servo object to control a servo
int pos = 60;
int sweepFlag = 1;

int URPWM = 3; // PWM Output 0－25000US，Every 50US represent 1cmk
int URTRIG = 10; // PWM trigger pin
uint8_t EnPwmCmd[4] = {0x44, 0x02, 0xbb, 0x01}; // distance measure command

void setup(){                                 // Serial initialization
  myservo.attach(9); 
  Serial.begin(9600);                         // Set the baud rate to 9600
  SensorSetup();
  delay(1000);
}

void loop() {
  if (measureDistance.check() == 1) {
    actualDistance = MeasureDistance();
//    Serial.println(actualDistance);
//    delay(100);
  }

  if (sweepServo.check() == 1) {
    servoSweep();
  }

  /*
   * In this decision tree the robot will continue to move forwards unless it encounters an obstacle 
   * If an obstacle is detected it will reverse and turn right or reverse and turn left.
   */
  if (actualDistance <= 30) {             //alter this value to change sensor sensitivity
    myservo.write(90);
    if (pos >= 90) {
      reverse(200, 200);
      Serial.println("reverse");
      delay(300);
      turnRight(255, 255);             //alter these values to change right turn speed
      Serial.println("turnRight");
      delay(500);
    } else {
      reverse(255, 255);                  //alter these values to change reverse speed
      Serial.println("reverse");
      delay(300);
      turnLeft(255, 255);              //alter these values to change left turn speed
      Serial.println("turnLeft");
      delay(500);
    }
  } else {
    forwards(100, 100);                 //alter these values to change forward speed
    Serial.println("forwards");
    delay(300);
  }
}

void SensorSetup() {
  pinMode(URTRIG, OUTPUT);                    // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG, HIGH);                 // Set to HIGH
  pinMode(URPWM, INPUT);                      // Sending Enable PWM mode command
  for (int i = 0; i < 4; i++) {
    Serial.write(EnPwmCmd[i]);
  }
}


/*
 * Measures the distance. 
 * LOW pull on COMP/TRIG (pin 6 on sensor) will trigger the sensor reading
 * When HIGH the pin will output pulses
 */
int MeasureDistance() { 
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);             
  unsigned long distance = pulseIn(URPWM, LOW);
  if (distance == 1000) {          // the reading is invalid.
    Serial.print("Invalid");
  } else {
    distance = distance / 50;       // every 50us low level stands for 1cm
  }
  return distance;
}

/*
 * The following control the movement of the car based on what the direction pins are set to. 
 * We have to set the direction for M1 and M2. 
 * Setting it to HIGH will cause the wheels to advance and LOW will cause to reverse. 
 */

//Tells the car to stop all wheels
void carStop() {                
  digitalWrite(speed_M2, 0);
  digitalWrite(direction_M1, LOW);
  digitalWrite(speed_M1, 0);
  digitalWrite(direction_M2, LOW);
}

//Tells the car to go backwards using speed passed in loop
void reverse(int leftSpeed, int rightSpeed) {       
  analogWrite (speed_M2, leftSpeed);             //PWM Speed Control
  digitalWrite(direction_M1, LOW);              //set LOW to reverse or HIGH to advance
  analogWrite (speed_M1, rightSpeed);
  digitalWrite(direction_M2, HIGH);
}

//Tells the car to go forwards using speed passed in loop
void forwards(int leftSpeed, int rightSpeed) {     
  analogWrite (speed_M2, leftSpeed);
  digitalWrite(direction_M1, HIGH);
  analogWrite (speed_M1, rightSpeed);
  digitalWrite(direction_M2, LOW);
}

//Tells the car to turn left using speed passed in loop
void turnLeft(int leftSpeed, int rightSpeed) {           
  analogWrite (speed_M2, leftSpeed);
  digitalWrite(direction_M1, HIGH);
  analogWrite (speed_M1, rightSpeed);
  digitalWrite(direction_M2, HIGH);
}

//Tells the car to turn right using speed passed in loop
void turnRight(int leftSpeed, int rightSpeed) {       
  analogWrite (speed_M2, leftSpeed);
  digitalWrite(direction_M1, LOW);
  analogWrite (speed_M1, rightSpeed);
  digitalWrite(direction_M2, LOW);
} 


//sweeps the servo to find obstacles
void servoSweep() 
{
  if (sweepFlag) {
    if (pos >= 60 && pos <= 120) {
      pos = pos + 15;                              // in steps of 1 degree
      myservo.write(pos);                         // tell servo to go to position in variable 'pos'
    }
    if (pos > 119)  sweepFlag = false;                    // assign the variable again
  }
  else {
    if (pos >= 60 && pos <= 120) {
      pos = pos - 15;
      myservo.write(pos);
    }
    if (pos < 61)  sweepFlag = true;
  }
  
}
