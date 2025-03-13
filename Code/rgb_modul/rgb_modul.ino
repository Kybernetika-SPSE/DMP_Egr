// RGB LED modul KY-016

// nastavení vstupních pinů
#define pinR 10
#define pinG 9
#define pinB 8
// proměnná obsahující maximální svítivost LED diod
const int maxSvit = 50;

void setup() {
  // nastavení pinů pro LED jako výstup
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
}

void loop() {
  // Rozsvícení červené
  nastavRGB(maxSvit, 0, 0);
  delay(1000); // čekání 1 sekundu

  // Rozsvícení zelené
  nastavRGB(0, maxSvit, 0);
  delay(1000); // čekání 1 sekundu

  // Rozsvícení modré
  nastavRGB(0, 0, maxSvit);
  delay(1000); // čekání 1 sekundu
}

void nastavRGB(int cervena, int zelena, int modra) {
  // nastavení všech barev na zvolené intenzity
  analogWrite(pinR, cervena);
  analogWrite(pinG, zelena);
  analogWrite(pinB, modra);
}