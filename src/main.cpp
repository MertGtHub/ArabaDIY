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

// int Stop = 8;

void setup() {
    pinMode(EnA, OUTPUT); //Enable: A
    pinMode(EnB, OUTPUT); //Enable: B
    pinMode(In1, INPUT); // Mod: Output olabilir.
    pinMode(In2, INPUT); // Mod: Output olabilir.
    pinMode(In3, INPUT); // Mod: Output olabilir.
    pinMode(In4, INPUT); // Mod: Output olabilir.
    // Extra
    pinMode(Far, OUTPUT);

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
void loop() {
    ileri();
    delay(1000);
    geri();
    delay(1000);
    dur();
    delay(1000);
}