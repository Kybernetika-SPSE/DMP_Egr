#include <Servo.h>

// Definování pinů na TCS3200
#define S0 52
#define S1 50
#define S2 48
#define S3 46
#define Out A0

// Definování IR pinů
#define IR1 A1
#define IR2 A2

// Definování NEMMA 17
#define dirPin 53
#define stepPin 51
const int stepsPerRevolution = 3600;

// Nastavení globální proměnné pro barvu
String detectedColor = "";

void setup() {
  // TCS3200
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(Out, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Seriová linka
  Serial.begin(9600);

  // IR senzory
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  // Krokový motor
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  // Kontrola prvního IR senzoru
  if (digitalRead(IR1) == HIGH) {
    stopMotor();
    delay(500);

    // Detekce barvy
    detectedColor = scanColor();
    Serial.println("Detected Color: " + detectedColor);

    // Pokračování pásu
    startMotor();
    delay(2000); 
  }

  // Kontrola druhého IR senzoru
  if (digitalRead(IR2) == HIGH) {
    stopMotor();
    delay(500);
    // Simulace ovládání ramene
    Serial.println("Object picked up by robotic arm");
    delay(2000); 

    // Pokračování pásu
    startMotor();
  }
}

// Funkce pro spuštění motoru
void startMotor() {
  Serial.println("Motor start");
  digitalWrite(dirPin, HIGH); // Směr pohybu
  for (int x = 0; x < stepsPerRevolution; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
}

// Funkce pro zastavení motoru
void stopMotor() {
  Serial.println("Motor stop");
}

// Funkce pro detekci barvy
String scanColor() {
  // Nastavení pro čtení konkrétní barvy (R, G, B)
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int red = pulseIn(Out, LOW);
  delay(50);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int green = pulseIn(Out, LOW);¨
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
  Serial.print(blue);

  if (red < green && red < blue) {
    Serial.println("Barva červená");
    return "Red";

  } else if (green < red && green < blue) {
    Serial.println("Barva zelená");
    return "Green";

  } else {
    Serial.println("Barva modrá");
    return "Blue";
  }
}
