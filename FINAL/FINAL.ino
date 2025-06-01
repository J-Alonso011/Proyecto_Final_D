#include <LiquidCrystal_I2C.h>

const int trigPin = 9;
const int echoPin = 10;
const int motorPin = 6;
const int buzzerPin = 7;
const int buttonPin = 2;  // Pin del botón normalmente cerrado

LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección del I2C
bool buzzerActivado = false;
bool productoDetectado = false;
bool sistemaActivo = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT); // Sin pull-up, ya que el NC conecta directamente a GND

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("Presione boton");
}

void loop() {
  if (!sistemaActivo) {
    if (digitalRead(buttonPin) == HIGH) { // Botón suelto (se presionó)
      sistemaActivo = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sistema activo");
      delay(1000);
      lcd.clear();
    } else {
      return; // Sigue esperando mientras el botón esté en LOW (conectado a GND)
    }
  }

  long duration;
  int distance;

  // Pulso ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.println(distance);

  if (distance <= 4) {
    if (!productoDetectado) {
      productoDetectado = true;

      digitalWrite(motorPin, LOW); // Apagar motor

      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("REGISTRAR");
      lcd.setCursor(4, 1);
      lcd.print("PRODUCTO");

      if (!buzzerActivado) {
        digitalWrite(buzzerPin, HIGH);
        delay(500);
        digitalWrite(buzzerPin, LOW);
        buzzerActivado = true;
      }
    }
  } else {
    if (productoDetectado) {
      productoDetectado = false;
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("COLOQUE");
      lcd.setCursor(4, 1);
      lcd.print("PRODUCTO");
    }

    digitalWrite(motorPin, HIGH); // Encender motor
    buzzerActivado = false;
  }

  delay(200);
}
