#include <WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h"

const char* ssid = "IOT";
const char* password = "IOT@123456789";

unsigned long channelID = 3358729;
const char* writeAPIKey = "8CF9UM6DZ4PMNN3E";

WiFiClient client;

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define VIBRATION_PIN 34
#define CURRENT_PIN 35
#define VOLTAGE_PIN 32

HardwareSerial gsm(2);

#define VOLTAGE_LIMIT 230
#define VIBRATION_LIMIT 2000

void sendSMS(String message)
{
  gsm.println("AT+CMGF=1");
  delay(1000);

  gsm.println("AT+CMGS=\"+919585697674\"");
  delay(1000);

  gsm.print(message);
  delay(500);

  gsm.write(26);
  delay(3000);
}

void setup()
{
  Serial.begin(115200);

  gsm.begin(9600, SERIAL_8N1, 16, 17);

  dht.begin();

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");

  ThingSpeak.begin(client);

  Serial.println("GSM Initialized");
  delay(3000);
}

void loop()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int vibrationValue = analogRead(VIBRATION_PIN);
  int currentRaw = analogRead(CURRENT_PIN);
  int voltageRaw = analogRead(VOLTAGE_PIN);

  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("DHT Sensor Error");
    delay(20000);
    return;
  }

  float currentVoltage = (currentRaw / 4095.0) * 3.3;
  float voltageSensor = (voltageRaw / 4095.0) * 3.3;

  float current = currentVoltage * 10.0;
  float voltage = voltageSensor * 100.0;

  if (voltage > VOLTAGE_LIMIT)
  {
    Serial.println("High Voltage Alert");
    sendSMS("Alert: Voltage exceeded 230V");
  }

  if (vibrationValue < VIBRATION_LIMIT)
  {
    Serial.println("Fan Fault Detected");
    sendSMS("Alert: Fan Fault Detected");
  }

  Serial.println("Sensor Data");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" percent");

  Serial.print("Vibration: ");
  Serial.println(vibrationValue);

  Serial.print("Current: ");
  Serial.print(current);
  Serial.println(" A");

  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, vibrationValue);
  ThingSpeak.setField(4, current);
  ThingSpeak.setField(5, voltage);

  int statusCode = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (statusCode == 200)
  {
    Serial.println("ThingSpeak Update Successful");
  }
  else
  {
    Serial.print("ThingSpeak Update Failed. Code: ");
    Serial.println(statusCode);
  }

  delay(20000);
}
