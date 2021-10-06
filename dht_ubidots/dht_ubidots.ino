#include <DHT.h>
#include <UbidotsMicroESP8266.h>

#define DHTPIN 14 /* mendefinisikan pin dht di nodeMcu adalah 4, D2 = 4 */
#define DHTTYPE DHT11 /* mendefinisikan tipe dht yang kita gunakan */

char auth[] = "YourAuthToken"; /* token yang dikirim dari blynk ke email masing2 */
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

DHT dht(DHTPIN, DHTTYPE);
Ubidots client(auth); /* setting token client ubidots */
unsigned long last = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin(); /* /* sensor mulai membaca suhu dan kelembapan */
  delay(20); /* delay 0,02 detik */
  client.wifiConnection(ssid, pass); /* meyambungkan ubidots client dengan wifi */

}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - last > 10000) { /* jika sudah 10 detik */
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    last = millis(); /* 11 */
    client.add("Kelembapan", hum); /* ubidots client membaca kelembapan */
    client.add("Temperature", temp); /* ubidots client membaca suhu/temperatur */
    client.sendAll(true); /* ubidots client mengirimkan semua data */
  }

}
