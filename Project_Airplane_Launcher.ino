#include <Servo.h>

int motor_potpin = 0;  // analog pin used to connect the motor potentiometer
int servo_potpin = 1; // analog pin used to connect the servo potentiometer
int motor_val;    // variable to read the value from the analog pin
int servo_val;    // variable to read the value from the analog pin
Servo myservo;  // create servo object to control a servo
int motorPin = 11;
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(motorPin, OUTPUT);
} 
 
void loop() 
{
  // Read the value of the potentiometer (value between 0 and 1023)
  // and scale it down to use it with the motor (value between 0 and 255)
  motor_val = map(analogRead(motor_potpin), 0, 1023, 0, 255);
  // Read the analog value of the potentiometer (value between 0 and 1023)
  // and scale it down to use with the motor (value between 0 and 180)
  servo_val = map(analogRead(servo_potpin, 0, 1023, 0, 90); 
  analogWrite(motorPin, motor_val);
  myservo.write(servo_val);
}

