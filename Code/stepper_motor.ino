#define dirPin = 51;
#define stepPin = 53;
const int stepsPerRevolution = 3200; 

void setup()
{
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
}

void loop()
{
    // Nastavení směru otočení (high = po směru, LOW = proti směru)
    digitalWrite(dirPin, HIGH);

    for (int x = 0; x < stepsPerRevolution; x++)
    {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000); // Nastavení rychlosti pohybu
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
    }

    delay(1000);
}
