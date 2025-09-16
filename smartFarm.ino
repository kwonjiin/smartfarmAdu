#include <DHT.h>      // DHT 라이브러리를 불러옵니다.
#include <Tone.h>

#define DHTPIN 7      // DHT 센서의 데이터 핀을 설정합니다.
#define DHTTYPE DHT11 // DHT11을 사용할 것입니다. 다른 모델을 사용하려면 변경하세요.
#define CDS_PIN A0    // CDS 센서의 아날로그 핀을 설정합니다.
#define LED_PIN_1 8   // LED 1을 제어할 디지털 핀을 설정합니다.
#define LED_PIN_2 9   // LED 2를 제어할 디지털 핀을 설정합니다.
#define LED_PIN_3 10   // LED 3을 제어할 디지털 핀을 설정합니다.
#define BUZZER_PIN 3

DHT dht(DHTPIN, DHTTYPE); // DHT 객체를 생성합니다.
Tone buzzer;

void setup() {
  Serial.begin(9600);       // 시리얼 통신을 시작합니다.
  dht.begin();              // DHT 센서를 시작합니다.
  pinMode(LED_PIN_1, OUTPUT); // LED 1의 핀을 출력으로 설정합니다.
  pinMode(LED_PIN_2, OUTPUT); // LED 2의 핀을 출력으로 설정합니다.
  pinMode(LED_PIN_3, OUTPUT); // LED 3의 핀을 출력으로 설정합니다.
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  float temperature = dht.readTemperature(); // 온도 값을 읽어옵니다.
  float humidity = dht.readHumidity();       // 습도 값을 읽어옵니다.
  int lightLevel = analogRead(CDS_PIN);      // CDS 센서 값을 읽어옵니다.

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.print(" % | Light Level: ");
  Serial.println(lightLevel);

  // 온도에 따라 LED 1 제어
  if (temperature > 24.6) {
    digitalWrite(LED_PIN_1, HIGH); // LED 1 켜기
  } else {
    digitalWrite(LED_PIN_1, LOW);  // LED 1 끄기
  }

  // 습도에 따라 LED 2 제어
  if (humidity > 42.1) {
    digitalWrite(LED_PIN_2, HIGH); // LED 2 켜기
  } else {
    digitalWrite(LED_PIN_2, LOW);  // LED 2 끄기
  }

  // 주변 조도에 따라 LED 3 제어
  if (lightLevel <10) {
    digitalWrite(LED_PIN_3, HIGH); // LED 3 켜기
  } else {
    digitalWrite(LED_PIN_3, LOW);  // LED 3 끄기
  }

  if (humidity > 42.1 && temperature > 24.6 && lightLevel < 10) {
    // 부저 울리기
    tone(BUZZER_PIN, 1000);
    delay(1000); // 1초 동안 대기
    noTone(BUZZER_PIN); // 부저 중지
    delay(1000); // 1초 동안 대기
  }

  delay(2000); // 2초 기다립니다.
}