#include <Servo.h>

// Definování pinů na TCS3200
#define S0 51 // zeleny
#define S1 53 // zluty
#define S2 49 // fialovy
#define S3 47 // modry
#define Out A15 // sedivy

// Definování IR pinů (IR1 = barva, IR2 = rameno)
#define IR1 36 
#define IR2 38

// Definování NEMA 17 (pas)
#define dirPin 50 //zluty
#define stepPin 52 // oranzovy
#define enablePin 48 // zeleny
const int stepsPerRevolution = 3600;

// Deklarace servomotorů pro rameno (1-6)
Servo osa1;
Servo osa2;
Servo osa3;
Servo osa4;
Servo osa5;
Servo osa6;

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
  // Krokový motor
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); // Aktivace driveru
  // Nastavení seriové linky
  Serial.begin(9600);
  
  // TCS3200
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(Out, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // IR senzory
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);




  // Servo inicializace
  osa1.attach(PIN_OSA1);
  osa2.attach(PIN_OSA2);
  osa3.attach(PIN_OSA3);
  osa4.attach(PIN_OSA4);
  osa5.attach(PIN_OSA5);
  osa6.attach(PIN_OSA6);

  //armSetup(); //Uhel 90 všechny
  //armReset(); // Uhel kdy bude rameno sedět 
}

void loop() {

  delay(1000);

  startMotorUntilSensor();
  stopMotor();

  delay(1000);

  detectedColor = scanColor();
  Serial.println("Detecovaná barva: " + detectedColor);

  delay(1000);

  startMotorUntilSensor();
  stopMotor();

    if (detectedColor == "R") {
      Serial.println("Cervena kostka");;
      //cubeGrab();
      //cubeRed(); // Pozice s červenou
    } else if (detectedColor == "G") {
      Serial.println("Zelena kostka");
      //cubeGrab()
      //cubeGreen(); // Pozice se zelenou
    } else if (detectedColor == "B") {
      Serial.println("Modra kostka");
      //cubeGrab()
      //cubeBlue(); // Pozice s modrou
    } else if (detectedColor == "XXX") {
      Serial.println("Neznama kostka");
      startMotorForDuration(3000); // Spuštění motoru na 5 sekund
      Serial.println("Neznama kostka pryč");      
    }
  delay(1000);
  Serial.println("Cyklus dokončen");
}




// Funkce pro spuštění motoru **dokud nesepne kterýkoliv IR senzor**
void startMotorUntilSensor() {
  Serial.println("Motor start");
  digitalWrite(enablePin, LOW);
  digitalWrite(dirPin, HIGH); // Směr pohybu

  while (digitalRead(IR1) == HIGH && digitalRead(IR2) == HIGH) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
  
  if (digitalRead(IR1) == LOW) {
    Serial.println("IR1 aktivován - pokračuji ještě x kroků");
    int steps = 400;
    for (int i = 0; i < steps; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000); // Délka pulzu pro řízení rychlosti
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1000);
    }
  }
  if (digitalRead(IR2) == LOW) {
    Serial.println("IR2 aktivován - pokračuji ještě x kroků");
    int steps = 1000;
    for (int i = 0; i < steps; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000); // Délka pulzu pro řízení rychlosti
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1000);
    }
  }
  int steps = 0;

}


// Funkce pro zastavení motoru
void stopMotor() {
  Serial.println("Motor stop");
  digitalWrite(enablePin, HIGH);
}

void startMotorForDuration(int duration) {
  Serial.println("Motor běží po dobu " + String(duration) + " ms");
  digitalWrite(enablePin, LOW);
  digitalWrite(dirPin, HIGH);

  for (int i = 0; i < duration / 4; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }

  stopMotor();
  Serial.println("Kostka pryč");
  delay(3000);
}

// Funkce pro detekci barvy
String scanColor() {
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
      return "R";
    } else if (green < 50) {
      Serial.println("Barva zelená");
      return "G";
    } else if (blue < 50) { 
      Serial.println("Barva modrá");
      return "B";
    }

    Serial.println("Barva nerozpoznána, opakuji měření...");
    attempts++;
    delay(500); // Počkej půl sekundy před novým měřením
  }

  Serial.println("Neznámá kostka, vracím XXX");
  return "XXX";
}


void moveArm(int a, int b, int c, int d, int e, int f) {
  osa1.write(a);
  osa2.write(b);
  osa3.write(c);
  osa4.write(d);
  osa5.write(e);
  osa6.write(f);
  delay(200);
}

void cubeGrab() {
  moveArm(90, 120, 150, 90, 60, 45); //Nadefinovat pozice
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

void armReset() {
  moveArm(90, 90, 90, 90, 90, 90); //Nadefinovat pozice
}

void armSetup() {
  moveArm(90, 90, 90, 90, 90, 90); //Nadefinovat pozice
}
