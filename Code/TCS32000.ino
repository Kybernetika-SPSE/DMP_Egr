// Detektory barvy

// nastavení propojovacích pinů modulu
#define pinS0 51
#define pinS1 53
#define pinS2 49
#define pinS3 45
#define pinOut A7


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

  // nastavení měření zelené barvy
  digitalWrite(pinS2,HIGH);
  digitalWrite(pinS3,HIGH);
  delay(50);
  frekvenceZelena = pulseIn(pinOut, LOW);

  // nastavení měření modré barvy
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

  // Kontrola detekce pro každou barvu
  if (frekvenceCervena < 60) {
    Serial.print(" | Detekce cervene. ");
  }

  if (frekvenceCervena >= 190 && frekvenceCervena <= 220,
      frekvenceZelena >= 140 && frekvenceZelena <= 160,
      frekvenceModra >= 150 && frekvenceModra <= 170) {
    Serial.print(" | Detekce zelene. ");
  }

  if (frekvenceModra < 60) {
    Serial.print(" | Detekce modre. ");
  }

  // ukončení řádku
  Serial.println();
  delay(1000);
}
