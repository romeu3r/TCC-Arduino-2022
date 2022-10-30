#include "DHT.h"

#define endereco 0x27
#define colunas 20
#define linhas 2
#define SENSOR 2
#define RELE 9
#define TIPO DHT22
DHT dht(SENSOR, TIPO);
int maxHumidade = 90;

void setup() {
  Serial.begin(9600);
  dht.begin();

  Serial.println(F(" Inicializando Umidificador Inteligente:"));
  delay(3000);

  pinMode(RELE, OUTPUT);
}
void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (h <= maxHumidade) {
    digitalWrite(RELE, HIGH);
    Serial.print(F(" UMIDIFICADOR LIGADO: "));
  } else if (h >= maxHumidade) {
    digitalWrite(RELE, LOW);
    Serial.print(F(" UMIDIFICADOR DESLIGADO: "));
  }

  Serial.print("Umidade relativa do ar: ");
  Serial.print(h);
  Serial.print(" %\t ");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" °C ");
  delay(2000);
}