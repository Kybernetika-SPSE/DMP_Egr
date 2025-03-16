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
  
  enableArm();
  delay(1000);


  cubeGrab();
  cubeRed();
  Serial.println("Cyklus červené");

  delay(1000);

  cubeGrab();
  cubeGreen();
  Serial.println("Cyklus zelené");

  delay(1000);

  cubeGrab();
  cubeBlue();
  Serial.println("Cyklus modré");

  delay(1000);


  armReset();
}

void loop() {

}

void moveArm(int a, int b, int c, int d, int e, int f, int steps = 40) {
  int startPos[6] = {osa1.read(), osa2.read(), osa3.read(), osa4.read(), osa5.read(), osa6.read()};
  int endPos[6] = {a, b, c, d, e, f};
  
  for (int s = 0; s <= steps; s++) {
    float t = (float)s / steps;
    // Smoothstep easing function: cubic interpolation for ease in/out
    float ease = t * t * (3 - 2 * t);
    
    osa1.write(startPos[0] + (endPos[0] - startPos[0]) * ease);
    osa2.write(startPos[1] + (endPos[1] - startPos[1]) * ease);
    osa3.write(startPos[2] + (endPos[2] - startPos[2]) * ease);
    osa4.write(startPos[3] + (endPos[3] - startPos[3]) * ease);
    osa5.write(startPos[4] + (endPos[4] - startPos[4]) * ease);
    osa6.write(startPos[5] + (endPos[5] - startPos[5]) * ease);
    
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
  osa1.write(85);
  osa2.attach(PIN_OSA2);
  osa2.write(5);
  osa3.attach(PIN_OSA3);
  osa3.write(70);
  osa4.attach(PIN_OSA4);
  osa4.write(170);
  osa5.attach(PIN_OSA5);
  osa5.write(60);
  osa6.attach(PIN_OSA6);
  osa6.write(80);
  Serial.println("Rameno aktivováno");
}

void cubeGrab() {
  moveArm(85, 120, 120, 100, 60, 80); //zvedne se z resetu +
  delay(500);
  moveArm(175, 120, 120, 100, 60, 25); // otočí se k pásu a otevřeruku *
  delay(500); 
  moveArm(175, 70, 87, 115, 60, 25); // nahne se k pásu -
  delay(500);
  moveArm(175, 70, 87, 115, 60, 57); //chycení kostky -
  delay(500);
  moveArm(175, 120, 120, 100, 60, 57); // oddálí se od pásu * (zavřena s kostkou)
  delay(500);
  moveArm( 85, 120, 120, 100, 60, 57); //otočí se zpět + (zavřena s kostkou)
  delay(500);
}


void armReset() {
  moveArm(85, 5, 70, 170, 60, 80);
  delay(1000);
  disableArm();
}

void cubeRed() {
  moveArm(110, 80, 80, 100, 60, 57); // nahnutí nad místo odhozu
  delay(500);
  moveArm(110, 80, 80, 100, 60, 25); // shození
  delay(500);
  moveArm(85, 120, 120, 100, 60, 80); // nahnutí zpátky
  delay(500);
}

void cubeGreen() {
  moveArm(85, 40, 20, 90, 60, 57); // nahnutí nad místo odhozu
  delay(500);
  moveArm(85, 40, 20, 90, 60, 25); // shození
  delay(500);
  moveArm(85, 120, 120, 100, 60, 80); // nahnutí zpátky
  delay(500);
}

void cubeBlue() {
  moveArm(55, 80, 80, 100, 60, 57);// nahnutí nad místo odhozu
  delay(500);
  moveArm(55, 80, 80, 100, 60, 25); // shození
  delay(500);
  moveArm(85, 120, 120, 100, 60, 80); // nahnutí zpátky
  delay(500);
}