#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

// ESP32 pin connections
const int ALCOHOL_PIN = 34;
const int HELMET_PIN  = 27;
const int RELAY_PIN   = 25;
const int BUZZER_PIN  = 26;
const int LED_PIN     = 12;

// Adjust if your relay is active HIGH
const int RELAY_ON  = LOW;
const int RELAY_OFF = HIGH;

// LCD and MPU6050
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_MPU6050 mpu;

const int ALCOHOL_THRESHOLD = 2200;
bool mpuAvailable = false;

unsigned long lastAccidentAlert = 0;
const unsigned long ALERT_COOLDOWN = 3000;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  pinMode(HELMET_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, RELAY_OFF);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Helmet");

  mpuAvailable = mpu.begin();

  if (mpuAvailable) {
    mpu.setAccelerometerRange(
      MPU6050_RANGE_8_G);
    Serial.println("MPU6050 detected");
  } else {
    Serial.println("MPU6050 not detected");
  }

  delay(1500);
  lcd.clear();
}

void loop() {
  int alcoholValue = analogRead(ALCOHOL_PIN);

  // Button pressed = helmet worn
  bool helmetWorn = (digitalRead(HELMET_PIN) == LOW);

  bool alcoholDetected =
      alcoholValue >= ALCOHOL_THRESHOLD;

  bool accidentDetected = false;

  // Basic sudden-acceleration demo.
  // This is not a reliable real-world crash detector.
  if (mpuAvailable) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    float magnitude = sqrt(
      a.acceleration.x * a.acceleration.x +
      a.acceleration.y * a.acceleration.y +
      a.acceleration.z * a.acceleration.z
    );

    if (magnitude > 25.0 &&
        millis() - lastAccidentAlert > ALERT_COOLDOWN) {
      accidentDetected = true;
      lastAccidentAlert = millis();
    }
  }

  bool ignitionAllowed =
      helmetWorn && !alcoholDetected;

  digitalWrite(RELAY_PIN,
      ignitionAllowed ? RELAY_ON : RELAY_OFF);

  digitalWrite(LED_PIN,
      ignitionAllowed ? HIGH : LOW);

  if (alcoholDetected || !helmetWorn ||
      accidentDetected) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  lcd.setCursor(0, 0);
  if (alcoholDetected) {
    lcd.print("Alcohol detected");
  } else if (!helmetWorn) {
    lcd.print("Wear your helmet");
  } else {
    lcd.print("Helmet: Ready   ");
  }

  lcd.setCursor(0, 1);
  lcd.print("ADC:");
  lcd.print(alcoholValue);
  lcd.print(" ");
  if (accidentDetected) {
    lcd.print("ACCIDENT!");
  } else if (ignitionAllowed) {
    lcd.print("IGN:ON ");
  } else {
    lcd.print("IGN:OFF");
  }

  Serial.print("Alcohol ADC: ");
  Serial.print(alcoholValue);
  Serial.print(" | Helmet worn: ");
  Serial.print(helmetWorn ? "YES" : "NO");
  Serial.print(" | Ignition: ");
  Serial.println(ignitionAllowed ? "ON" : "OFF");

  if (accidentDetected) {
    Serial.println(
      "ALERT: Possible accident detected!");
    Serial.println(
      "GPS/SMS not implemented in this simulation.");
  }

  delay(1000);
}