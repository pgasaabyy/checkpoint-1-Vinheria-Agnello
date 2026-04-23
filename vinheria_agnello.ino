const int ledVerde = 5;
const int ledAmarelo = 6;
const int ledVermelho = 7;
const int buzzer = 3;
const int sensorLuminosidade = A0;

int valorLuminosidade = 0;
int limiteOK = 880;
int limiteAlerta = 960;

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sensorLuminosidade, INPUT);
  Serial.begin(9600);
}

void loop() {
  valorLuminosidade = analogRead(sensorLuminosidade);
  Serial.println(valorLuminosidade);

  if (valorLuminosidade < limiteOK) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    noTone(buzzer);
  }
  else if (valorLuminosidade >= limiteOK && valorLuminosidade <= limiteAlerta) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
    tone(buzzer, 500);
    delay(3000);
    noTone(buzzer);
  }
  else if (valorLuminosidade > limiteAlerta) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    tone(buzzer, 1000);
  }

  delay(1000);
}