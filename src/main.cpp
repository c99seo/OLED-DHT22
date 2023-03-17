//OLED + DHT22
#include <Arduino.h>
#include <SSD1306.h>
#include <DHTesp.h>

DHTesp              dht;
int                 interval = 2000;
unsigned long       lastDHTReadMillis = 0;
float               humidity = 0;
float               temperature = 0;
char msg1[50] = {0x00};
char msg2[50] = {0x00};

SSD1306             display(0x3c, 4, 5, GEOMETRY_128_32);

void setup() {
  Serial.begin(115200);
  dht.setup(14, DHTesp::DHT22); // Connect DHT sensor to GPIO 14
  delay(1000);

  Serial.println(); Serial.println("Humidity (%)\tTemperature (C)");

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.display();
  display.clear();
}

void readDHT22() {
    unsigned long currentMillis = millis();

    if(currentMillis - lastDHTReadMillis >= interval) {
        lastDHTReadMillis = currentMillis;

        humidity = dht.getHumidity();              // Read humidity (percent)
        temperature = dht.getTemperature();        // Read temperature as Fahrenheit
    }
}

void loop() {
  readDHT22();
  sprintf(msg1, "%.1f", humidity);
  sprintf(msg2, "%.1f", temperature);
  display.drawString(10, 10, String(humidity));
  display.drawString(60, 10, String(temperature));
  
  display.display();
  display.clear();

  Serial.printf("%.1f\t %.1f\n", temperature, humidity);
  delay(1000);
}