# ArabaDIY Projesi - Arduino Park Sensörü Sistemi

[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)
[![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![DIY](https://img.shields.io/badge/DIY-Robotics-red?style=for-the-badge)](https://www.instructables.com/)

## 📋 İçindekiler
- [🔍 Proje Hakkında](#proje-hakkında)
- [🛠️ Donanım Gereksinimleri](#donanım-gereksinimleri)
- [🔌 Pin Bağlantıları](#pin-bağlantıları)
- [🚗 Kontrol Fonksiyonları](#kontrol-fonksiyonları)
- [📊 Park Sensörü Sistemi](#park-sensörü-sistemi)
- [💡 LED Uyarı Sistemi](#led-uyarı-sistemi)
- [🧪 Test Etme](#test-etme)
- [❓ Sorun Giderme](#sorun-giderme)
- [🚀 Geliştirme Önerileri](#geliştirme-önerileri)

## Proje Hakkında
🔍 ArabaDIY, Arduino kullanarak L293D motor sürücü modülü ile DC motorları kontrol eden bir DIY (Kendin Yap) robot araba projesidir. Bu proje, ultrasonik sensör ve LED'ler kullanarak park sensörü sistemi oluşturur ve temel robotik ve elektronik konularında pratik yapmanıza olanak sağlar.

## Donanım Gereksinimleri
- Arduino UNO/Nano
- L293D Motor Sürücü Entegresi veya Motor Sürücü Shield
- 2 adet DC Motor
- Araba şasisi
- Güç kaynağı (batarya paketi, 6-12V)
- Jumper kablolar
- Breadboard (isteğe bağlı)

## Pin Bağlantıları
| Arduino Pin | Bağlantı       |
|-------------|----------------|
| D3 (PWM)    | EnA (Motor A Hız Kontrolü) |
| D11 (PWM)   | EnB (Motor B Hız Kontrolü) |
| D2          | In1 (Motor A Yön Kontrolü 1) |
| D4          | In2 (Motor A Yön Kontrolü 2) |
| D12         | In3 (Motor B Yön Kontrolü 1) |
| D10         | In4 (Motor B Yön Kontrolü 2) |
| D13         | Far (Ön Farlar) |
| D8          | Stop (Arka Lambaları) |
| D5          | Kırmızı LED |
| D6          | Sarı LED |
| D7          | Yeşil LED |
| A0          | Ultrasonik Sensör Trig Pin |
| A1          | Ultrasonik Sensör Echo Pin |

## Kontrol Fonksiyonları

Bu projedeki kontrol fonksiyonları şunlardır:

### Hareket Fonksiyonları
- `ileri()`: Arabayı ileri hareket ettirir (iki motor da ileri yönde)
- `geri()`: Arabayı geri hareket ettirir (iki motor da geri yönde)
- `dur()`: Arabayı durdurur (iki motor da durur)
- `Hafifsag()`: Hafif sağa dönüş (sağ motor durur, sol motor devam eder)
- `Tamsag()`: Tam sağa dönüş (sol motor ileri, sağ motor geri)
- `Hafifsol()`: Hafif sola dönüş (sol motor durur, sağ motor devam eder)
- `Tamsol()`: Tam sola dönüş (sağ motor ileri, sol motor geri)

### Işık Kontrol Fonksiyonları
- `FarYak()`: Ön farları yakar
- `FarSon()`: Ön farları söndürür
- `StopYak()`: Arka lambaları yakar
- `StopSon()`: Arka lambaları söndürür

## Park Sensörü Sistemi

Bu projenin en önemli özelliklerinden biri, ultrasonik sensör kullanarak oluşturulan park sensörü sistemidir. Bu sistem şu şekilde çalışır:

### Mesafe Ölçümü
`mesafeOlc()` fonksiyonu, HC-SR04 ultrasonik sensör kullanarak önündeki engele olan mesafeyi ölçer:

1. Trig pininden 10 mikrosaniyelik bir pulse gönderilir
2. Echo pininden gelen yankıyı ölçer
3. Ses hızını kullanarak mesafeyi hesaplar (cm cinsinden)
