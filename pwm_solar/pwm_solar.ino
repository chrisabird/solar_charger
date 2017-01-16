#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define voltageDivider 0.203389830508
#define supplyVoltage 5.0
#define chargeVoltage 13.5
#define chargePwmPin 3
#define solarVoltagePin A0
#define batteryVoltagePin A1

Adafruit_PCD8544 display = Adafruit_PCD8544(12, 11, 10, 9, 8);
uint8_t duty = 0;

void setup() {
  display.begin();
  display.setContrast(50);

  display.display();
  delay(2000);
  display.clearDisplay();

  pinMode(solarVoltagePin, INPUT);
  pinMode(batteryVoltagePin, INPUT);
  pinMode(chargePwmPin, OUTPUT);

  analogWrite(chargePwmPin, 0);
}

double readVoltage(uint8_t voltagePin) {
  analogRead(voltagePin);
  delay(10);
  return ((analogRead(voltagePin) * supplyVoltage) / 1024) / voltageDivider;
}

void loop() {
  double solarVoltage = readVoltage(solarVoltagePin);
  double batteryVoltage = readVoltage(batteryVoltagePin);

  if (batteryVoltage < chargeVoltage && duty < 255t) {
    duty++;
  }
  if (batteryVoltage > chargeVoltage && duty > 0) {
    duty--;
  }
  analogWrite(chargePwmPin, duty);

  display.clearDisplay();
  display.print("SOLAR ");
  display.println(solarVoltage);
  display.print("BAT ");
  display.println(batteryVoltage);
  display.print("DUTY ");
  display.println(duty);
  display.display();
}
