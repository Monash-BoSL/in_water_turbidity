// TIA_PWR_EN (PC3/A3) -> HIGH
// REF_EN (PC1/A1) -> HIGH
// LED_1_EN (PD6/6) -> HIGH
// LED_2_EN (PD7/7) -> HIGH
// LED_DIGITAL_SIGNAL (PC2/A2) -> ON/OFF
// LED_PWR_EN (PD4/4) -> LOW
// NEG_VOLT_EN (PD2/2) -> HIGH

#define TIA_PWR_EN A3
#define REF_EN A1
#define LED_1_EN 6
#define LED_2_EN 7
#define LED_DIGITAL_SIGNAL A2
#define LED_PWR_EN 4
#define NEG_VOLT_EN 2

void setup() {
  // put your setup code here, to run once:
  pinMode(TIA_PWR_EN, OUTPUT);
  pinMode(REF_EN, OUTPUT);
  pinMode(LED_1_EN, OUTPUT);
  pinMode(LED_2_EN, OUTPUT);
  pinMode(LED_DIGITAL_SIGNAL, OUTPUT);
  pinMode(LED_PWR_EN, OUTPUT);
  pinMode(NEG_VOLT_EN, OUTPUT);

  digitalWrite(TIA_PWR_EN, HIGH);
  digitalWrite(REF_EN, HIGH);
  digitalWrite(LED_1_EN, HIGH);
  digitalWrite(LED_2_EN, HIGH);
  digitalWrite(LED_DIGITAL_SIGNAL, HIGH);
  digitalWrite(LED_PWR_EN, LOW);
  digitalWrite(NEG_VOLT_EN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_DIGITAL_SIGNAL, LOW);
  delay(2);
  digitalWrite(LED_DIGITAL_SIGNAL, HIGH);
  delay(2);
}
