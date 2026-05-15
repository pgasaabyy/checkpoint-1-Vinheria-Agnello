/*
 * =======================================================
 *  FIAP — Edge Computing & Computer Systems
 *  Checkpoint 02 — Vinheria Agnello
 ====
 *    Guilherme Tome Nogueira       RM: 570144
 *    Lucas de Andrade Astorini     RM: 569119
 *    Sabrina Lopes da Silva        RM: 571870
 *    Sofia Satomi Hagio            RM: 569120
  */

#include <DHT.h>
#include <Wire.h> // Biblioteca utilizada para fazer a comunicação com o I2C
#include <LiquidCrystal_I2C.h> // Biblioteca utilizada para fazer a comunicação com o display 20x4

#define col 16 // Serve para definir o numero de colunas do display utilizado
#define lin 2 // Serve para definir o numero de linhas do display utilizado
#define ende 0x27 // Serve para definir o endereço do display.

#define DHTPIN 8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(ende,col,lin); // Chamada da funcação LiquidCrystal para ser usada com o I2C

byte rostoFeliz[8] = {
 0b00000,
 0b01010,
 0b01010,
 0b00000,
 0b10001,
 0b01110,
 0b00000,
 0b00000
};

int buzzer = 9;
int ledVerde = 13;
int ledAmarelo = 12;
int ledVermelho = 10;
int ldr = A0;

constint TEMP_MIN = 10;
constint TEMP_MAX = 15;
constint UMID_MIN = 50;
constint UMID_MAX = 70;
constint NUM_LEITURAS = 5;
constunsignedlong INTERVALO = 5000;

unsignedlong ultimaLeitura = 0;

float mediaTemp = 0;
float mediaUmid = 0;
int mediaLuz = 0;

voidsetup() {
Serial.begin(9600);
dht.begin();
lcd.init();
lcd.backlight();
lcd.clear();
lcd.createChar(0, rostoFeliz);
lcd.setCursor(0, 0);
lcd.print("Vinheria Agnello");
lcd.setCursor(2, 1);
lcd.write(byte(0)); 
delay(10000);

pinMode(buzzer, OUTPUT);
pinMode(ledVerde, OUTPUT);
pinMode(ledAmarelo, OUTPUT);
pinMode(ledVermelho, OUTPUT);
pinMode(ldr, INPUT);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Edge Solution!");
delay(2000);
lcd.clear();
}

voidcoletarLeituras() {
float somaTemp = 0, somaUmid = 0;
long somaLuz = 0;

 for (int i = 0; i < NUM_LEITURAS; i++) {
 somaTemp += dht.readTemperature();
 somaUmid += dht.readHumidity();
 somaLuz += analogRead(ldr);
delay(200);
 }

 mediaTemp = somaTemp / NUM_LEITURAS;
 mediaUmid = somaUmid / NUM_LEITURAS;
int ldrBruto = somaLuz / NUM_LEITURAS;
 mediaLuz = map(ldrBruto, 974, 54, 0, 100);
 mediaLuz = constrain(mediaLuz, 0, 100);
}

voidresetAlertas() {
bool tempOK = (mediaTemp >= TEMP_MIN && mediaTemp <= TEMP_MAX);
bool umidOK = (mediaUmid >= UMID_MIN && mediaUmid <= UMID_MAX);
bool buzzerContinuo = (mediaLuz == 100) || !tempOK || !umidOK;

digitalWrite(ledVerde, LOW);
digitalWrite(ledAmarelo, LOW);
digitalWrite(ledVermelho, LOW);

 if (!buzzerContinuo) {
noTone(buzzer);
 }
}

voidprocessarLuz() {
Serial.print("Luminosidade: ");
Serial.print(mediaLuz);
Serial.println("%");

 if (mediaLuz >= 31 && mediaLuz <= 59) {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Ambiente a");
lcd.setCursor(0, 1);
lcd.print("meia luz");
delay(1500);
lcd.clear();

 } else if (mediaLuz >= 60) {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Ambiente muito");
lcd.setCursor(0, 1);
lcd.print("claro");
delay(1500);
lcd.clear();
 }
}

voidprocessarTemperatura() {
Serial.print("Temp: ");
Serial.print(mediaTemp);
Serial.println("C");

 if (mediaTemp >= TEMP_MIN && mediaTemp <= TEMP_MAX) {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Temperatura OK");
lcd.setCursor(0, 1);
lcd.print("Temp. = ");
lcd.print(mediaTemp, 1);
lcd.print("C");
delay(1500);
lcd.clear();

 } else if (mediaTemp > TEMP_MAX) {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Temp. ALTA");
lcd.setCursor(0, 1);
lcd.print("Temp. = ");
lcd.print(mediaTemp, 1);
lcd.print("C");
delay(1500);
lcd.clear();

 } else {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Temp. BAIXA");
lcd.setCursor(0, 1);
lcd.print("Temp. = ");
lcd.print(mediaTemp, 1);
lcd.print("C");
delay(1500);
lcd.clear();
 }
}

voidprocessarUmidade() {
Serial.print("Umidade: ");
Serial.print(mediaUmid);
Serial.println("%");

 if (mediaUmid >= UMID_MIN && mediaUmid <= UMID_MAX) {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Umidade OK");
lcd.setCursor(0, 1);
lcd.print("Umidade = ");
lcd.print(mediaUmid, 0);
lcd.print("%");
delay(1500);
lcd.clear();

 } else if (mediaUmid > UMID_MAX) {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Umidade ALTA");
lcd.setCursor(0, 1);
lcd.print("Umidade = ");
lcd.print(mediaUmid, 0);
lcd.print("%");
delay(1500);
lcd.clear();

 } else {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Umidade BAIXA");
lcd.setCursor(0, 1);
lcd.print("Umidade = ");
lcd.print(mediaUmid, 0);
lcd.print("%");
delay(1500);
lcd.clear();
 }
}

voidaplicarAlertas() {
bool tempOK = (mediaTemp >= TEMP_MIN && mediaTemp <= TEMP_MAX);
bool umidOK = (mediaUmid >= UMID_MIN && mediaUmid <= UMID_MAX);
bool luzOK = (mediaLuz <= 30);
bool buzzerContinuo = (mediaLuz == 100) || !tempOK || !umidOK;

 if (luzOK && tempOK && umidOK) {
digitalWrite(ledVerde, HIGH);

 } else if (mediaLuz >= 31 && mediaLuz <= 59) {
digitalWrite(ledAmarelo, HIGH);

 } else if (mediaLuz >= 60) {
digitalWrite(ledVermelho, HIGH);
 if (!buzzerContinuo) {
tone(buzzer, 1000);
delay(3000);
noTone(buzzer);
 }
 }

 if (!tempOK) {
digitalWrite(ledAmarelo, HIGH);
 }

 if (!umidOK) {
digitalWrite(ledVermelho, HIGH);
 }

 if (buzzerContinuo) {
tone(buzzer, 1000);
 }
}

voidloop() {
unsignedlong agora = millis();

 if (agora - ultimaLeitura >= INTERVALO) {
 ultimaLeitura = agora;

coletarLeituras();
resetAlertas();

processarLuz();
processarTemperatura();
processarUmidade();

aplicarAlertas();
 }
}
