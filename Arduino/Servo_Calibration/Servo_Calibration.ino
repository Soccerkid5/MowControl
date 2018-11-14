#include <Servo.h> 
    Servo myservo;  // create servo object to control a servo 

    void setup() { 
      myservo.attach(9);  // attaches the servo on pin 3
    } 
    void loop() { 

       int i;
       for(i=60; i < 120; i=i+15){
       myservo.write(i);   // tell servo to go to position in 90 
       delay(300);      // waits 15ms 
       }

       for(i=120; i > 60; i=i-15){
       myservo.write(i);   // tell servo to go to position in 90 
       delay(300);      // waits 15ms 
       }
    }
