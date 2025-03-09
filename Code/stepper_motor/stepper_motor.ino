#define dirPin 50
#define stepPin 52
#define enablePin 48  // Pin pro povolení/vypnutí driveru

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  digitalWrite(enablePin, LOW); // Aktivace driveru
  Serial.begin(9600);
}

void loop() {
  startMotorForever();
}

// ✅ Funkce pro **neustálý chod motoru**
void startMotorForever() {
  Serial.println("Motor běží stále...");
  digitalWrite(enablePin, LOW);
  digitalWrite(dirPin, HIGH); // Směr pohybu

  while (true) {  // Nekonečná smyčka
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000); // Nastavení rychlosti
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000); // Nastavení rychlosti
  }
}
