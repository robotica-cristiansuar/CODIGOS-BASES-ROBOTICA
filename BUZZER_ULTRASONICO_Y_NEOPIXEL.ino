//ULTRASONICO
#define TRIGGER_PIN 17
#define ECHO_PIN 16
long duration;
int distance; 

//BUZZER
#include <EasyBuzzer.h>
int BUZZER_PIN = 27;

//NEOPIXEL
#include <Wire.h> //I2C
#include <Adafruit_NeoPixel.h>
#define PIXEL_COUNT 4
#define PIXEL_PIN_1 15
#define PIXEL_PIN_2 13

Adafruit_NeoPixel neopixel1(PIXEL_COUNT, PIXEL_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neopixel2(PIXEL_COUNT, PIXEL_PIN_2, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(115200);
  Wire.begin(21, 22); //Pines I2C de nuestro ESP32
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT); 
  EasyBuzzer.setPin(BUZZER_PIN); //Initialize buzzer
}

void loop()
{
  //CONTROL ULTRASONICO
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(20);

  if (distance <= 20)
  {
    //ENCENDEMOS EL NEOPIXEL
    for(int i = 0; i < PIXEL_COUNT; i++)
  {
    neopixel1.setPixelColor(i, neopixel1.Color(255,255,255));
    neopixel2.setPixelColor(i, neopixel2.Color(255,255,255));
  }
  neopixel1.show();
  neopixel2.show();
  
  EasyBuzzer.beep(500); // Frequency in hertz(HZ).
    delay(100);
    EasyBuzzer.beep(1500); // Frequency in hertz(HZ).
    delay(100);
    EasyBuzzer.beep(200); // Frequency in hertz(HZ).
    delay(100);
  }
  else
  {
    //MANTENEMOS APAGADO EL NEOPIXEL
  neopixel1.clear();
  neopixel2.clear();
  neopixel1.show();
  neopixel2.show();

    EasyBuzzer.stopBeep();
  }
  delay(100);
}
