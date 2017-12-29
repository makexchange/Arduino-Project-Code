// Include the Servo library 
#include <Servo.h>

boolean common_cathode = true; // If using a common-anode RGB LED set to false
int redPin = 11;
int greenPin = 10;
int servoPin = 2;   // Declare the Servo pin 
Servo Servo1;       // Create a servo object 

int buttonPins[]={7, 6, 5, 4};
int secret_code[4];
int enter_code[4];
boolean unlock = true;

void setup() {
   Serial.begin(9600);  // Use serial for debugging
   for (int i=0; i<4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
   }
   Servo1.attach(servoPin); // Attach the servo object to the used pin number 
   pinMode(redPin, OUTPUT);
   pinMode(greenPin, OUTPUT);
   digitalWrite(redPin, LOW); // Set to HIGH for common-anode RGB LED
   digitalWrite(greenPin, LOW); // Set to HIGH for common-anode RGB LED
}

void loop(){
  if (unlock == true) {
    Servo1.write(180);
    Serial.println("Set the Secret Code:");
    for (int i=0; i<4; i++) {
      secret_code[i] = input_code();
      blinkRGB(1, 100, 0, 255);
      Serial.print("["); Serial.print(i); print_code("] secret_code", secret_code);
    }
    Servo1.write(90);
    delay(200);
    blinkRGB(2, 500, 0, 255);
    unlock = false; 
  } else {
      Serial.println("Enter the Secret Code");
      for (int i=0; i<4; i++) {
        enter_code[i] = input_code();
        blinkRGB(1, 100, 205, 255);
        Serial.print("["); Serial.print(i); print_code("] enter_code", enter_code);
      }
      if (check_equal(enter_code, secret_code) == true) {
        Servo1.write(180);
        blinkRGB(1, 2000, 0, 255);
        unlock = true;
        memset(&secret_code[4], 0, sizeof(secret_code));  
      } else {
        blinkRGB(1, 1000, 255, 0);
        for (int i=0; i<4; i++) {
          enter_code[i] = 0;
        }
      }
  }
}

// Compare the values of two arrays
boolean check_equal(int array1[], int array2[]) {
  for (int i=0; i<4; i++) {
    if (array1[i] != array2[i]) {
      return false;
    }
  } return true;
}

// Check for button press and return the button number
int input_code() {  
  int previous_buttonState[4];
  while (true) {
     // Check that all buttons are not already being pressed
     for (int b=0; b<4; b++) {
      int buttonState = digitalRead(buttonPins[b]);
      previous_buttonState[b] = buttonState;
     }
     delay(50);  
     for (int b=0; b<4; b++) {
      int buttonState = digitalRead(buttonPins[b]);
      if (buttonState == LOW && previous_buttonState[b] == HIGH) {
        return (b + 1);
      }
    }
  }
}

// A function for printing array contents
void print_code(String array_name, int my_array[]) {
  Serial.print(array_name); Serial.print(" = { ");
  for (int i=0; i<4; i++) {
    Serial.print(my_array[i]);
    Serial.print(", ");
  }
  Serial.println("}");
}

// A helper function to blink the RGB LED in various patterns
void blinkRGB(int times, int length_ms, int red_brightness, int green_brightness){
  if (common_cathode != true) {
    red_brightness = 255-red_brightness;
    green_brightness = 255-green_brightness;
  }
  for (int x=0; x<times; x++) {
    analogWrite(redPin, red_brightness);
    analogWrite(greenPin, green_brightness);
    delay (length_ms);
    if (common_cathode == true) {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
    } else {
      analogWrite(redPin, 255);
      analogWrite(greenPin, 255);
    }
    delay(length_ms);
  }
}
