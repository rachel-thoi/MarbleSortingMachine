#include <Servo.h>

// =====================
// Servo Objects
// =====================
Servo TServo;
Servo BServo;

// =====================
// Pin Definitions
// =====================
int buttonPin = 11;
int buttonState = 0;

int pulsePin = 7;

int prescale0Pin    = 3;
int prescale1Pin    = 4;
int colorSelect0pin = 5;
int colorSelect1pin = 6;


// =====================
// Setup
// =====================
void setup() {

  // Color sensor setup
  pinMode(prescale0Pin, OUTPUT);
  pinMode(prescale1Pin, OUTPUT);

  digitalWrite(prescale0Pin, HIGH);
  digitalWrite(prescale1Pin, HIGH);

  pinMode(colorSelect0pin, OUTPUT);
  pinMode(colorSelect1pin, OUTPUT);
  pinMode(pulsePin, INPUT);

  // Servo setup
  TServo.attach(9);
  BServo.attach(8);

  // Button setup
  pinMode(buttonPin, INPUT_PULLUP);

  // Serial
  Serial.begin(9600);
  Serial.println("Color Reader");
}


// =====================
// Main Loop
// =====================
void loop() {

  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {

    TServo.write(0);          // Full speed rotation
    delay(4200);              // Full 360 rotation (estimated)

    digitalWrite(10, HIGH);
    BServo.write(35);

    // -----------------
    // Read Colors
    // -----------------
    long red   = readRed();
    long green = readGreen();
    long blue  = readBlue();
    long white = readWhite();

    int rotationConstant = 45;

    // =====================
    // RED
    // =====================
    if ((red < green) && (red < blue)) {

      Serial.println("RED");
      Serial.println(red);
      Serial.println(blue);
      Serial.println(green);
      Serial.println(white);

      TServo.write(0);
      delay(525);

      TServo.write(90);       // Stop
      delay(2000);            // Drop marble

      TServo.write(0);
      delay(3675);            // Return

      TServo.write(90);       // Stop at start
    }

    // =====================
    // MODIFY FOR BLUE
    // =====================
    if ((red < green) && (red < blue)) {

      Serial.println("RED");
      Serial.println(red);
      Serial.println(blue);
      Serial.println(green);
      Serial.println(white);

      TServo.write(0);
      delay(525);

      TServo.write(90);
      delay(2000);

      TServo.write(0);
      delay(3675);

      TServo.write(90);
    }

    // =====================
    // MODIFY FOR GREEN
    // =====================
    if ((red < green) && (red < blue)) {

      Serial.println("RED");
      Serial.println(red);
      Serial.println(blue);
      Serial.println(green);
      Serial.println(white);

      TServo.write(0);
      delay(525);

      TServo.write(90);
      delay(2000);

      TServo.write(0);
      delay(3675);

      TServo.write(90);
    }

    // Similar modifications for other colors...

    digitalWrite(10, LOW);
    delay(1000);
  }
}


// =====================
// Color Functions
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