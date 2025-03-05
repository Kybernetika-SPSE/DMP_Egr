
#include <Servo.h>

Servo servo_0; // Declaración del objeto para controlar el primer servo
Servo servo_1; // Declaración del objeto para controlar el segundo servo
Servo servo_2; // Declaración del objeto para controlar el tercer servo
Servo servo_3; // Declaración del objeto para controlar el cuarto servo
Servo servo_4; // Declaración del objeto para controlar el quinto servo
Servo servo_5; // Declaración del objeto para controlar el sexto servo
Servo servo_6; // Declaración del objeto para controlar el sexto servo

void setup() {
  Serial.begin(9600); // Inicializar comunicación serial
  servo_0.attach(7); // Asocia el servo_0 al pin 2        X
  servo_1.attach(6); // Asocia el servo_1 al pin 3        X
  servo_2.attach(5); // Asocia el servo_2 al pin 4        X
  servo_3.attach(4); // Asocia el servo_3 al pin 5        X
  servo_4.attach(3); // Asocia el servo_4 al pin 6        X     
  servo_5.attach(2); // Asocia el servo_5 al pin 7        X
}

void loop() {
  if (Serial.available() > 0) { // Si hay datos disponibles para leer
    String input = Serial.readStringUntil('\n'); // Leer la cadena de datos hasta el salto de línea
    int servoIndex = input.substring(0, 1).toInt(); // Obtener el índice del servo
    int servoValue = input.substring(2).toInt(); // Obtener el valor del servo
    
    switch (servoIndex) {
      case 1:
        servo_0.write(servoValue);
        break;
      case 2:
        servo_1.write(servoValue);
        break;
      case 3:
        servo_2.write(servoValue);
        break;
      case 4:
        servo_3.write(servoValue);
        break;
      case 5:
        servo_4.write(servoValue);
        break;
      case 6:
        servo_5.write(servoValue);
        
        break;
      default:
        // Índice de servo inválido
        break;
    }
  }
}