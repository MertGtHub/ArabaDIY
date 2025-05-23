#include <Arduino.h>

// 🚗 Bu kod: Çağdaş Özdemir yardımıyla yapılmıştır.
// Updated Date: 5/23/2025 - 23 Mayıs 2025 Cuma
// 🔌 Enable Pinleri
int EnA = 3;
int EnB = 11;

// 🔌 İnput pinleri
int In1 = 2;
int In2 = 4;
int In3 = 12;
int In4 = 10;

// 💡 Extralar
int Far = 13;

// int Stop = 8;

// 🛠️ Arduino pin ayarlarını yapılandırma
void setup() {
    pinMode(EnA, OUTPUT); //Enable: A Kiliti
    pinMode(EnB, OUTPUT); //Enable: B Kiliti
    // Input:
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);
    // Extra (Farlar ve Stop ışıkları)
    // pinMode(Far, OUTPUT);
    // pinMode(Stop, OUTPUT);

}
// 🚗 PWM Pinleri ile hız kontrolü

// ⬆️ Arabayı ileri hareket ettirir
// İki motor da ileri yönde çalışır
void ileri() {
    analogWrite(EnA, 255);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);

    analogWrite(EnB, 255);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
}

// ⬇️ Arabayı geri hareket ettirir
// İki motor da geri yönde çalışır
void geri() {
    analogWrite(EnA, 255);
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);

    analogWrite(EnB, 255);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
}

// 🛑 Arabayı durdurur
// İki motor da durdurulur
void dur() {
    analogWrite(EnA, LOW);
    analogWrite(EnB, LOW);
}

// ↗️ Hafif sağa dönüş yapar
// Sağ motor tam hız çalışır, sol motor durdurulur
void Hafifsag() {
    analogWrite(EnA, 255); // Sağ motor tam hız
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);

    analogWrite(EnB, 0); // Sağ motor yarım hız
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);  // Sağ Motoru Durdur.
}

// ➡️ Tam sağa dönüş yapar
// Sol motor ileri, sağ motor geri yönde çalışır
void Tamsag() {
    analogWrite(EnA, 255); // Sağ motor tam hız
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);

    analogWrite(EnB, 255); // Sağ motoru Tam Hız geri çevir
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
}

// ↖️ Hafif sola dönüş yapar
// Sol motor durdurulur, sağ motor tam hız çalışır
void Hafifsol() {
    analogWrite(EnA, 0);    // Sol motoru durdur.
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);

    analogWrite(EnB, 255); // Sağ motoru Tam Hız geri çevir
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
}

// ⬅️ Tam sola dönüş yapar
// Sağ motor ileri, sol motor geri yönde çalışır
void Tamsol() {
    analogWrite(EnA, 255);    // Sol motoru Tam Hız Geri Çevir.
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);

    analogWrite(EnB, 255); // Sağ motoru Tam Hız geri çevir
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
}

// 💡 Ön farları yakar
void FarYak() {

}

// 🔅 Ön farları söndürür
void FarSon() {

}

// 🚨 Arka stop ışıklarını yakar
void StopYak() {} // Arka ışıklar.

// 🔅 Arka stop ışıklarını söndürür
void StopSon() {}

// 🔄 Ana döngü - temel test işlemleri
// Park Sensörü eklenebilir.
void loop() {
    ileri();     // ⬆️ İleri git
    delay(1000); // ⏱️ 1 saniye bekle
    geri();      // ⬇️ Geri git
    delay(1000); // ⏱️ 1 saniye bekle
    dur();       // 🛑 Dur
    delay(1000); // ⏱️ 1 saniye bekle
}