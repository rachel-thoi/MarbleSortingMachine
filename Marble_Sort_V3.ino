#include <Servo.h>

// =====================
// Servo Objects
// =====================
Servo TServo;
Servo BServo;

// =====================
// Button Section
// =====================
int buttonPin = 11;
int buttonState = 0;   // Initial state

// =====================
// Color Sensor Section
// =====================
int pulsePin = 7;      // OUT from sensor

// Sensor pin mapping
int prescale0Pin    = 3;  // S0
int prescale1Pin    = 4;  // S1
int colorSelect0pin = 5;  // S2
int colorSelect1pin = 6;  // S3

// =====================
// Setup
// =====================
void setup() {

  // ----- Color Reader Setup -----
  pinMode(prescale0Pin, OUTPUT);
  pinMode(prescale1Pin, OUTPUT);

  // Set output frequency scaling to 100%
  digitalWrite(prescale0Pin, HIGH);
  digitalWrite(prescale1Pin, HIGH);

  pinMode(colorSelect0pin, OUTPUT);
  pinMode(colorSelect1pin, OUTPUT);
  pinMode(pulsePin, INPUT);

  // ----- Servo Setup -----
  TServo.attach(9);
  BServo.attach(8);

  // ----- Button Setup -----
  pinMode(buttonPin, INPUT);

  // ----- Serial Setup -----
  Serial.begin(9600);
  Serial.println("Color Reader");
}

// =====================
// Main Loop
// =====================
void loop() {

  // Check button
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {

    // Move top servo
    TServo.write(120);
    delay(1000);
    TServo.write(160);
    delay(1000);

    // Turn on sensor LED (Pin 10 assumed configured elsewhere)
    digitalWrite(10, HIGH);

    // Position bottom servo
    BServo.write(120);

    // Read colors
    long red   = readRed();
    long green = readGreen();
    long blue  = readBlue();
    long white = readWhite();

    // ----- Color Detection -----

    if ((red < green) && (red < blue)) {
      Serial.println("RED");
      Serial.println(red);
      Serial.println(blue);
      Serial.println(green);
      Serial.println(white);
    }

    if ((green > 230) && (blue > 200) && (red > 330)) {
      Serial.println("GREEN");
      Serial.println(red);
      Serial.println(blue);
      Serial.println(green);
      Serial.println(white);
    }

    if ((blue < green) && (blue < red)) {
      Serial.println("BLUE");
      Serial.println(red);
      Serial.println(blue);
      Serial.println(green);
      Serial.println(white);
    }

    if ((white < 300) && (green < 200) && (red < 200)) {
      Serial.println("WHITE");
      Serial.println(red);
      Serial.println(blue);
      Serial.println(green);
      Serial.println(white);
    }

    // Turn off sensor LED
    digitalWrite(10, LOW);

    delay(1000);
  }
}

// =====================
// Color Reading Helpers
// =====================
long readRed() {
  return readColor(LOW, LOW);
}

long readGreen() {
  return readColor(HIGH, HIGH);
}

long readBlue() {
  return readColor(LOW, HIGH);
}

long readWhite() {
  return readColor(HIGH, LOW);
}

long readColor(int bit0, int bit1) {

  digitalWrite(colorSelect0pin, bit0);
  digitalWrite(colorSelect1pin, bit1);

  long start = millis();

  for (int i = 0; i < 1000; i++) {
    pulseIn(pulsePin, HIGH);
  }

  return (millis() - start);
}