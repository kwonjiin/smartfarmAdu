# smartfarmAdu

이 프로젝트는 Arduino Uno와 센서를 활용하여 스마트팜 환경을 모니터링하는 **스마트 농장 환경 감지 시스템**입니다.  
온도, 습도, 조도를 측정하고 조건에 따라 LED와 부저로 알림을 제공합니다.

## 🔧 사용한 부품
- Arduino Uno  
- DHT11 (온습도 센서)  
- CDS 조도 센서  
- LED 3개  
- 부저  
- 점퍼 케이블, 브레드보드  

## ⚙️ 기능
1. **온도 모니터링**  
   - 온도가 24.6°C 이상일 경우 LED 1 켜기
2. **습도 모니터링**  
   - 습도가 42.1% 이상일 경우 LED 2 켜기
3. **조도 모니터링**  
   - 주변 조도가 10 미만일 경우 LED 3 켜기
4. **종합 알림**  
   - 온도, 습도, 조도 조건 모두 만족 시 부저 울림

## 🔌 회로 연결
- DHT11  
  - VCC → 5V  
  - GND → GND  
  - DATA → D7  
- CDS 조도 센서 → A0  
- LED 1 → D8  
- LED 2 → D9  
- LED 3 → D10  
- 부저 → D3  

## 📝 Arduino 코드

```cpp
#include <DHT.h>      
#include <Tone.h>

#define DHTPIN 7      
#define DHTTYPE DHT11 
#define CDS_PIN A0    
#define LED_PIN_1 8   
#define LED_PIN_2 9   
#define LED_PIN_3 10  
#define BUZZER_PIN 3

DHT dht(DHTPIN, DHTTYPE); 
Tone buzzer;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int lightLevel = analogRead(CDS_PIN);

  Serial.print("Temperature: "); Serial.print(temperature);
  Serial.print(" °C | Humidity: "); Serial.print(humidity);
  Serial.print(" % | Light Level: "); Serial.println(lightLevel);

  digitalWrite(LED_PIN_1, temperature > 24.6 ? HIGH : LOW);
  digitalWrite(LED_PIN_2, humidity > 42.1 ? HIGH : LOW);
  digitalWrite(LED_PIN_3, lightLevel < 10 ? HIGH : LOW);

  if (humidity > 42.1 && temperature > 24.6 && lightLevel < 10) {
    tone(BUZZER_PIN, 1000);
    delay(1000);
    noTone(BUZZER_PIN);
    delay(1000);
  }

  delay(2000);
}
