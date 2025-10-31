#include <Servo.h>
#define sgn(x) (((x) > 0) - ((x) < 0))
// #define SLOW_SERVO

int loopCount;
int pos;
const int servoPin = 10;
const int ledPin = 9;
Servo myservo;

void setup() {
  loopCount = 0;
  pos = 90;
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, 0);
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  //myservo.attach(servoPin);
  //myservo.write(pos);
}

// put your main code here, to run repeatedly:
void loop() {
  int inByte;
  int deg;
  int incr;
  int newPos;
  int ms = 100;

  // Check for incoming serial data and read it if available.
  // Check for single character command for left, center, right, or pause.
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    switch (inByte) {
      case 'l':
        newPos = 30;
        break;
      case 'c':
        newPos = 90;
        break;
      case 'r':
        newPos = 150;
        break;
      case 'p':
        delay(200);
        ms = 0;
        // No break
      default:
        newPos = pos;
    }
    if (newPos != pos) {
      myservo.attach(servoPin);
      digitalWrite(ledPin, 1);
  #ifdef SLOW_SERVO
      incr = sgn(newPos - pos) * 5;
      for (deg = pos; deg != newPos; deg += incr) {
        myservo.write(deg);
        delay(50);
      }
  #else
      myservo.write(newPos);
      delay(abs(newPos-pos) <= 90 ? 400 : 800);
  #endif
      ms = 0;
      myservo.detach();
      digitalWrite(ledPin, 0);
      pos = newPos;
    }
  }
  delay(ms);
}
