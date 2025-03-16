#include <Arduino.h>
#include <Servo.h>

// ... zbytek tvých definic a funkcí

#define BUZZER_PIN 40  // Přidán pin pro bzučák

// Inicializace bzučáku
void initBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, HIGH); // Vypnutí bzučáku po startu
}

// Funkce pro přehrání tónu
void bzucakon(int frekvence, int doba, int pauza) {
  while (true) {
    tone(BUZZER_PIN, frekvence, doba); // Spustí tón
    delay(doba);                      // Doba bzučení
    noTone(BUZZER_PIN);               // Vypne tón
    delay(pauza);                     // Pauza mezi tóny
  }
}

void bzucakoff() {
  digitalWrite(BUZZER_PIN, HIGH); // Vypni bzučák
}
void setup() {
  // Inicializace ostatních pinů a zařízení...
  
  // Inicializace bzučáku
  initBuzzer();
  
  // Můžeš zde také přehrát testovací tón:
  bzucakon(200, 1000, 1000); // 200 Hz, 1000 ms
  delay(10000);

  bzucakoff();
}

void loop() {

  
  // ... zbytek tvého kódu
}
