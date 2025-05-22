<div align="right">
  <a href="README.md"><img src="https://img.shields.io/badge/Dil-T%C3%BCrk%C3%A7e-red.svg?style=for-the-badge"></a>
  <a href="README_EN.md"><img src="https://img.shields.io/badge/Language-English-blue.svg?style=for-the-badge"></a>
</div>

# ArabaDIY Projesi

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
- [🔄 Güncellemeler](#-güncellemeler)
- [📄 Lisans](#-lisans)
- [✨ Bitiş](#-bitiş)
- [📝 Not](#-not)

## 🔍 Proje Hakkında
ArabaDIY, Arduino kullanarak L293D motor sürücü modülü ile DC motorları kontrol eden bir DIY (Kendin Yap) robot araba projesidir. Bu proje, ultrasonik sensör ve LED'ler kullanarak park sensörü sistemi oluşturur ve temel robotik ve elektronik konularında pratik yapmanıza olanak sağlar.

## 🛠️ Donanım Gereksinimleri
- Arduino UNO/Nano
- L293D Motor Sürücü Entegresi veya Motor Sürücü Shield
- 2 adet DC Motor
- Araba şasisi
- Güç kaynağı (batarya paketi, 6-12V)
- Jumper kablolar
- Breadboard (isteğe bağlı)

## 🔌 Pin Bağlantıları
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

## 🚗 Kontrol Fonksiyonları

Bu projedeki kontrol fonksiyonları şunlardır:

### 🔄 Hareket Fonksiyonları
- `ileri()`: Arabayı ileri hareket ettirir (iki motor da ileri yönde)
- `geri()`: Arabayı geri hareket ettirir (iki motor da geri yönde)
- `dur()`: Arabayı durdurur (iki motor da durur)
- `Hafifsag()`: Hafif sağa dönüş (sağ motor durur, sol motor devam eder)
- `Tamsag()`: Tam sağa dönüş (sol motor ileri, sağ motor geri)
- `Hafifsol()`: Hafif sola dönüş (sol motor durur, sağ motor devam eder)
- `Tamsol()`: Tam sola dönüş (sağ motor ileri, sol motor geri)

### 💡 Işık Kontrol Fonksiyonları
- `FarYak()`: Ön farları yakar
- `FarSon()`: Ön farları söndürür
- `StopYak()`: Arka lambaları yakar
- `StopSon()`: Arka lambaları söndürür

## 📊 Park Sensörü Sistemi

Bu projenin en önemli özelliklerinden biri, ultrasonik sensör kullanarak oluşturulan park sensörü sistemidir. Bu sistem şu şekilde çalışır:

### 📏 Mesafe Ölçümü
`mesafeOlc()` fonksiyonu, HC-SR04 ultrasonik sensör kullanarak önündeki engele olan mesafeyi ölçer:

1. Trig pininden 10 mikrosaniyelik bir pulse gönderilir
2. Echo pininden gelen yankıyı ölçer
3. Ses hızını kullanarak mesafeyi hesaplar (cm cinsinden)

### 🅿️ Park Asistanı
`parkSensoru()` fonksiyonu, ölçülen mesafeye göre aracın hızını ayarlar ve LED'leri uygun şekilde yakar:

- **< 10 cm**: Tehlikeli yakınlık - Kırmızı LED yanar, araç durur, stop lambaları yanar
- **10-20 cm**: Yakın mesafe - Sarı LED yanar, araç yavaşlar (hız: 100/255)
- **20-30 cm**: Orta mesafe - Yeşil LED yanar, araç orta hızda ilerler (hız: 150/255)
- **> 30 cm**: Güvenli mesafe - LED'ler söner, araç tam hızda ilerler (hız: 255/255)

## 💡 LED Uyarı Sistemi

Park sensörü sisteminin görsel uyarı bileşeni olarak üç farklı renkte LED kullanılmaktadır:

- **🔴 Kırmızı LED (D5)**: Çok yakın mesafe (< 10 cm) - Tehlike uyarısı
- **🟡 Sarı LED (D6)**: Yakın mesafe (10-20 cm) - Dikkat uyarısı
- **🟢 Yeşil LED (D7)**: Güvenli mesafe (20-30 cm) - Güvenli ilerleme

### 🎛️ LED Kontrol Fonksiyonları
- `ledleriSondur()`: Tüm LED'leri kapatır
- `kirmiziYak()`: Sadece kırmızı LED'i yakar
- `sariYak()`: Sadece sarı LED'i yakar
- `yesilYak()`: Sadece yeşil LED'i yakar

Bu sistem, gerçek arabalardaki park sensörlerine benzer şekilde sürücüye yaklaşma hızını ayarlaması için görsel geri bildirim sağlar.

## 🧪 Test Etme

Projenizi düzgün bir şekilde test etmek için aşağıdaki adımları izleyin:

### 🔄 Motor Testi
- `loop()` fonksiyonundaki yorum satırlarını kaldırın
- Arduino'yu bilgisayarınıza bağlayın ve kodu yükleyin
- Motorların sırasıyla ileri, geri hareket ettiğini ve durduğunu gözlemleyin

### 📏 Sensör Testi
- Ultrasonik sensörün önüne elinizi yavaşça yaklaştırın
- Seri monitörü açın (9600 baud) ve mesafe değerlerini izleyin
- LED'lerin mesafeye göre doğru şekilde yanıp yanmadığını kontrol edin

### 💡 Işık Testi
- `FarYak()`, `FarSon()`, `StopYak()` ve `StopSon()` fonksiyonlarını `loop()` içinde test edin
- Işıkların beklendiği gibi yanıp yanmadığını kontrol edin

### 🔄 Dönüş Testi
- `Hafifsag()`, `Tamsag()`, `Hafifsol()` ve `Tamsol()` fonksiyonlarını test edin
- Aracın doğru yöne döndüğünü doğrulayın

## ❓ Sorun Giderme

Projenizde karşılaşabileceğiniz yaygın sorunlar ve çözümleri:

| 🔧 Sorun | 🔍 Olası Neden | ✅ Çözüm |
|-------|-------------|-------|
| 🚫 Motorlar çalışmıyor | Bağlantı hatası | Pin bağlantılarını kontrol edin |
| | Yetersiz güç | Batarya voltajını kontrol edin (6-12V olmalı) |
| | L293D arızası | Motor sürücü entegresini değiştirin |
| 📏 Ultrasonik sensör yanlış ölçüm yapıyor | Bağlantı hatası | Echo ve Trig pin bağlantılarını kontrol edin |
| | Sensör arızası | Sensörü değiştirin |
| | Gürültülü ortam | Sensörün önündeki engelleri kaldırın |
| 💡 LED'ler yanmıyor | Bağlantı hatası | LED bağlantılarını ve polariteyi kontrol edin |
| | Yanmış LED | LED'leri değiştirin |
| 🔄 Arduino yanıt vermiyor | Kod hatası | Kodu yeniden yükleyin |
| | Donanım arızası | Arduino'yu sıfırlayın veya değiştirin |

## 🚀 Geliştirme Önerileri

Projenizi daha da geliştirmek için yapabileceğiniz bazı öneriler:

### 📱 Uzaktan Kontrol
- HC-05/HC-06 Bluetooth modülü ekleyerek akıllı telefondan kontrol
- Özel bir mobil uygulama geliştirme

### 🔊 Sesli Uyarı
- Buzzer ekleyerek sesli geri bildirim
- Mesafe azaldıkça artan frekans veya hızda bip sesi

### 🧠 Akıllı Navigasyon
- Engellerden kaçınmak için otomatik rota belirleme
- Birden fazla ultrasonik sensör kullanarak 360° algılama

### ⚡ Hız Kontrolü
- PWM değerlerini daha hassas ayarlama
- Kademeli hızlanma ve yavaşlama fonksiyonları

### 💾 Veri İşleme
- SD kart modülü ile mesafe verilerini kaydetme
- Sensör verilerini analiz etmek için bilgisayar arayüzü

## 🔄 Güncellemeler

Projenin en son güncellemeleri, değişiklikleri ve düzeltmeleri GitHub releases sayfasında bulabilirsiniz. Her sürüm için detaylı açıklamalar ve yeni özellikler listelenmiştir.

### Son Sürüm (v1.0.0)
- İlk resmi sürüm
- Temel motor kontrol fonksiyonları eklendi
- Ultrasonik sensör desteği eklendi
- LED uyarı sistemi tamamlandı

### Önceki Sürümler
Önceki sürümlerin tüm detayları ve değişiklik geçmişi için [GitHub Releases](https://github.com/MertGtHub/ArabaDIY/releases) sayfasını ziyaret ediniz.

## 📄 Lisans

Bu proje MIT lisansı altında lisanslanmıştır. Detaylar için `LICENSE` dosyasına bakınız.

## ✨ Bitiş
Bizi takip ettiğiniz için teşekkür ederiz.
Ve sevgili hocam: Çağdaş Özdemir ile yaptığımız bu projeyi bitirdik.
Görüşmek üzere 👋🚀

## 📝 Not
**Bu proje eğitim amaçlıdır ve gerçek araç sistemleri için güvenlik standartlarını karşılamaz. Yalnızca hobi ve öğrenme amaçlı kullanılmalıdır.**
