# ArabaDIY Projesi
# ArabaDIY - Arduino Park Sensörü Projesi

Bu proje, Arduino kullanarak oluşturulmuş bir robot araba için park sensörü sistemi içermektedir. Ultrasonik sensör ve LED'ler kullanılarak arabanın engelleri algılaması ve buna göre davranması sağlanmıştır.

## Donanım Gereksinimleri

- Arduino Uno/Nano/Mega
- L298N Motor Sürücü Kartı
- 2 adet DC Motor
- Ultrasonik Mesafe Sensörü (HC-SR04)
- 3 adet LED (Kırmızı, Sarı, Yeşil)
- 3 adet 220 ohm direnç (LED'ler için)
- Jumper kablolar
- Güç kaynağı (6-12V, motor beslemesi için)

## Pin Bağlantıları

### Motor Sürücü Bağlantıları
- EnA: 3 (PWM)
- EnB: 11 (PWM)
- In1: 2
- In2: 4
- In3: 12
- In4: 10

### LED Bağlantıları
- Kırmızı LED: 5
- Sarı LED: 6
- Yeşil LED: 7
- Ön Far: 13
- Stop Lambası: 8

### Ultrasonik Sensör Bağlantıları
- Trig Pin: A0
- Echo Pin: A1

## Özellikler

1. **Temel Hareket Kontrolleri**:
   - İleri gitme
   - Geri gitme
   - Durma
   - Hafif sağa dönme
   - Tam sağa dönme
   - Hafif sola dönme
   - Tam sola dönme

2. **Park Sensörü Sistemi**:
   - Mesafe ölçümü (Ultrasonik sensör ile)
   - Engele yaklaşma durumuna göre otomatik hız ayarı
   - Çok yakın engellerde otomatik durma

3. **LED Uyarı Sistemi**:
   - Kırmızı LED: Çok yakın engel (10 cm'den az) - Durma
   - Sarı LED: Yakın engel (10-20 cm arası) - Yavaşlama
   - Yeşil LED: Orta mesafe engel (20-30 cm arası) - Orta hız
   - LED'ler kapalı: Uzak engel (30 cm'den fazla) - Tam hız

4. **Ek Fonksiyonlar**:
   - Ön farları yakma/söndürme
   - Stop lambalarını yakma/söndürme
   - Seri port üzerinden mesafe bilgilerini görüntüleme

## Kod Açıklaması

Kod şu ana bölümlerden oluşmaktadır:

1. **Pin Tanımlamaları**: Motorlar, LED'ler ve sensörler için pin tanımlamaları
2. **Setup Fonksiyonu**: Pinlerin giriş/çıkış ayarları ve seri haberleşme başlatma
3. **Hareket Fonksiyonları**: İleri, geri, durma ve dönüş fonksiyonları
4. **LED Kontrol Fonksiyonları**: LED'leri açma/kapama fonksiyonları
5. **Mesafe Ölçüm Fonksiyonu**: Ultrasonik sensör ile mesafe ölçümü
6. **Park Sensörü Fonksiyonu**: Mesafeye göre davranış ve LED uyarı sistemi
7. **Loop Fonksiyonu**: Ana programın sürekli çalışan kısmı

## Test Etme

Projeyi test etmek için aşağıdaki adımları izleyebilirsiniz:

### 1. Park Sensörü Testleri

1. Arduino'yu bilgisayarınıza bağlayın ve kodu yükleyin.
2. Seri Monitörü açın (9600 baud).
3. Ultrasonik sensörün önüne elinizi veya bir cisim yaklaştırın.
4. Seri monitörde ölçülen mesafeyi takip edin.
5. Farklı mesafelerde LED'lerin ve motorların davranışını gözlemleyin:
   - 30+ cm: LED'ler sönük, motorlar tam hız
   - 20-30 cm: Yeşil LED yanar, motorlar orta hız
   - 10-20 cm: Sarı LED yanar, motorlar düşük hız
   - 0-10 cm: Kırmızı LED ve stop lambası yanar, motorlar durur

### 2. Manuel Hareket Testleri

Loop fonksiyonundaki yorum satırına alınmış test kodlarını aktif hale getirmek için:

1. Loop fonksiyonunda bulunan aşağıdaki kodu yorum işaretlerinden çıkarın:
## Proje Hakkında
ArabaDIY, Arduino kullanarak L293D motor sürücü modülü ile DC motorları kontrol eden bir DIY (Kendin Yap) robot araba projesidir. Bu proje, basit bir hareket sistemi geliştirerek robotik ve elektronik konularında pratik yapmanıza olanak sağlar.

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
