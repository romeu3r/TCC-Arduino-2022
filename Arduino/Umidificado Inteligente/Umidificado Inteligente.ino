#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#define endereco 0x27
#define colunas 16
#define linhas 2
#define SENSOR 2
#define RELE 9
#define TIPO DHT22
LiquidCrystal_I2C lcd(endereco, colunas, linhas);  //Dados referentes ao LCD.
DHT dht(SENSOR, TIPO);                             //Dados para o DHT

int maxHumidade = 70;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print(F("Inicializando..."));
  lcd.setCursor(2, 0);
  lcd.print(F("Prog. com Arduino"));

  Serial.println(F(" Inicializando Umidificador Inteligente:"));
  delay(3000);

  pinMode(RELE, OUTPUT);
}

void loop() {
  float h = dht.readHumidity();     //Ler Umidade
  float t = dht.readTemperature();  //Ler Temperatura

  if (false) defensiva();
  else {
    if (h <= maxHumidade) {
      ligar(h, t);
    } else {
      desligar(h, t);
    }
  }

  Serial.print("Umidade relativa do ar: ");
  Serial.print(h);
  Serial.print(" %\t ");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" °C ");
  delay(2000);
}

void defensiva() {
  Serial.print("Defensiva");
}

void ligar(float h, float t) {
  digitalWrite(RELE, HIGH);
  lcd.clear();
  lcd.setCursor(4, 0);                           //Coloca o cursor na coluna 4 da linha 0 do LCD.
  lcd.print(F("LIGADO"));                        //Imprime o texto no LCD
  lcd.setCursor(0, 1);                           //Coloca o cursor na coluna 0 da linha 1 do LCD.
  lcd.print(F("Temp:"));                         //Imprime o texto no LCD
  lcd.print(t);                                  //Imprime o texto no LCD
  lcd.print(F("umid:"));                         //Imprime o texto no LCD
  lcd.print(h);                                  //Imprime o texto no LCD
  lcd.print(F("%"));                             //Imprime o texto no LCD
  Serial.print(F(" UMIDIFICADOR DESLIGADO: "));  //Serial Display
}

void desligar(float h, float t) {
  digitalWrite(RELE, LOW);
  lcd.clear();
  lcd.setCursor(3, 0);                           //Coloca o cursor na coluna 3 da linha 0 do LCD.
  lcd.print(F("DESLIGADO"));                     //Imprime o texto no LCD
  lcd.setCursor(0, 1);                           //Coloca o cursor na coluna 0 da linha 1 do LCD.
  lcd.print(F("Temp:"));                         //Imprime o texto no LCD
  lcd.print(t);                                  //Imprime o texto no LCD
  lcd.print(F("umid:"));                         //Imprime o texto no LCD
  lcd.print(h);                                  //Imprime o texto no LCD
  lcd.print(F("%"));                             //Imprime o texto no LCD
  Serial.print(F(" UMIDIFICADOR DESLIGADO: "));  //Serial Display
}