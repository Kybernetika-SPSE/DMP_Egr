// Akustický bzučák

// proměnná pro nastavení propojovacího pinu
int bzucak = 52;

void setup() {
  // nastavení propojovacího pinu jako výstupního
  pinMode(bzucak, OUTPUT);
  // vzhledem k tomu, že náš bzučák je
  // aktivní v nule, tedy LOW, je nutné
  // ho po dohrání nastavit na vysokou
  // úroveň, aby jsme zamezili bzučení
  // v pauzách
  digitalWrite(bzucak, HIGH);
}

void loop() {
  // v nekonečné smyčce for, která proběhne
  // pro hodnoty i 1 až 10, se vždy zavolá
  // funkce zahraj, která zahraje zvuk o
  // nastavené frekvenci a délce zadané ve tvaru
  // zahraj(frekvence, doba), kde frekvence
  // je v Hertzech a doba v milisekundách
  for (int i=1; i < 11; i++) {
    // frekvence se rovná i-násobku 100,
    // zde tedy bude v rozsahu 100 až 1000 Hz,
    // doba hraní je pak 50 milisekund
    zahraj(100*i, 50);
    // po každé frekvenci následuje pauza 250 ms
    // pro rozeznání frekvencí
    delay(250);
  }
  // pauza 2 vteřiny pro rozeznání konce smyčky
  delay(2000);
}
// podprogram zahraj obsahuje všechny důležité
// funkce pro zahrání zadaného zvuku
void zahraj(int frekvence, int doba) {
  // funkce tone má na prvním místě pin
  // s připojeným bzučákem, na druhém
  // frekvenci hraného zvuku a na třetím
  // dobu hraní zvuku v milisekundách;
  // maximální frekvence je 65535 Hz,
  // pro člověka neslyšitelná frekvence
  tone(bzucak, frekvence, doba);
  delay(doba);
  digitalWrite(bzucak, HIGH);
}