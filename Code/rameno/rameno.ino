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
  
  
  armReset();
}

void loop() {
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
  // Před zapnutím zjistíme aktuální polohu (pokud je známa)
  int lastPos[6] = { osa1.read(), osa2.read(), osa3.read(), osa4.read(), osa5.read(), osa6.read() };

  // Připojení serv, ale bez pohybu
  osa1.attach(PIN_OSA1);
  osa2.attach(PIN_OSA2);
  osa3.attach(PIN_OSA3);
  osa4.attach(PIN_OSA4);
  osa5.attach(PIN_OSA5);
  osa6.attach(PIN_OSA6);

  // Okamžitě servům říct, že mají zůstat na své předchozí pozici
  osa1.write(lastPos[0]);
  osa2.write(lastPos[1]);
  osa3.write(lastPos[2]);
  osa4.write(lastPos[3]);
  osa5.write(lastPos[4]);
  osa6.write(lastPos[5]);

  Serial.println("Rameno aktivováno");
}

void cubeGrab() {
  moveArm(80, 5, 70, 60, 170, 115);
  delay(2000);
  moveArm( 80, 120, 120, 60, 100, 115);
}

void cubeRed() {
  moveArm(125, 125, 135, 105, 75, 25); //Nadefinovat pozice
}

void cubeGreen() {
  moveArm(155, 135, 125, 115, 85, 20); //Nadefinovat pozice
}

void cubeBlue() {
  moveArm(185, 145, 115, 125, 95, 15); //Nadefinovat pozice
}

void cubeUknown() {
  moveArm(125, 145, 115, 125, 95, 15);
}

void armReset() {
  enableArm();
  delay(500);
  moveArm(80, 5, 70, 60, 170, 115);
  disableArm();
}

void armSetup() {
  enableArm();
  moveArm(90, 90, 90, 90, 90, 90); //Nadefinovat pozice
}