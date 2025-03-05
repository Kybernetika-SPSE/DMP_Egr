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

  // Krokový motor
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

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
  startMotor();

  if (digitalRead(IR1) == HIGH) {
    delay(1000); // Nechá dojet kostku pod TCS (vyzkoušet a opravit)
    stopMotor();
    delay(500);

    detectedColor = scanColor();
    Serial.println("Detecovaná barva: " + detectedColor);

    startMotor();
  }

  if (digitalRead(IR2) == HIGH) {
    delay(1000);
    stopMotor();
    delay(500);

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
    
    armReset(); // Base poloha pro rameno
    delay(2000);
  }
}

// Funkce pro spuštění motoru
void startMotor() {
  Serial.println("Motor start");
  digitalWrite(dirPin, HIGH); // Směr pohybu (high = po směru, LOW = proti směru)
  for (int x = 0; x < stepsPerRevolution; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000); // Nastavení rychlosti pohybu
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000); // Nastavení rychlosti pohybu
  }
}

// Funkce pro zastavení motoru
void stopMotor() {
  Serial.println("Motor stop");
  digitalWrite(stepPin, LOW); // LOW = neposíláme impulzy
  digitalWrite(dirPin, LOW);  // Vypneme směr, což často zastaví driver
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

    } else if (red >= 190 && red <= 220 &&
               green >= 140 && green <= 160 &&
               blue >= 150 && blue <= 170) {
      Serial.println("Barva zelená");
      return "G";

    } else if (blue > green && blue > red) { 
      Serial.println("Barva modrá");
      return "B";
    }

    Serial.println("Barva nerozpoznána, opakuji měření...");
    attempts++;
    delay(500); // Počkej půl sekundy před novým měřením
  }
  
  Serial.println("Kostka nebyla rozpoznána");
  return "XXX"; // Vrátí prázdný řetězec, pokud nebyla barva rozpoznána
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

void cubeUknown() {
  moveArm(125, 145, 115, 125, 95, 15);
}

void armReset() {
  moveArm(90, 90, 90, 90, 90, 90); //Nadefinovat pozice
}

void armStup() {
  moveArm(90, 90, 90, 90, 90, 90); //Nadefinovat pozice
}


