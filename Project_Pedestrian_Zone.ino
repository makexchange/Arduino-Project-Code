const int buttonPin = 2;
int buttonState = 0;

int NorthStreet[]={13,12,11};
int WestStreet[]={10,9,8};

// If you are using a common-anode RGB LED
// you can change the below boolean to 'false'
boolean common_cathode = true;

void setup() {
  // Loop through pins 3 through 13 setting each as OUTPUTs
  for (int x=3; x<14; x++) {
    pinMode(x, OUTPUT);
  }
  // The buttonPin will be used to check for button inputs
  pinMode(buttonPin, INPUT);
}

void loop() {
  // When Traffic Light #1 is green the pedestrians must wait to cross
  // Fortunately, they have a button they can use to speed things up
  stopTimer(8000, NorthStreet[2], WestStreet[0]);
  stopTimer(2000, NorthStreet[1], WestStreet[0]);
  
  // When Traffic Light #2 comes on the pedestrians can safely cross
  goTimer(4000, NorthStreet[0], WestStreet[2]);
  blinkTimer(4, 2000, NorthStreet[0], WestStreet[2]); 
  stopTimer(2000, NorthStreet[0], WestStreet[1]);
}

void stopTimer(int duration, int light1, int light2 ) {
  lightsOut(); // Turn off the traffic lights
  walkLight(10, 0, 255); // Set the RGB LED to an orange-red color
  digitalWrite(light1, HIGH);
  digitalWrite(light2, HIGH);  
  // This for loop checks for a button press every 1 millisecond
  // for the length of the duration parameter  
  for (int x=0; x<duration; x++) {
    buttonState = digitalRead(buttonPin);
    if (light1 == NorthStreet[2] and buttonState == HIGH) {
      break; 
    } else {
      delay(1);   
    } 
  }      
}

void goTimer(int duration, int light1, int light2) {  
  lightsOut();
  walkLight(40, 0, 0); // Set the RGB LED to white
  digitalWrite(light1, HIGH);
  digitalWrite(light2, HIGH);
  delay(duration);       
}

void blinkTimer(int cycles, int duration, int light1, int light2 ) {  
  // Blink the crossing light (cycles) number of times 
  // over (duration) seconds
  duration = (duration / cycles);
  lightsOut();
  digitalWrite(light1, HIGH);
  digitalWrite(light2, HIGH);
  for (int i=0; i<cycles; i++) {
    // Turn off the RGB LED
    walkLight(255, 255, 255);
    delay(duration);
    // Set the RGB LED to an orange-red color
    walkLight(10, 0, 255);
    delay(duration);    
  }     
}

void walkLight(int R, int G, int B) {
  // Set the color of the RGB LED using PWM to write
  // a value between 0 and 255
  if (common_cathode == true) {
    R = 255 - R;
    G = 255 - G;
    B = 255 - B;
  }
  analogWrite(6, R);   // Red
  analogWrite(5, G);   // Green
  analogWrite(3, B);   // Blue     
}

void lightsOut() {
  // Turn off all 6 traffic lights
  for (int i=8; i<14; i++) {
    digitalWrite(i, LOW);
  }
}

