# ArabaDIY Projesi - Arduino Park Sensörü Sistemi

[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)
[![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![DIY](https://img.shields.io/badge/DIY-Robotics-red?style=for-the-badge)](https://www.instructables.com/)

## 📋 İçindekiler
- [🔍 Proje Hakkında](#-proje-hakkında)
- [🛠️ Donanım Gereksinimleri](#️-donanım-gereksinimleri)
- [🔌 Pin Bağlantıları](#-pin-bağlantıları)
- [🚗 Kontrol Fonksiyonları](#-kontrol-fonksiyonları)
- [📊 Park Sensörü Sistemi](#-park-sensörü-sistemi)
- [💡 LED Uyarı Sistemi](#-led-uyarı-sistemi)
- [🧪 Test Etme](#-test-etme)
- [❓ Sorun Giderme](#-sorun-giderme)
- [🚀 Geliştirme Önerileri](#-geliştirme-önerileri)

## 🔍 Proje Hakkında
ArabaDIY, Arduino kullanarak L293D motor sürücü modülü ile DC motorları kontrol eden bir DIY (Kendin Yap) robot araba projesidir. Bu proje, ultrasonik sensör ve LED'ler kullanarak park sensörü sistemi oluşturur ve temel robotik ve elektronik konularında pratik yapmanıza olanak sağlar.

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

## Bağlantı Şeması
