//Servo section
#include <Servo.h>
Servo TServo;
Servo BServo;

//Button Section
int buttonPin = 11;
int buttonState = 0;   // This is the initial condition and is zero

//Color reader
int pulsePin = 7;
//OUT on color sensor goes to pin 7
//LED on Sensor goes to 5 V
//VCC goes to 5V There are two of them
//S0 on sensor goes to Arduino pin 3
int prescale0Pin = 3;
//S1 on color sensor goes to Arduino pin 4
int prescale1Pin = 4;
//S2 on color sensor goes to Arduino pin 5
int colorSelect0pin = 5;
//S3 on color sensor goes to Arduino pin 6
int colorSelect1pin = 6;

void setup() {

//Color reader section
pinMode(prescale0Pin, OUTPUT);
pinMode(prescale1Pin, OUTPUT);

//set max prescale
//setting output frequency scaling to 100 percent
//for 20 percent use colorSelect1pin LOW not HIGH    
// colorSelect1pin is S1 on sensor
//20 percent scaling is common

digitalWrite(prescale0Pin,HIGH);
digitalWrite(prescale1Pin, HIGH);
pinMode(colorSelect0pin,OUTPUT);
pinMode(colorSelect1pin,OUTPUT);
pinMode(pulsePin,INPUT);

//Servo section
TServo.attach(9);
BServo.attach(8);

//Button section
pinMode(buttonPin,2);

//Serial communication
//9600 in the code below is a baud rate and governs the rate of information exchange
Serial.begin(9600);
//  The next line just shows up on the serial monitor
Serial.println("Color Reader");

}


void loop()

{

//Check the button
buttonState = digitalRead(buttonPin);  // voltage is being read
if (buttonState == HIGH) {

//Move Servo to initial position
TServo.write(120);
delay(1000);
TServo.write(160);
delay(1000);

// The next line turns on the LED on pin 10 and signals the color sensor is being read
digitalWrite(10,HIGH);

//the functions to read for each color are being called below
//Move collecting bin to position
BServo.write(120);
long red=readRed();
long green=readGreen();
long blue = readBlue();
long white=readWhite();

//change to numeric values instead of variables green and blue on the next line if not reading red 
//correctly and do the same for the other colors

if ((red<green)&&(red<blue))
{
Serial.println("RED");
Serial.println(red);
Serial.println(blue);
Serial.println(green);
Serial.println(white);
}


if((green>230 ) && (blue >200) && (red>330))
{
Serial.println("GREEN");
Serial.println(red);
Serial.println(blue);
Serial.println(green);
Serial.println(white);
}

if ((blue < green) && (blue < red))
{
Serial.println("BLUE");
Serial.println(red);
Serial.println(blue);
Serial.println(green);
Serial.println(white);
}

if ((white<300) && (green<200 )&& (red<200))
{
Serial.println("WHITE");
Serial.println(red);
Serial.println(blue);
Serial.println(green);
Serial.println(white);
}


//the next line turns off the LED
digitalWrite(10,LOW);
delay(1000);

//for your final project code to direct the marble to its proper color bin goes here
//this is the end of the loop
}
}

long readRed()
{
return (readColor(LOW,LOW));
}

long readGreen()
{
return(readColor(HIGH,HIGH));
}

long readBlue()
{
return(readColor(LOW,HIGH));
}

long readWhite()
{
return(readColor(HIGH,LOW));
}

long readColor(int bit0, int bit1)
{
digitalWrite(colorSelect0pin, bit0);
digitalWrite(colorSelect1pin, bit1);

//millis is a time  this is measuring time to read in from the pulsePin
long start = millis();

for (int i = 0; i <1000; i++)
{
pulseIn(pulsePin,HIGH);
}
return (millis()-start);
}