#include <Servo.h> 

const int pot1Pin = 2;    // 10kΩ pot for maximum angle
const int pot2Pin = 3;    // 10kΩ pot for minimum angle
const int servoPin = 9;   // servo motor
const int trigPin = 2;    // ultrasonic sensor trigger
const int echoPin = 4;    // ultrasonic sensor echo
const int ledRedPin = 5;  // red LED
const int ledBluePin = 6; // blue LED

const int maxCm = 50;     // ultrasonic sensor maximum distance
const int ledCycle = 100; // duration of red/blue LED cycle
                          // FIXME? timing is not constant for some reason :3

Servo servo;

long cm = 0;
int ledCounter = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
}
 
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long durationUs = pulseIn(echoPin, HIGH);
  long newCm = durationUs / 74;
  if(newCm <= maxCm) {
    cm = newCm;
  }

  if(cm > maxCm) {
    cm = maxCm;
  }

  int maxVal = analogRead(pot1Pin);
  int minVal = analogRead(pot2Pin);
  int angle = (((long) cm * (maxVal - minVal) * 180) / 50 + ((long) minVal) * 180) / 1023;
  
  //Serial.print(minVal);
  //Serial.print(" ");
  //Serial.print(maxVal);
  //Serial.print(" ");
  //Serial.print(angle);
  //Serial.print(cm);
  //Serial.println(" ");
  
  servo.write(angle);

  bool cycle0 = ledCounter < ledCycle / 2;
  digitalWrite(ledRedPin, cycle0 ? HIGH : LOW);
  digitalWrite(ledBluePin, cycle0 ? LOW : HIGH);
  ledCounter++;
  if(ledCounter >= ledCycle) {
    ledCounter = 0;
  }
} 

