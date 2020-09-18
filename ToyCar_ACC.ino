//Adaptive Cruise Control (ACC) Toy Car --->     //USES PWM to control speed
//M.Khaled
//June 2, 2020

#include <elapsedMillis.h>

#define trigPin 13
#define echoPin 12

#define buzzer 4

elapsedMillis timeElapsed;
unsigned int interval = 10000; //10 seconds

// DC motor 1 control
#define P1A 2  // define pin 2 as for P1A
#define P2A 3  // define pin 3 as for P2A
#define EN12 5 // define pin for 1,2EN enable

//DC motor 2 control

#define P3A 6
#define P4A 7
#define EN34 9

void setup() {
  // L293 Motor Control 
  Serial.begin(9600);   // setup Serial Monitor to display information
  pinMode(P1A, OUTPUT); // define pin as OUTPUT for P1A
  pinMode(P2A, OUTPUT); // define pin as OUTPUT for P2A
  pinMode(EN12, OUTPUT);// define pin as OUTPUT for 1,2EN

  pinMode(P3A, OUTPUT);
  pinMode(P4A, OUTPUT);
  pinMode(EN34, OUTPUT);

  pinMode(buzzer, OUTPUT); //active buzzer

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);  //calculates the travel time of sound wave in microseconds 
  distance = (duration/2)/29.1;  //use duration to calculate the distance in "cm" 

  Serial.print(distance);
  Serial.println(" cm");

 if (distance>=50 && distance<=300){   //ultrasonic sensor's range is around 2cm - 400cm
    digitalWrite(buzzer, LOW);  //turn buzzer OFF

    digitalWrite(EN12 ,HIGH);// Enable 1A and 2A   //turn motor 1 at full speed
    digitalWrite(P1A,HIGH);  // send + to P1A
    digitalWrite(P2A,LOW);   // send - to P2A 

    digitalWrite(EN34 ,HIGH);// Enable 3A and 4A   //turn motor 2 at full speed
    digitalWrite(P3A,HIGH);  // send + to P3A
    digitalWrite(P4A,LOW);   // send - to P4A 
  }

  else if (distance>=10 && distance<50){  //adapt the speed according to the distance measured by ultrasonic sensor

    digitalWrite(buzzer, LOW); //turn buzzer OFF

    int dist = map(distance, 10, 50, 70, 255);

    analogWrite(EN12,dist); //adapt speed of motor1 depending on dist
    digitalWrite(P1A,HIGH); // send + or HIGH signal to P1A
    digitalWrite(P2A,LOW);  // send - or LOW signal to P2A 

    analogWrite(EN34,dist); //adapt speed of motor2 depending on dist
    digitalWrite(P3A,HIGH); // send + or HIGH signal to P3A
    digitalWrite(P4A,LOW);  // send - or LOW signal to P4A 
   //delay(500);
} 

  else if (distance<10 && distance>1){
    
    digitalWrite(EN12, LOW);  // Disable 1A and 2A //object too close, turn off motor1
    digitalWrite(EN34, LOW);  // Disable 3A and 4A //object too close, turn off motor2
    digitalWrite(buzzer, HIGH); //turn buzzer ON to alert
  }
  
  else {
    digitalWrite(EN12, LOW);// Disable 1A and 2A
    digitalWrite(EN34, LOW);
    digitalWrite(buzzer, LOW); //buzzer OFF
  
    //delay(1000);
  }

}
