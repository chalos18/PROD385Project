#include <Servo.h>

Servo myServo;

const int servoPin = 9;

// Tuning values (adjust these)
int angle = 90;          // Start position (center)
int stepSize = 3;        // Small movement increment
int minAngle = 70;       // Lower limit (rope unwind)
int maxAngle = 110;      // Upper limit (rope wind)
int moveDelay = 2000;    // Time between movements (ms)

int direction = 1;       // 1 = forward, -1 = backward

void setup() {
  myServo.attach(servoPin);
  myServo.write(angle);
}

void loop() {
  // angle += stepSize * direction;

  // // Reverse direction at limits
  // if (angle >= maxAngle || angle <= minAngle) {
  //   direction = -direction;
  // }

  // myServo.write(angle);
  // delay(moveDelay);
}


// void loop() {
  // Wind the string (0 → 180)
  // myServo.write(180);
  // delay(500);   // time to fully wind (adjust)

  // // Unwind the string (180 → 0)
  // myServo.write(0);
  // delay(500);   // time to fully unwind
// }

// #include <Servo.h>

// Servo myServo;

// int servoPin = 9;
// int counter = 1;   // global counter

// void setup() {
//   myServo.attach(servoPin);
// }

// void loop() {
//   if (counter == 0) {
//     myServo.detach();
//   }
//   if (counter > 0) {
//     // Sweep 0 → 180
//     for (int angle = 0; angle <= 180; angle++) {
//       myServo.write(angle);
//       delay(25);
//     }

//     // Sweep 180 → 0
//     for (int angle = 180; angle >= 0; angle--) {
//       myServo.write(angle);
//       delay(25);
//     }

//     counter--;   // decrease after one full cycle
//   }
// }
