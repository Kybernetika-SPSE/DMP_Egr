#include <Servo.h>

#define PIN_OSA1 2
#define PIN_OSA2 3
#define PIN_OSA3 4
#define PIN_OSA4 5
#define PIN_OSA5 6
#define PIN_OSA6 7

Servo osa1, osa2, osa3, osa4, osa5, osa6;
bool running = false;  // Proměnná pro řízení běhu programu

const int DEAD_BAND = 2; // Deadband ±2°

void setup() {
  Serial.begin(9600);
  
  osa1.attach(PIN_OSA1);
  osa2.attach(PIN_OSA2);
  osa3.attach(PIN_OSA3);
  osa4.attach(PIN_OSA4);
  osa5.attach(PIN_OSA5);
  osa6.attach(PIN_OSA6);
  
  armReset();
  Serial.println("Napiš 'start' pro spuštění pohybu ramene.");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command == "start") {
      running = true;
      Serial.println("Rameno se začíná hýbat.");
    } else if (command == "stop") {
      running = false;
      Serial.println("Rameno zastaveno.");
    }
  }
  
  if (running) {
    cubeGrab();
    delay(2000);
  }
}

void moveArm(int a, int b, int c, int d, int e, int f, int steps = 50) {
  int startPos[6] = {osa1.read(), osa2.read(), osa3.read(), osa4.read(), osa5.read(), osa6.read()};
  int endPos[6] = {a, b, c, d, e, f};
  
  float stepSize[6];
  for (int i = 0; i < 6; i++) {
    // Přidán deadband filtr
    if (abs(endPos[i] - startPos[i]) < DEAD_BAND) {
      endPos[i] = startPos[i]; // Nehýbej servem, pokud je rozdíl menší než deadband
    }
    stepSize[i] = (endPos[i] - startPos[i]) / (float)steps;
  }
  
  for (int s = 0; s <= steps; s++) {
    if (!running) return; // Okamžité zastavení při příkazu "stop"
    
    osa1.write(startPos[0] + stepSize[0] * s);
    osa2.write(startPos[1] + stepSize[1] * s);
    osa3.write(startPos[2] + stepSize[2] * s);
    osa4.write(startPos[3] + stepSize[3] * s);
    osa5.write(startPos[4] + stepSize[4] * s);
    osa6.write(startPos[5] + stepSize[5] * s);
    delay(20);
  }
}

void armReset() {
  moveArm(80, 97, 83, 87, 55, 90);
}

void cubeGrab() {
  delay(3000);
  moveArm(80, 75, 180, 114, 47, 40);
  delay(3000);
  moveArm(140, 106, 180, 58, 44, 90);
}
