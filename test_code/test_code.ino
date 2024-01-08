#include <digitalWriteFast.h>
#include <SPI.h>

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
#define BUFFER_EN 8
#define LED_PWR_ALRT 5

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
  pinMode(BUFFER_EN, OUTPUT);
  pinMode(LED_PWR_ALRT, INPUT);

  digitalWrite(TIA_PWR_EN, HIGH);
  digitalWrite(REF_EN, HIGH);
  digitalWrite(LED_1_EN, LOW);
  digitalWrite(LED_2_EN, HIGH);  
  digitalWrite(LED_PWR_EN, LOW);
  digitalWrite(NEG_VOLT_EN, HIGH);
  digitalWrite(ADC_SS, LOW);
  digitalWriteFast(LED_DIGITAL_SIGNAL, LOW);
  digitalWrite(BUFFER_EN, LOW);

  Serial.begin(9600);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("TMP117 test!");

  // Try to initialize!
  if (!tmp117.begin()) {
    Serial.println("Failed to find TMP117 chip");
    while (1) { delay(10); }
  }
  Serial.println("TMP117 Found!");
  SPI.begin();
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
}

void loop() {
  sensors_event_t temp; // create an empty event to be filled
  tmp117.getEvent(&temp); //fill the empty event object with the current measurements
  // Serial.print("Temperature  "); Serial.print(temp.temperature);Serial.println(" degrees C");
  // Serial.println("");
  //digitalWriteFast(LED_DIGITAL_SIGNAL, HIGH);
  //delayMicroseconds(20);
  //digitalWriteFast(LED_DIGITAL_SIGNAL, LOW);

  // Serial.println(digitalRead(LED_PWR_ALRT));
  //delayMicroseconds(100);
  //digitalWriteFast(LED_DIGITAL_SIGNAL, LOW);
  //delayMicroseconds(20);

  float on_acc = 0.0;
  float off_acc = 0.0;
  int samples = 5;
  
  for (int i = 0; i < samples; i++) 
  {
    // Read off data
    digitalWriteFast(ADC_SS, HIGH);
    delayMicroseconds(3);
    digitalWriteFast(ADC_SS, LOW);
    
    uint16_t off = SPI.transfer16(0);
    digitalWrite(LED_1_EN, LOW);
    digitalWrite(LED_2_EN, HIGH);

    delay(2);

    digitalWriteFast(LED_DIGITAL_SIGNAL, HIGH);
    delayMicroseconds(20);

    // Read on data
    digitalWriteFast(ADC_SS, HIGH);
    delayMicroseconds(3);
    digitalWriteFast(ADC_SS, LOW);

    digitalWrite(LED_1_EN, LOW);
    digitalWrite(LED_2_EN, LOW);
    digitalWriteFast(LED_DIGITAL_SIGNAL, LOW);

    uint16_t on = SPI.transfer16(0);

    on_acc += (float)on;
    off_acc += (float)off;

    delay(5000);
  }

  Serial.print(on_acc/samples);
  Serial.print(',');
  Serial.print(off_acc/samples);
  Serial.print(',');
  Serial.print(on_acc/samples-off_acc/samples);
  Serial.print(',');
  Serial.println(temp.temperature);
  
  delay(5000);
}
