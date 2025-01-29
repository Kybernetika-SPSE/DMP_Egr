// Define pin connections & motor's steps per revolution
const int dirPin = 51;
const int stepPin = 53;
const int stepsPerRevolution = 3200; // Pro 1/16 mikrokrokování

void setup()
{
    // Declare pins as Outputs
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
}

void loop()
{
    // Set motor direction clockwise
    digitalWrite(dirPin, HIGH);

    // Spin motor at constant speed
    for (int x = 0; x < stepsPerRevolution; x++)
    {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000); // Nastavení rychlosti pohybu
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
    }

    delay(1000); // Wait a second
}
