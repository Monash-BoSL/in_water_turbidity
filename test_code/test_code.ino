#include <digitalWriteFast.h>

// TIA_PWR_EN (PC3/A3) -> HIGH
// REF_EN (PC1/A1) -> HIGH
// LED_1_EN (PD6/6) -> HIGH
// LED_2_EN (PD7/7) -> HIGH
// LED_DIGITAL_SIGNAL (PC2/A2) -> ON/OFF
// LED_PWR_EN (PD4/4) -> HIGH
// NEG_VOLT_EN (PD2/2) -> HIGH

#define TIA_PWR_EN A3
#define REF_EN A1
#define LED_1_EN 6
#define LED_2_EN 7
#define LED_DIGITAL_SIGNAL A2
#define LED_PWR_EN 4
#define NEG_VOLT_EN 2
#define ADC_SS 10

#include <Wire.h>
#include <Adafruit_TMP117.h>
#include <Adafruit_Sensor.h>

Adafruit_TMP117  tmp117;

void setup() {
  // put your setup code here, to run once:
  pinMode(TIA_PWR_EN, OUTPUT);
  pinMode(REF_EN, OUTPUT);
  pinMode(LED_1_EN, OUTPUT);
  pinMode(LED_2_EN, OUTPUT);
  pinModeFast(LED_DIGITAL_SIGNAL, OUTPUT);
  pinMode(LED_PWR_EN, OUTPUT);
  pinMode(NEG_VOLT_EN, OUTPUT);
  pinMode(ADC_SS, OUTPUT);

  digitalWrite(TIA_PWR_EN, HIGH);
  digitalWrite(REF_EN, HIGH);
  digitalWrite(LED_1_EN, HIGH);
  digitalWrite(LED_2_EN, HIGH);  
  digitalWrite(LED_PWR_EN, LOW);
  digitalWrite(NEG_VOLT_EN, HIGH);
  digitalWrite(ADC_SS, LOW);
  digitalWriteFast(LED_DIGITAL_SIGNAL, HIGH);

  Serial.begin(9600);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("TMP117 test!");

  // Try to initialize!
  if (!tmp117.begin()) {
    Serial.println("Failed to find TMP117 chip");
    while (1) { delay(10); }
  }
  Serial.println("TMP117 Found!");

}

void loop() {
  sensors_event_t temp; // create an empty event to be filled
  tmp117.getEvent(&temp); //fill the empty event object with the current measurements
  Serial.print("Temperature  "); Serial.print(temp.temperature);Serial.println(" degrees C");
  Serial.println("");
  digitalWriteFast(LED_DIGITAL_SIGNAL, HIGH);
  delayMicroseconds(2000);
  digitalWriteFast(LED_DIGITAL_SIGNAL, LOW);
  delayMicroseconds(20);
  digitalWriteFast(LED_DIGITAL_SIGNAL, HIGH);
}
