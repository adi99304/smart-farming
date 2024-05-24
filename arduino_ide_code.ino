#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define RAINFALL_PIN A0
#define BUZZER_PIN 12
#define SOIL_MOISTURE_ANALOG_PIN A1
#define SOIL_MOISTURE_DIGITAL_PIN 3

#define LCD_RS_PIN 7
#define LCD_EN_PIN 6
#define LCD_D4_PIN 5
#define LCD_D5_PIN 4
#define LCD_D6_PIN 3
#define LCD_D7_PIN 2

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

int humidity;
int temperature;
int rainValue;
int soilMoistureValue;
int rainThreshold = 10;
int soilMoistureThreshold = 800; // Adjust this value based on your sensor's readings

void setup() {
  Serial.begin(115200);
  Serial.println("DHT11, Rain Sensor, and Soil Moisture Sensor");
  Serial.println("Ready");
  dht.begin();
  lcd.begin(16, 2);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RAINFALL_PIN, INPUT);
  pinMode(SOIL_MOISTURE_DIGITAL_PIN, INPUT);
}

void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  rainValue = analogRead(RAINFALL_PIN);
  soilMoistureValue = analogRead(SOIL_MOISTURE_ANALOG_PIN);

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Temp: ");
  Serial.print(temperature);
  Serial.print(" °C, Rain: ");
  Serial.print(rainValue);
  Serial.print(", Soil Moisture: ");
  Serial.println(soilMoistureValue);

  rainValue = map(rainValue, 0, 1023, 225, 0);

  if (rainValue >= rainThreshold) {
    Serial.println("Rain detected");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Rain detected!");
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");
    digitalWrite(BUZZER_PIN, LOW);
  }


  // Analog soil moisture reading
  if (soilMoistureValue >= soilMoistureThreshold) { // Soil is wet
    Serial.println("Soil is dry");
    Serial.println("Motor is on");
    digitalWrite(BUZZER_PIN, LOW); // Turn on buzzer
  } else { // Soil is dry
    Serial.println("Soil is wet");

    digitalWrite(BUZZER_PIN, HIGH); // Turn off buzzer
  }

  delay(1000); // Increase delay to slow down the readings
}