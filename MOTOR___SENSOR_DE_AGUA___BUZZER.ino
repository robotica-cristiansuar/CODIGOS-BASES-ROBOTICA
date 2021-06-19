#include <EasyBuzzer.h>
#include <TB6612_ESP32.h>
int BUZZER_PIN = 27;

// MOTOR2
# define  BIN1  25
# define  BIN2  26
# define  PWMB  14

const int offsetB = 1;

Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, 0, 5000, 8, 2);


int sensor;

void setup() {
  Serial.begin(9600);
  EasyBuzzer.setPin(BUZZER_PIN);
}

void loop() {
 sensor = analogRead(A0);
 Serial.println(sensor);
 
 if(sensor >=30)
 {
    EasyBuzzer.beep(500); 
    EasyBuzzer.beep(1500);
    forward(motor2,motor2, 20);
 }
 else if (sensor <40)
 {
  back(motor2,motor2, 20);
  EasyBuzzer.stopBeep();
 }
 else
 {
  EasyBuzzer.beep(0); 
  brake(motor2,motor2);
 }
delay(200);
}
