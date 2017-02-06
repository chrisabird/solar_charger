#include <avr/power.h>

#define adcRange 1023
#define dividerResistor1 22000.0
#define dividerResistor2 4900.0
#define supplyVoltage 3.3
#define chargeVoltage 13.5
#define chargePwmPin 3
#define batteryVoltagePin A1

int duty = 0;
int chargeVoltageADC = ((chargeVoltage * (dividerResistor2 / (dividerResistor1 + dividerResistor2))) / supplyVoltage) * adcRange;

void setup() {

  clock_prescale_set(clock_div_32);
  power_twi_disable();
  power_spi_disable() ;
  TCCR2B = (TCCR2B & 0b11111000) | 0x02;

  pinMode(batteryVoltagePin, INPUT);
  pinMode(chargePwmPin, OUTPUT);

  analogWrite(chargePwmPin, 0);
}

void loop() {
    analogRead(batteryVoltagePin);
    delay(10);
    int batteryVoltageADC = analogRead(batteryVoltagePin);
    int difference = abs(batteryVoltageADC - chargeVoltageADC);

    if (batteryVoltageADC < chargeVoltageADC) {
      duty += difference;

    }
    if (batteryVoltageADC > chargeVoltageADC) {
      duty -= difference;
    }

    if (duty < 0) duty = 0;
    if (duty > 255) duty = 255;

    analogWrite(chargePwmPin, duty);
}


