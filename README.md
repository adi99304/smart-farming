# Smart Farming with IoT using ThingSpeak

# Overview
This project implements smart farming techniques using IoT (Internet of Things) technology to optimize crop production and irrigation practices. It integrates various sensors, actuators, and cloud services to collect, analyze, and act upon environmental data in real-time. This README provides a comprehensive overview of the components, technologies, and implementation details of the project.

# Components
1. *Sensors*:
   - Rain Sensor: Measures rainfall to adjust irrigation schedules.
   - DHT11 Sensor: Monitors temperature and humidity for environmental control.
   - Soil Moisture Sensor: Determines soil moisture levels for optimized irrigation.
2. *Actuators*:
   - Arduino Relay: Controls the irrigation system based on sensor data.
   - Motor: Dispenses water for irrigation when triggered.
3. *IoT Platform*:
   - ThingSpeak: Cloud platform for collecting, analyzing, and visualizing sensor data.
4. *Data Upload*:
   - Python Script: Uploads sensor data to ThingSpeak for real-time monitoring and analysis.

# Implementation Details
1. *Sensor Integration*:
   - Connect the rain sensor, DHT11 sensor, and soil moisture sensor to the Arduino board.
   - Ensure proper wiring and calibration for accurate data readings.

2. *Actuator Control*:
   - Use the Arduino Relay to control the irrigation system based on sensor readings.
   - Connect the motor to the Arduino board and program it to dispense water when required.

3. *ThingSpeak Integration*:
   - Sign up for a ThingSpeak account and create channels to store sensor data.
   - Generate API keys to allow communication between the Arduino and ThingSpeak.
   - Use the Python script to read sensor data from the Arduino and upload it to ThingSpeak using the ThingSpeak API.

4. *Data Visualization*:
   - Use the ThingSpeak platform to visualize sensor data in real-time.
   - Create charts and graphs to monitor environmental conditions and irrigation activities.
# Arduino code:-
#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define RAINFALL_PIN A0
#define BUZZER_PIN 12
#define SOIL_MOISTURE_DIGITAL_PIN 4
#define LCD_RS_PIN 7
#define LCD_EN_PIN 6
#define LCD_D4_PIN 5
#define LCD_D5_PIN 3
#define LCD_D6_PIN 2
#define LCD_D7_PIN 1

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

int humidity;
int temperature;
int rainValue;
bool soilMoistureValue;
int rainThreshold = 10;
int soilMoistureThreshold = 900; // Adjust this value based on your sensor's readings

void setup() {
  Serial.begin(115200);
  Serial.println("DHT11, Rain Sensor, and Soil Moisture Sensor");
  Serial.println("Ready");
  dht.begin();
  lcd.begin(16, 2);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RAINFALL_PIN, INPUT);
  pinMode(SOIL_MOISTURE_DIGITAL_PIN, INPUT_PULLUP);
}

void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  rainValue = analogRead(RAINFALL_PIN);
  soilMoistureValue = !digitalRead(SOIL_MOISTURE_DIGITAL_PIN); // Invert the digital reading

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
    lcd.print("Temp


# Benefits
1. *Optimized Irrigation*: Automated irrigation control based on sensor data ensures efficient water usage and prevents overwatering or underwatering.
2. *Environmental Monitoring*: Real-time monitoring of temperature, humidity, soil moisture, and rainfall enables precise environmental control.
3. *Data Analysis*: Historical data analysis helps in identifying trends and patterns for informed decision-making.
4. *Remote Monitoring*: Access sensor data and control irrigation systems remotely via the ThingSpeak platform.

# Conclusion
By leveraging IoT technology and cloud services like ThingSpeak, this smart farming project offers an effective solution for optimizing irrigation practices and maximizing crop yield. With real-time monitoring, data analysis, and remote control capabilities, farmers can enhance productivity while conserving resources and reducing manual labor.
