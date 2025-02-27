#define irSensorPin 36  // Nebo alternativně: const int irSensorPin = 38, 36

void setup() {
  pinMode(irSensorPin, INPUT);
  Serial.begin(9600); 
}

void loop() {
  int sensorValue = digitalRead(irSensorPin);

  if (sensorValue == LOW) {
    // Obstacle detected
    Serial.println("Obstacle detected!");
  } else {
    // No obstacle
    Serial.println("No obstacle.");
  }

  delay(1000);
}
