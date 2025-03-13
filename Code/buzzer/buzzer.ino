// Akustický bzučák

int bzucak = 52;
int frekvence = 200;  // Zadej frekvenci v Hz
int doba = 1000;      // Zadej dobu bzučení v ms

void setup() {
  pinMode(bzucak, OUTPUT);
  digitalWrite(bzucak, HIGH); // Vypnutí bzučáku po startu
  zahraj(frekvence, doba);
}

void loop() {
  zahraj(frekvence, doba);
  delay(2000);
}

void zahraj(int frekvence, int doba) {
  tone(bzucak, frekvence, doba);
  delay(doba);
  digitalWrite(bzucak, HIGH); // Vypnutí bzučáku po skončení
}
