
// Araba Testin için Ayarlandı.

#include <Arduino.h>
// Enable Pinleri
int EnA = 3;
int EnB = 11;

// İnput pinleri
int In1 = 2;
int In2 = 4;
int In3 = 12;
int In4 = 10;

// Extralar
int Far = 13;
int Stop = 8;

// LED pinleri
int ledKirmizi = 5;
int ledSari = 6;
int ledYesil = 7;

// Ultrasonik sensör pinleri
int trigPin = A0;
int echoPin = A1;

void setup() {
    Serial.begin(9600); // Seri haberleşme başlatma
    
    pinMode(EnA, OUTPUT); //Enable: A
    pinMode(EnB, OUTPUT); //Enable: B
    pinMode(In1, OUTPUT); // Motor kontrol pinleri OUTPUT olmalı
    pinMode(In2, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);
    
    // Extra (Farlar ve Stop ışıkları)
    pinMode(Far, OUTPUT);
    pinMode(Stop, OUTPUT);
    
    // LED pinleri ayarlama
    pinMode(ledKirmizi, OUTPUT);
    pinMode(ledSari, OUTPUT);
    pinMode(ledYesil, OUTPUT);
    
    // Ultrasonik sensör pinleri ayarlama
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}
// PWM Pinleri ile hız kontrolü

void ileri() {
    analogWrite(EnA, 255);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);

    analogWrite(EnB, 255);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
}

void geri() {
    analogWrite(EnA, 255);
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);

    analogWrite(EnB, 255);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
}

void dur() {
    analogWrite(EnA, LOW);
    analogWrite(EnB, LOW);
}

void Hafifsag() {
    analogWrite(EnA, 255); // Sağ motor tam hız
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);

    analogWrite(EnB, 0); // Sağ motor yarım hız
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);  // Sağ Motoru Durdur.
}

void Tamsag() {
    analogWrite(EnA, 255); // Sağ motor tam hız
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);

    analogWrite(EnB, 255); // Sağ motoru Tam Hız geri çevir
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
}

void Hafifsol() {
    analogWrite(EnA, 0);    // Sol motoru durdur.
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);

    analogWrite(EnB, 255); // Sağ motoru Tam Hız geri çevir
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
}

void Tamsol() {
    analogWrite(EnA, 255);    // Sol motoru Tam Hız Geri Çevir.
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);

    analogWrite(EnB, 255); // Sağ motoru Tam Hız geri çevir
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
}

void FarYak() {
    digitalWrite(Far, HIGH);
}

void FarSon() {
    digitalWrite(Far, LOW);
}

void StopYak() { // Arka ışıklar.
    digitalWrite(Stop, HIGH);
}

void StopSon() {
    digitalWrite(Stop, LOW);
}

// LED kontrol fonksiyonları
void ledleriSondur() {
    digitalWrite(ledKirmizi, LOW);
    digitalWrite(ledSari, LOW);
    digitalWrite(ledYesil, LOW);
}

void kirmiziYak() {
    digitalWrite(ledKirmizi, HIGH);
    digitalWrite(ledSari, LOW);
    digitalWrite(ledYesil, LOW);
}

void sariYak() {
    digitalWrite(ledKirmizi, LOW);
    digitalWrite(ledSari, HIGH);
    digitalWrite(ledYesil, LOW);
}

void yesilYak() {
    digitalWrite(ledKirmizi, LOW);
    digitalWrite(ledSari, LOW);
    digitalWrite(ledYesil, HIGH);
}

// Mesafe ölçüm fonksiyonu
float mesafeOlc() {
    // Sensörü temizleme
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Ultrasonik sinyal gönderme
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Yankı süresini ölçme
    long sure = pulseIn(echoPin, HIGH);
    
    // Süreyi mesafeye dönüştürme (cm cinsinden)
    float mesafe = sure * 0.034 / 2;
    
    return mesafe;
}

// Park sensörü fonksiyonu
void parkSensoru() {
    float mesafe = mesafeOlc();
    
    Serial.print("Mesafe: ");
    Serial.print(mesafe);
    Serial.println(" cm");
    
    // Mesafeye göre LED'leri kontrol etme
    if (mesafe < 10) {
        // Çok yakın - kırmızı LED yak, dur
        kirmiziYak();
        StopYak();
        dur();
    } else if (mesafe < 20) {
        // Yakın - sarı LED yak, yavaşla
        sariYak();
        analogWrite(EnA, 100); // Yavaş hız
        analogWrite(EnB, 100);
    } else if (mesafe < 30) {
        // Orta mesafe - yeşil LED yak
        yesilYak();
        analogWrite(EnA, 150); // Orta hız
        analogWrite(EnB, 150);
    } else {
        // Uzak mesafe - tüm LED'leri söndür
        ledleriSondur();
        analogWrite(EnA, 255); // Tam hız
        analogWrite(EnB, 255);
    }
}

void loop() {
    // Park sensörünü her 100ms'de bir kontrol et
    parkSensoru();
    delay(100);
    
    // Test için aşağıdaki satırları yorum satırından çıkarabilirsiniz
    /*
    ileri();
    delay(1000);
    geri();
    delay(1000);
    dur();
    delay(1000);
    */
}