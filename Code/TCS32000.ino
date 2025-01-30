// Detektory barvy

// nastavení propojovacích pinů modulu
#define pinS0 44
#define pinS1 46
#define pinS2 50
#define pinS3 48
#define pinOut 52

void setup() {
  pinMode(pinS0, OUTPUT);
  pinMode(pinS1, OUTPUT);
  pinMode(pinS2, OUTPUT);
  pinMode(pinS3, OUTPUT);
  pinMode(pinOut, INPUT);
  digitalWrite(pinS0,HIGH);
  digitalWrite(pinS1,LOW);

  Serial.begin(9600);
}

void loop() {

  int frekvenceCervena, frekvenceZelena, frekvenceModra;
  // nastavení měření červené barvy
  digitalWrite(pinS2,LOW);
  digitalWrite(pinS3,LOW);
  delay(50);

  frekvenceCervena = pulseIn(pinOut, LOW);
  digitalWrite(pinS2,HIGH);
  digitalWrite(pinS3,HIGH);

  delay(50);

  frekvenceZelena = pulseIn(pinOut, LOW);
  digitalWrite(pinS2,LOW);
  digitalWrite(pinS3,HIGH);

  delay(50);
  frekvenceModra = pulseIn(pinOut, LOW);
  // vytištění načtených frekvencí po sériové lince
  Serial.print("R: ");
  Serial.print(frekvenceCervena);
  Serial.print(" | G: ");
  Serial.print(frekvenceZelena);
  Serial.print(" | B: ");
  Serial.print(frekvenceModra);

  if (frekvenceCervena < 60) {
    Serial.print(" | Detekce cervene. ");
  }
  if (frekvenceZelena < 60) {
    Serial.print(" | Detekce zelene. ");
  }
  if (frekvenceModra < 60) {
    Serial.print(" | Detekce modre. ");
  }

  // ukončení řádku
  Serial.println();
  // volitelná pauza pro přehledné čtení výsledků
  delay(850);
}