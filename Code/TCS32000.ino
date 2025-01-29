// Detektory barvy

// nastavení propojovacích pinů modulu
#define pinS0 52
#define pinS1 50
#define pinS2 48
#define pinS3 46
#define pinOut A8

void setup() {
  // nastavení propojovacích pinů S jako výstupních
  pinMode(pinS0, OUTPUT);
  pinMode(pinS1, OUTPUT);
  pinMode(pinS2, OUTPUT);
  pinMode(pinS3, OUTPUT);
  // nastavení pinu OUT jako vstupního
  pinMode(pinOut, INPUT);
  // inicializace detektoru barev
  digitalWrite(pinS0,HIGH);
  digitalWrite(pinS1,LOW);
  // komunikace přes sériovou linku rychlostí 9600 baud
  Serial.begin(9600);
}
void loop() {
  // proměnné pro uložení frekvencí barev
  int frekvenceCervena, frekvenceZelena, frekvenceModra;
  // nastavení měření červené barvy
  digitalWrite(pinS2,LOW);
  digitalWrite(pinS3,LOW);
  // krátká pauza pro přesné měření
  delay(50);
  // načtení frekvence červené barvy
  frekvenceCervena = pulseIn(pinOut, LOW);
  // nastavení měření zelené barvy
  digitalWrite(pinS2,HIGH);
  digitalWrite(pinS3,HIGH);
  // krátká pauza pro přesné měření
  delay(50);
  // načtení frekvence zelené barvy
  frekvenceZelena = pulseIn(pinOut, LOW);
  // nastavení měření modré barvy
  digitalWrite(pinS2,LOW);
  digitalWrite(pinS3,HIGH);
  // krátká pauza pro přesné měření
  delay(50);
  // načtení frekvence modré barvy
  frekvenceModra = pulseIn(pinOut, LOW);
  // vytištění načtených frekvencí po sériové lince
  Serial.print("R: ");
  Serial.print(frekvenceCervena);
  Serial.print(" | G: ");
  Serial.print(frekvenceZelena);
  Serial.print(" | B: ");
  Serial.print(frekvenceModra);
  // pokud je detekována nějaká z barev, vytiskneme
  // informaci po sériové lince
  if (frekvenceCervena < 60) {
    Serial.print(" | Detekce cervene. ");
  }
  if (frekvenceZelena < 60) {
    Serial.print(" | Detekce zelene. ");
  }
  if (frekvenceModra < 60) {
    Serial.print(" | Detekce modre. ");
  }
  // detekce vlastní barvy složené z různých složek
  if (frekvenceCervena < 60 & frekvenceZelena < 60 ) {
    Serial.print(" | Detekce zlute. ");
  }
  // ukončení řádku
  Serial.println();
  // volitelná pauza pro přehledné čtení výsledků
  delay(850);
}