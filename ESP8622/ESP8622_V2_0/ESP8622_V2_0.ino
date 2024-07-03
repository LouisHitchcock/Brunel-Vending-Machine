#include<SoftwareSerial.h>  // Includes a libary requred to use Serial (I2C) Protocol to communicate between devices. 
SoftwareSerial i2c(3, 1);
bool Ir; // Creates a boolean (Either ON or OFF (1 or 0)) variable 
unsigned long currentTime = 0; // Declares an unsigned long variable for the current time, as that stops the variable from overloading the IC.
unsigned long recordedTime = 0; // Declares an unsigned long variable for the recorded time, as that stops the variable from overloading the IC.
const int gap = 12000; // Amount of time between sending the trigger, in miliseconds. 1000 = 1 Second. 

void setup() {
  Serial.begin(9600); // This is mostly for debugging, although should also match.
 i2c.begin(9600);  // Define i2c baudrate of 9600 - THIS IS ESSENTIAL & MUST MATCH THE OTHER ARDUINO.
  pinMode(D5, INPUT);  // Defines the IR as an Input
}

void loop() {
  currentTime = millis(); // sets Current Time to the amount of miliseconds the device has had power. 
  Ir = digitalRead(D5); // Reads the status of the IR, either 0 (on) or 1 (off)
  Serial.println(Ir); // Outputs the status of IR, mostly Debugging purposes.

if (Ir == 0) { // If the IR is triggered, then activate the below code.
  recordedTime = millis(); // Records time that the IR is triggered. 
  if (currentTime >= (recordedTime + gap)) { // Compares the recorded time with the current time PLUS the gap. 
    i2c.write(123); // Send the codeword "123" through the I2C protocol to the other device. 
    delay(500); // Slows things down. 
   }
  }
else if (Ir == 1) {
  // If IR is not triggered.
  }
delay(100); // Just slows things down, make sure dont Overload the IC
}
