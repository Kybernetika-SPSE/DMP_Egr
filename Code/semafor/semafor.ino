#include <Arduino.h>
#define CERVENA 8 //nadefinujeme červené diodu na pin 6
#define ZLUTA 9 //nadefinujeme žlutou diodu na pin 8
#define ZELENA 10 //nadefinujeme zelenou diodu na pin 7
int pauza = 1000; //nastavíme si jak dlouhou chceme pauzu
void setup() {
pinMode(CERVENA,OUTPUT); //nastavíme všechny piny na výstup
pinMode(ZLUTA, OUTPUT);
pinMode(ZELENA, OUTPUT);
}
void loop() {
 //HIGH = svítí, LOW = nesvítí
 digitalWrite(CERVENA, HIGH);
 digitalWrite(ZLUTA, HIGH);
 digitalWrite(ZELENA, HIGH);
 delay(pauza);

 digitalWrite(CERVENA, HIGH);
 digitalWrite(ZLUTA, LOW);
 digitalWrite(ZELENA, LOW);
 delay(pauza);
 digitalWrite(CERVENA, LOW);
 digitalWrite(ZLUTA, HIGH);
 digitalWrite(ZELENA, LOW);
 delay(pauza);
 digitalWrite(CERVENA, LOW);
 digitalWrite(ZLUTA, LOW);
 digitalWrite(ZELENA, HIGH);
 delay(pauza);
}