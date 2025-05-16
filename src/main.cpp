#include <Arduino.h>

int EnA = 3;
int EnB = 11;

int In1 = 2;
// int In2 =
int In3 = 12;
// int In4 =
void setup() {
    pinMode(EnA, OUTPUT);
    pinMode(EnB, OUTPUT);
    pinMode(In1, INPUT);
    // pinMode(In2, INPUT);
    pinMode(In3, INPUT);
    // pinMode(In4, INPUT); 

}

void loop() {
    // PWM Pinleri ile hız kontrolü
    analogWrite(EnA, 255);
    digitalWrite(In1, HIGH);

    analogWrite(EnB, 255);
    digitalWrite(In3, HIGH);
}