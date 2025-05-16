#include <Arduino.h>

// Enable Pinleri
int EnA = 3;
int EnB = 11;

// İnput pinleri
int In1 = 2;
int In2 = 4;
int In3 = 12;
int In4 = 10;

void setup() {
    pinMode(EnA, OUTPUT); //Enable: A
    pinMode(EnB, OUTPUT); //Enable: B
    pinMode(In1, INPUT); // Mod: Output olabilir.
    pinMode(In2, INPUT); // Mod: Output olabilir.
    pinMode(In3, INPUT); // Mod: Output olabilir.
    pinMode(In4, INPUT); // Mod: Output olabilir.

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
void loop() {
    ileri();
    delay(1000);
    geri();
    delay(1000);
    dur();
    delay(1000);
}