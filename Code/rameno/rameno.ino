#include <Servo.h>

#define PIN_OSA1 2
#define PIN_OSA2 3
#define PIN_OSA3 4
#define PIN_OSA4 5
#define PIN_OSA5 6
#define PIN_OSA6 7

Servo osa1, osa2, osa3, osa4, osa5, osa6;

void setup() {
  Serial.begin(9600);
  
  osa1.attach(PIN_OSA1);
  osa2.attach(PIN_OSA2);
  osa3.attach(PIN_OSA3);
  osa4.attach(PIN_OSA4);
  osa5.attach(PIN_OSA5);
  osa6.attach(PIN_OSA6);
  
  
  armReset();
}

void loop() {
  armReset();
  
  while (true);
}

void moveArm(int a, int b, int c, int d, int e, int f, int steps = 75) {
  int startPos[6] = {osa1.read(), osa2.read(), osa3.read(), osa4.read(), osa5.read(), osa6.read()};
  int endPos[6] = {a, b, c, d, e, f};
  
  float stepSize[6];
  for (int i = 0; i < 6; i++) {
    stepSize[i] = (endPos[i] - startPos[i]) / (float)steps;
  }
  
  for (int s = 0; s <= steps; s++) {
    osa1.write(startPos[0] + stepSize[0] * s);
    osa2.write(startPos[1] + stepSize[1] * s);
    osa3.write(startPos[2] + stepSize[2] * s);
    osa4.write(startPos[3] + stepSize[3] * s);
    osa5.write(startPos[4] + stepSize[4] * s);
    osa6.write(startPos[5] + stepSize[5] * s);
    delay(20);
  }
}

void disableArm() {
  osa1.detach();
  osa2.detach();
  osa3.detach();
  osa4.detach();
  osa5.detach();
  osa6.detach();
  Serial.println("Rameno vypnuto");
}

void enableArm() {
  // Připojení serv, ale bez pohybu
  osa1.attach(PIN_OSA1);
  osa2.attach(PIN_OSA2);
  osa3.attach(PIN_OSA3);
  osa4.attach(PIN_OSA4);
  osa5.attach(PIN_OSA5);
  osa6.attach(PIN_OSA6);


  Serial.println("Rameno aktivováno");
}

void cubeGrab() {
  enableArm();
  moveArm(80, 120, 120, 60, 100, X); //zvedne se z resetu +
//delay?
  moveArm(175, 120, 120, 60, 100, X); // otočí se k pásu a otevřeruku *
  delay?
 moveArm(175, 80, 100, 60, 115, X); // nahne se k pásu -
//delay?
  moveArm(175, 80, 100, 60, 115, X); //chycení kostky -
//delay?
  moveArm(175, 120, 120, 60, 100, X); // oddálí se od pásu * (zavřená ruka!!)
//delay?
  moveArm(90, 120, 120, 60, 100, X); //otočí se zpět +
// navazují barvy
}


void armReset() {
  moveArm(80, 5, 70, 60, 170, 115);
  disableArm();
}

void armSetup() {
  moveArm(90, 90, 90, 90, 90, 90); //Nadefinovat pozice
}