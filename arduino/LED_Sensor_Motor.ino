// LEDs
#include <FastLED.h>
#define NUM_LEDS 6
CRGBArray<NUM_LEDS> leds;

double feetUntilTurn=25;
double totalFeet=feetUntilTurn;
int val = 0;         // variable to store the read value
int LEFT=0;
int RIGHT=1;
//int feetUntilTurn = 600;

// motion sensor
#define echoPin 3 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 2 //attach pin D3 Arduino to pin Trig of HC-SR04

//vibration motor
int motorPin = 10;

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int distance1=0;
int distance2=0;
double Speed=0;
double Delay=0.1;

void setup() {

  //LED set up
  FastLED.addLeds<NEOPIXEL,5>(leds, NUM_LEDS); 

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode( 7 , OUTPUT);

  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("LED test");
}

void loop() {
  int turnDirection = LEFT;
  int hue = 95 - (feetUntilTurn/totalFeet)*95;
  if(feetUntilTurn > 100) {
    changeColor(hue);
  } else if (feetUntilTurn > 0) {
    turnSignal(hue);
  } else if (feetUntilTurn == 0) {
    feetUntilTurn = 25;
    totalFeet = 25;
  }
  feetUntilTurn--;
  Serial.println(feetUntilTurn);
  checkDistance(distance, Speed);
  distance = ultrasonicRead();
  Speed = getSpeed();
  
  
  
}


void checkDistance(double distance, double Speed) {
  if (distance < 20) {
    digitalWrite(motorPin, HIGH);
    delay(100);  // delay one second
    digitalWrite(motorPin, LOW);  //stop vibrating
    delay(50); //wait 50 seconds. 
  }
}
float getSpeed() {
  //calculating Speed
   distance1 = ultrasonicRead(); //calls ultrasoninicRead() function below
   
   delay(Delay);//giving a time gap of 1 sec
   
   distance2 = ultrasonicRead(); //calls ultrasoninicRead() function below
   
   //formula change in distance divided by change in time
   Speed = (distance2 - distance1)/Delay; //as the time gap is 1 sec we divide it by 1.
   
  //Displaying Speed
  Serial.print("Speed in cm/s  :"); 
  Serial.println(Speed);
}

float ultrasonicRead () {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  //calculating distance
  distance= duration*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance in cm : ");
  Serial.println(distance);
  return distance;
}

void changeColor(int hue) {
  for(int i = 0; i < NUM_LEDS; i++) {   
    leds[i] = CHSV(hue, 255, 255);
    FastLED.delay(10);
  }
}

void turnSignal(int hue) {
  for(int i = 0; i < NUM_LEDS; i++) {  
    leds.fadeToBlackBy(150); 
    leds[i] = CHSV(hue, 255, 255);
    FastLED.delay(100);
  }
}
