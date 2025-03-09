#define dirPin 50
#define stepPin 52
#define enablePin 48  // Pin pro povolení/vypnutí driveru
const int stepsPerRevolution = 3200;

void setup()
{
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(enablePin, OUTPUT);

    digitalWrite(enablePin, LOW); // Aktivace driveru
}

void loop()
{
    digitalWrite(dirPin, LOW); // Nastavení směru

    // Provedení otočení
    for (int x = 0; x < stepsPerRevolution; x++)
    {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000); // Nastavení rychlosti pohybu
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
    }



    digitalWrite(enablePin, HIGH); // Vypnutí motoru (uspání)
    
    delay(2000); // Počkáme před dalším pohybem

    digitalWrite(enablePin, LOW); // Opět aktivujeme motor před dalším pohybem
}
