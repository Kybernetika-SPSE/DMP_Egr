#include <Servo.h>

#define PIN_OSA1 2
#define PIN_OSA2 3
#define PIN_OSA3 4
#define PIN_OSA4 5
#define PIN_OSA5 6
#define PIN_OSA6 7

Servo osa1, osa2, osa3, osa4, osa5, osa6;
int uhly[6] = {90, 90, 90, 90, 90, 60}; // Výchozí úhly

void setup() {
  Serial.begin(9600);
  Serial.println("Zadejte cislo osy (1-6) a uhel (0-180), napr.: '1 90'");
  Serial.println("Pro vypis uhlu napiste: final");

  osa1.attach(PIN_OSA1);
  osa2.attach(PIN_OSA2);
  osa3.attach(PIN_OSA3);
  osa4.attach(PIN_OSA4);
  osa5.attach(PIN_OSA5);
  osa6.attach(PIN_OSA6);

  // Serva nastavíme na výchozí pozici
  osa1.write(uhly[0]);
  osa2.write(uhly[1]);
  osa3.write(uhly[2]);
  osa4.write(uhly[3]);
  osa5.write(uhly[4]);
  osa6.write(uhly[5]);
}

void loop() {
  if (Serial.available()) {
    String vstup = Serial.readStringUntil('\n'); // Načtení celého řádku
    vstup.trim(); // Odstranění bílých znaků

    if (vstup == "final") {
      vypisUhly();
    } else {
      int osa, uhel;
      if (sscanf(vstup.c_str(), "%d %d", &osa, &uhel) == 2) {
        if (osa >= 1 && osa <= 6 && uhel >= 0 && uhel <= 180) {
          moveServoSmooth(osa, uhel, 50);
          uhly[osa - 1] = uhel;
          Serial.print("Osa "); Serial.print(osa);
          Serial.print(" nastavena na "); Serial.print(uhel);
          Serial.println("°");
        } else {
          Serial.println("Neplatny vstup, zadejte cislo osy (1-6) a uhel (0-180)");
        }
      }
    }
  }
}

void moveServoSmooth(int osa, int uhel, int steps) {
  Servo *servo;
  switch (osa) {
    case 1: servo = &osa1; break;
    case 2: servo = &osa2; break;
    case 3: servo = &osa3; break;
    case 4: servo = &osa4; break;
    case 5: servo = &osa5; break;
    case 6: servo = &osa6; break;
    default: return;
  }
  
  int startPos = servo->read();
  float stepSize = (uhel - startPos) / (float)steps;
  
  for (int s = 0; s <= steps; s++) {
    servo->write(startPos + stepSize * s);
    delay(20);
  }
}

void vypisUhly() {
  Serial.println("Aktualni uhly serv:");
  for (int i = 0; i < 6; i++) {
    Serial.print("Osa "); Serial.print(i + 1);
    Serial.print(": "); Serial.print(uhly[i]);
    Serial.println("°");
  }
}
