#include <Arduino.h>

// 🚗 Bu kod: Çağdaş Özdemir yardımıyla yapılmıştır.
// Updated Date: 5/23/2025 - 23 Mayıs 2025 Cuma
// 🔌 Enable Pinleri
int EnA = 5;
int EnB = 10;

// 🔌 İnput pinleri
int In1 = 6;
int In2 = 7;
int In3 = 8;
int In4 = 9;

// 💡 Extralar
int Far = 13;

int Stop = 12;

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

// 🛑 Arabayı durdurur.
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
    digitalWrite(Far, HIGH);
}

// 🔅 Ön farları söndürür
void FarSon() {
    digitalWrite(Far, LOW);
}

// 🚨 Arka stop ışıklarını yakar
void StopYak() {

} // Arka ışıklar.

// 🔅 Arka stop ışıklarını söndürür
void StopSon() {

}

// 🔄 Ana döngü - temel test işlemleri

// Park Sensörü eklenebilir.
void loop() {
    ileri();     // ⬆️ İleri git
    delay(2000); // ⏱️ 2 saniye bekle
    dur();
    delay(500);
    geri();
    delay(2000); // 2 Saniye bekle
    dur();
    delay(500);
    Tamsag();
    delay(500);
    Tamsol();
    delay(500);
    dur();
    delay(500); // yarım Saniye bekle
}