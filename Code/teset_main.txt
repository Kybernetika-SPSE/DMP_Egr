#include <Arduino.h>
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

// RGB LED modul KY-016
#define pinR 10 // bílý
#define pinG 9 //šedivy
#define pinB 8 // fialový
const int maxSvit = 50;

// semafor
#define cervena_semafor 13 //bílá
#define zluta_semafor 12 //šedivý
#define zelena_semafor 11 //fialová
int pauza = 1000; //nastavíme si jak dlouhou chceme pauzu

//bzucak
#define BUZZER_PIN 40


// Nastavení globální proměnné pro barvu
String detectedColor = "";

String barva = "";

// Funkce pro debouncing IR senzoru
bool isSensorLowDebounced(int sensorPin, int debounceDelay = 10) {
  if (digitalRead(sensorPin) == LOW) {
    delay(debounceDelay);
    if (digitalRead(sensorPin) == LOW) {
      if (digitalRead(sensorPin) == LOW) {
        delay(debounceDelay);
        if (digitalRead(sensorPin) == LOW) {
          return true;
        }
      }
    }
  }
  return false;
}


void setup() {
  // semafor
  pinMode(cervena_semafor, OUTPUT);
  pinMode(zluta_semafor, OUTPUT);
  pinMode(zelena_semafor, OUTPUT);

  //rgb modul
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);

  //bzucak
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, HIGH); // Bzučák vypnutý po startu

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
  delay(2000);
  enableArm();
  delay(1000);
  armReset();

  delay(500);
  semafor("cervena");
  startMotorForDuration(3000);
  stopMotor();
  delay(1000);
  semafor("zelena");
}

void loop() {
  semafor("zelena");
  
  // Spustí motor a čeká pouze na aktivaci IR1
  startMotorUntilSensorPin(IR1, 400);
  stopMotor();
  semafor("zluta");


  delay(1000);

  detectedColor = scanColor();
  Serial.println("Detekovaná barva: " + detectedColor);

  if (detectedColor == "R") {
    nastavRGB(maxSvit, 0, 0);
  } else if (detectedColor == "G") {
    nastavRGB(0, maxSvit, 0);
  } else if (detectedColor == "B") {
    nastavRGB(0, 0, maxSvit);
  }

  delay(1000);
  
  // Opět spustí motor a čeká na aktivaci IR1
  startMotorUntilSensorPin(IR2, 1000);
  stopMotor();

  if (detectedColor == "R") {
    Serial.println("Cervena kostka");
    enableArm();
    cubeGrab();
    cubeRed();
    armReset();
  } else if (detectedColor == "G") {
    Serial.println("Zelena kostka");
    enableArm();
    cubeGrab();
    cubeGreen();
    armReset();
  } else if (detectedColor == "B") {
    Serial.println("Modra kostka");
    enableArm();
    cubeGrab();
    cubeBlue();
    armReset();
  } else if (detectedColor == "XXX") {
    Serial.println("Neznama kostka");
    startMotorForDuration(3000); // Spuštění motoru na 3 sekundy
    Serial.println("Neznama kostka pryč");      
  }
  delay(1000);
  nastavRGB(0, 0, 0);
  Serial.println("Cyklus dokončen");

}

// Funkce pro spuštění motoru **dokud nesepne kterýkoliv IR senzor**
void startMotorUntilSensorPin(int sensorPin, int extraSteps) {
  Serial.println("Motor start");
  digitalWrite(enablePin, LOW);
  digitalWrite(dirPin, HIGH); // Směr pohybu

  // Motor běží, dokud zvolený senzor nedetekuje stabilní LOW signál
  while (!isSensorLowDebounced(sensorPin)) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
  
  // Po detekci provede definovaný počet extra kroků
  Serial.print("Senzor na pinu ");
  Serial.print(sensorPin);
  Serial.println(" aktivován - pokračuji ještě extra kroky");
  for (int i = 0; i < extraSteps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
  
  // Po provedení extra kroků počká, dokud se senzor neuvolní
  while (digitalRead(sensorPin) == LOW) {
    delay(10);
  }
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
    if (red < 30) {
      Serial.println("Barva červená");
      return "R";
    } else if (green < 30) {
      Serial.println("Barva zelená");
      return "G";
    } else if (blue < 30) { 
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
  delay(200);
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


void semafor(String barva) {
    digitalWrite(cervena_semafor, LOW);
    digitalWrite(zluta_semafor, LOW);
    digitalWrite(zelena_semafor, LOW);
    
    if (barva == "cervena") {
        digitalWrite(cervena_semafor, HIGH);
    } else if (barva == "zluta") {
        digitalWrite(zluta_semafor, HIGH);
    } else if (barva == "zelena") {
        digitalWrite(zelena_semafor, HIGH);
    }
}

void nastavRGB(int cervena, int zelena, int modra) {
  // nastavení všech barev na zvolené intenzity
  analogWrite(pinR, cervena);
  analogWrite(pinG, zelena);
  analogWrite(pinB, modra);
}

void bzucakon(int frekvence, int doba, int pauza) {
  unsigned long startTime = millis();
  // Smyčka poběží, dokud neuplyne 10 sekund
  while (millis() - startTime < 10000) {
    tone(BUZZER_PIN, frekvence, doba); // Spustí tón na dobu "doba"
    delay(doba);                      // Počká, než tón skončí
    noTone(BUZZER_PIN);               // Vypne tón (pro jistotu)
    delay(pauza);                     // Pauza mezi tóny
  }
}

