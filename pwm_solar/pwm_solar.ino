#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(12, 11, 10, 9, 8);

void setup() {
  // put your setup code here, to run once:

  display.begin();

  display.setContrast(50);
  
  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();   // clears the screen and buffer

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(3, OUTPUT);
  analogWrite(3, 32);
}

double readVoltage(uint8_t voltagePin) {
  double reading = 0;
  reading = analogRead(voltagePin);
  delay(100);
  reading = analogRead(voltagePin);
  reading += analogRead(voltagePin);
  reading += analogRead(voltagePin);
  reading += analogRead(voltagePin);
  reading += analogRead(voltagePin);
  reading += analogRead(voltagePin);
  reading += analogRead(voltagePin);
  reading += analogRead(voltagePin);
  reading += analogRead(voltagePin);
  reading += analogRead(voltagePin);
  return ((5.0 * (reading / 10)) / 1024) /  (1200.0 / (4700.0 + 1200.0));

  
}

void loop() {
  display.clearDisplay();
  display.print("SOLAR ");
  display.println(readVoltage(A0));
  display.print("BAT ");
  display.println(readVoltage(A1));
  display.print("DUTY ");
  display.println(128);
  display.display();

  

}
