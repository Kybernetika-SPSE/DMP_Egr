#include <Servo.h>

// Definování pinů na TCS3200
#define S0 51
#define S1 53
#define S2 49
#define S3 45
#define Out A7

// Definování IR pinů (IR1 = barva, IR2 = rameno)
#define IR1 36 
#define IR2 38

// Definování NEMA 17 (pas)
#define dirPin 50
#define stepPin 52
#define enablePin 48

// Deklarace servomotorů pro rameno (1-6)
Servo osa1, osa2, osa3, osa4, osa5, osa6;

// Piny pro připojení servomotorů
#define PIN_OSA1 2
#define PIN_OSA2 3
#define PIN_OSA3 4
#define PIN_OSA4 5
#define PIN_OSA5 6
#define PIN_OSA6 7

// Nastavení globální proměnné pro barvu
String detectedColor = "";

void setup() {
  // Nastavení seriové linky
  Serial.begin(9600);
  
  // TCS3200
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(Out, INPUT);
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);

  // IR senzory
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  // Krokový motor
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
   pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); // Aktivace driveru

  // Servo inicializace
  osa1.attach(PIN_OSA1);
  osa2.attach(PIN_OSA2);
  osa3.attach(PIN_OSA3);
  osa4.attach(PIN_OSA4);
  osa5.attach(PIN_OSA5);
  osa6.attach(PIN_OSA6);

  armSetup(); //Uhel 90 všechny
  armReset(); // Uhel kdy bude rameno sedět 


}

void loop() {
  startMotorUntilSensor(IR1);

  delay(1000); // Nechá dojet kostku pod TCS (vyzkoušet a opravit)
  stopMotor();

  delay(500);

  detectedColor = scanColor();
  Serial.println("Detecovaná barva: " + detectedColor);

  startMotorUntilSensor(IR2);
  delay(1000);
  stopMotor();

  Serial.println("Rameno aktivováno");
  cubeGrab();

  if (detectedColor == "R") {
    cubeRed(); // Pozice s červenou
  } else if (detectedColor == "G") {
    cubeGreen(); // Pozice se zelenou
  } else if (detectedColor == "B") {
    cubeBlue(); // Pozice s modrou
  } else if (detectedColour == "XXX") {
    cubeUknown();
  }
    
  armReset(); // Reset ramena na základní pozici + vypnutí
  delay(2000);
  }
}

// Funkce pro spuštění motoru
void startMotorUntilSensor() {
  Serial.println("Motor start");
  digitalWrite(enablePin, LOW);
  digitalWrite(dirPin, HIGH); // Směr pohybu

  while (digitalRead(IRsensor) == HIGH) {  // Motor běží, dokud není senzor aktivován
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }

  Serial.println("Senzor aktivován - zastavuji motor!");
}

// Funkce pro zastavení motoru
void stopMotor() {
  Serial.println("Motor stop");
  digitalWrite(enablePin, HIGH);
}

// Funkce pro detekci barvy
String scanColor() {
  digitalWrite(S0, HIGH); // Zapnutí senzoru
  digitalWrite(S1, LOW);
  delay(100);

  int attempts = 0;
  while (attempts < 5) { // Opakuj měření maximálně 5x
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    int red = pulseIn(Out, LOW);
    delay(50);

    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    int green = pulseIn(Out, LOW);
    delay(50);

    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    int blue = pulseIn(Out, LOW);
    delay(50);

    Serial.print("R: ");
    Serial.print(red);
    Serial.print(" | G: ");
    Serial.print(green);
    Serial.print(" | B: ");
    Serial.println(blue);

    // Rozhodování o barvě
    if (red < 60) {
      Serial.println("Barva červená");
      digitalWrite(S0, LOW); // Vypnutí senzoru
      return "R";

    } else if (red >= 190 && red <= 220 &&
               green >= 140 && green <= 160 &&
               blue >= 150 && blue <= 170) {
      Serial.println("Barva zelená");
      digitalWrite(S0, LOW); // Vypnutí senzoru
      return "G";

    } else if (blue > green && blue > red) { 
      Serial.println("Barva modrá");
      digitalWrite(S0, LOW); // Vypnutí senzoru
      return "B";
    }

    Serial.println("Barva nerozpoznána, opakuji měření...");
    attempts++;
    delay(500); // Počkej půl sekundy před novým měřením
  }
  
  Serial.println("Kostka nebyla rozpoznána");
  digitalWrite(S0, LOW); // Vypnutí senzoru
  return "XXX"; // Barva rozpoznána
}



void moveArm(int a, int b, int c, int d, int e, int f, int steps = 50) {
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
  moveArm(0, 120, 50, 90, 60, 45); //Nadefinovat pozice
  moveArm(90, 120, 150, 48, 60, 45); //Nadefinovat pozice
  moveArm(90, 0, 150, 90, 60, 45); //Nadefinovat pozice
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
  // vyhození motorem
}

void armReset() {
  enableArm();
  moveArm(90, 90, 90, 90, 90, 90); //Nadefinovat pozice
  disableArm();
}

void armSetup() {
  enableArm();
  moveArm(90, 90, 90, 90, 90, 90); //Nadefinovat pozice
}


