// A common-cathode RGB LED works similarly to
// other LEDs, with 0 being LOW and 255 being HIGH
// For common-anode RGB LEDs the highest value (255)
// stops the flow of electricity, turning off the color
const int redPin = 6;
const int greenPin = 5;
const int bluePin = 3;

// If you are using a common-anode RGB LED you will have to
// add a short wire between 5V and the right [+] rail,
// and place the end of the resistor in this rail.
// Then simply change the below boolean to 'false'
boolean common_cathode = true;
const int buttonPin = 2;

void setup() {
  // Start with the LED off.
  setColorRgb(0,0,0);
  pinMode(buttonPin, INPUT_PULLUP);
 }

void loop() {
  unsigned int rgbColor[3];
  
  if (digitalRead(buttonPin) == LOW) {
    // Start off with red.
    rgbColor[0] = 255;
    rgbColor[1] = 0;
    rgbColor[2] = 0; 

    // Choose the colors to increment and decrement.
    for (int incColor = 0; incColor < 3; incColor += 1) {
      int decColor = incColor == 2 ? 0 : incColor + 1;
  
      
      // cross-fade the two colors.
      for(int i = 0; i < 255; i += 1) {
        rgbColor[incColor] -= 1;
        rgbColor[decColor] += 1; 
        setColorRgb(rgbColor[0], rgbColor[1], rgbColor[2]);
        delay(5); 
      }         
    }
  } else {
    // Turn LED off
    setColorRgb(0,0,0);
  } 
}

void setColorRgb(unsigned int red, unsigned int green, unsigned int blue) {
  if (common_cathode != true) {
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  }
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
 }
