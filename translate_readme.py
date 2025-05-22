#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
README.md dosyasını otomatik olarak izleyen ve değişiklikleri README_EN.md'ye çeviren script.
Bu script, README.md dosyasında yapılan değişiklikleri algılar ve içeriği İngilizce'ye çevirerek
README_EN.md dosyasını günceller.

Gereksinimler:
- Python 3.6+
- watchdog kütüphanesi (pip install watchdog)
- googletrans kütüphanesi (pip install googletrans==4.0.0-rc1)

Kullanım:
$ python translate_readme.py
"""

import os
import time
import re
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
from googletrans import Translator
import sys

# Çeviri için özel sözlük - Türkçe kelimelerin İngilizce karşılıkları
TRANSLATION_DICT = {
    "ArabaDIY": "CarDIY",
    "Proje Hakkında": "About the Project",
    "Donanım Gereksinimleri": "Hardware Requirements",
    "Pin Bağlantıları": "Pin Connections",
    "Kontrol Fonksiyonları": "Control Functions",
    "Park Sensörü Sistemi": "Parking Sensor System",
    "LED Uyarı Sistemi": "LED Warning System",
    "Test Etme": "Testing",
    "Sorun Giderme": "Troubleshooting",
    "Geliştirme Önerileri": "Development Suggestions",
    "Lisans": "License",
    "Bitiş": "Conclusion",
    "Not": "Note",
    "İçindekiler": "Contents",
    "Hareket Fonksiyonları": "Movement Functions",
    "Işık Kontrol Fonksiyonları": "Light Control Functions",
    "Mesafe Ölçümü": "Distance Measurement",
    "Park Asistanı": "Parking Assistant",
    "LED Kontrol Fonksiyonları": "LED Control Functions",
    "Motor Testi": "Motor Test",
    "Sensör Testi": "Sensor Test",
    "Işık Testi": "Light Test",
    "Dönüş Testi": "Turn Test",
    "Uzaktan Kontrol": "Remote Control",
    "Sesli Uyarı": "Audio Alert",
    "Akıllı Navigasyon": "Smart Navigation",
    "Hız Kontrolü": "Speed Control",
    "Veri İşleme": "Data Processing",
    "Sorun": "Problem",
    "Olası Neden": "Possible Cause",
    "Çözüm": "Solution",
    "Motorlar çalışmıyor": "Motors not working",
    "Bağlantı hatası": "Connection error",
    "Yetersiz güç": "Insufficient power",
    "L293D arızası": "L293D failure",
    "Ultrasonik sensör yanlış ölçüm yapıyor": "Ultrasonic sensor giving incorrect measurements",
    "Sensör arızası": "Sensor failure",
    "Gürültülü ortam": "Noisy environment",
    "LED'ler yanmıyor": "LEDs not lighting up",
    "Yanmış LED": "Burnt LED",
    "Arduino yanıt vermiyor": "Arduino not responding",
    "Kod hatası": "Code error",
    "Donanım arızası": "Hardware failure",
    "Pin bağlantılarını kontrol edin": "Check pin connections",
    "Batarya voltajını kontrol edin": "Check battery voltage",
    "Motor sürücü entegresini değiştirin": "Replace motor driver IC",
    "Echo ve Trig pin bağlantılarını kontrol edin": "Check Echo and Trig pin connections",
    "Sensörü değiştirin": "Replace the sensor",
    "Sensörün önündeki engelleri kaldırın": "Remove obstacles in front of the sensor",
    "LED bağlantılarını ve polariteyi kontrol edin": "Check LED connections and polarity",
    "LED'leri değiştirin": "Replace LEDs",
    "Kodu yeniden yükleyin": "Reload the code",
    "Arduino'yu sıfırlayın veya değiştirin": "Reset or replace Arduino",
    "Far": "Headlight",
    "Stop": "Brake Light",
    "Ön Farlar": "Front Lights",
    "Arka Lambaları": "Rear Lights",
    "Kırmızı LED": "Red LED",
    "Sarı LED": "Yellow LED",
    "Yeşil LED": "Green LED",
    "Tehlikeli yakınlık": "Dangerous proximity",
    "Yakın mesafe": "Close distance",
    "Orta mesafe": "Medium distance",
    "Güvenli mesafe": "Safe distance",
    "Tehlike uyarısı": "Danger warning",
    "Dikkat uyarısı": "Caution warning",
    "Güvenli ilerleme": "Safe to proceed",
    "Motor A Hız Kontrolü": "Motor A Speed Control",
    "Motor B Hız Kontrolü": "Motor B Speed Control",
    "Motor A Yön Kontrolü 1": "Motor A Direction Control 1",
    "Motor A Yön Kontrolü 2": "Motor A Direction Control 2",
    "Motor B Yön Kontrolü 1": "Motor B Direction Control 1",
    "Motor B Yön Kontrolü 2": "Motor B Direction Control 2",
    "Ultrasonik Sensör Trig Pin": "Ultrasonic Sensor Trig Pin",
    "Ultrasonik Sensör Echo Pin": "Ultrasonic Sensor Echo Pin",
    "Bağlantı": "Connection",
    "isteğe bağlı": "optional",
    "Kendin Yap": "Do It Yourself",
    "Araba şasisi": "Car chassis",
    "Güç kaynağı": "Power supply",
    "batarya paketi": "battery pack",
    "Jumper kablolar": "Jumper wires",
    "Breadboard": "Breadboard",
    "Arduino UNO/Nano": "Arduino UNO/Nano",
    "DC Motor": "DC Motor",
    "LED": "LED",
    "Bu proje eğitim amaçlıdır": "This project is for educational purposes",
    "gerçek araç sistemleri için güvenlik standartlarını karşılamaz": "does not meet safety standards for real vehicle systems",
    "Yalnızca hobi ve öğrenme amaçlı kullanılmalıdır": "It should be used for hobby and learning purposes only",
    "ArabaDIY Projesi": "CarDIY Project",
    "Çağdaş Özdemir ile yaptığımız bu projeyi bitirdik": "We have completed this project with Çağdaş Özdemir",
    "Görüşmek üzere": "See you soon",
    "Bizi takip ettiğiniz için teşekkür ederiz": "Thank you for following us",
    "Ve sevgili hocam": "And dear professor",
    "Bu projedeki kontrol fonksiyonları şunlardır": "The control functions in this project are",
    "Arabayı ileri hareket ettirir": "Moves the car forward",
    "iki motor da ileri yönde": "both motors forward",
    "Arabayı geri hareket ettirir": "Moves the car backward",
    "iki motor da geri yönde": "both motors backward",
    "Arabayı durdurur": "Stops the car",
    "iki motor da durur": "both motors stop",
    "Hafif sağa dönüş": "Slight right turn",
    "sağ motor durur, sol motor devam eder": "right motor stops, left motor continues",
    "Tam sağa dönüş": "Full right turn",
    "sol motor ileri, sağ motor geri": "left motor forward, right motor backward",
    "Hafif sola dönüş": "Slight left turn",
    "sol motor durur, sağ motor devam eder": "left motor stops, right motor continues",
    "Tam sola dönüş": "Full left turn",
    "sağ motor ileri, sol motor geri": "right motor forward, left motor backward",
    "Ön farları yakar": "Turns on the headlights",
    "Ön farları söndürür": "Turns off the headlights",
    "Arka lambaları yakar": "Turns on the brake lights",
    "Arka lambaları söndürür": "Turns off the brake lights",
    "Bu projenin en önemli özelliklerinden biri": "One of the most important features of this project is",
    "ultrasonik sensör kullanarak oluşturulan park sensörü sistemidir": "the parking sensor system created using an ultrasonic sensor",
    "Bu sistem şu şekilde çalışır": "This system works as follows",
    "HC-SR04 ultrasonik sensör kullanarak önündeki engele olan mesafeyi ölçer": "measures the distance to an obstacle in front using the HC-SR04 ultrasonic sensor",
    "Trig pininden 10 mikrosaniyelik bir pulse gönderilir": "A 10-microsecond pulse is sent from the Trig pin",
    "Echo pininden gelen yankıyı ölçer": "Measures the echo received from the Echo pin",
    "Ses hızını kullanarak mesafeyi hesaplar": "Calculates the distance using the speed of sound",
    "cm cinsinden": "in cm",
    "ölçülen mesafeye göre aracın hızını ayarlar ve LED'leri uygun şekilde yakar": "adjusts the car's speed and illuminates LEDs appropriately according to the measured distance",
    "Kırmızı LED yanar, araç durur, stop lambaları yanar": "Red LED lights up, car stops, brake lights turn on",
    "Sarı LED yanar, araç yavaşlar": "Yellow LED lights up, car slows down",
    "hız: 100/255": "speed: 100/255",
    "Yeşil LED yanar, araç orta hızda ilerler": "Green LED lights up, car moves at medium speed",
    "hız: 150/255": "speed: 150/255",
    "LED'ler söner, araç tam hızda ilerler": "LEDs turn off, car moves at full speed",
    "hız: 255/255": "speed: 255/255",
    "Park sensörü sisteminin görsel uyarı bileşeni olarak üç farklı renkte LED kullanılmaktadır": "Three different colored LEDs are used as a visual warning component of the parking sensor system",
    "Çok yakın mesafe": "Very close distance",
    "Tüm LED'leri kapatır": "Turns off all LEDs",
    "Sadece kırmızı LED'i yakar": "Turns on only the red LED",
    "Sadece sarı LED'i yakar": "Turns on only the yellow LED",
    "Sadece yeşil LED'i yakar": "Turns on only the green LED",
    "Bu sistem, gerçek arabalardaki park sensörlerine benzer şekilde sürücüye yaklaşma hızını ayarlaması için görsel geri bildirim sağlar": "This system provides visual feedback to the driver to adjust approaching speed, similar to parking sensors in real cars",
    "Projenizi düzgün bir şekilde test etmek için aşağıdaki adımları izleyin": "Follow these steps to properly test your project",
    "loop() fonksiyonundaki yorum satırlarını kaldırın": "Uncomment the sections in the loop() function",
    "Arduino'yu bilgisayarınıza bağlayın ve kodu yükleyin": "Connect the Arduino to your computer and upload the code",
    "Motorların sırasıyla ileri, geri hareket ettiğini ve durduğunu gözlemleyin": "Observe that the motors move forward, backward, and stop in sequence",
    "Ultrasonik sensörün önüne elinizi yavaşça yaklaştırın": "Slowly move your hand towards the ultrasonic sensor",
    "Seri monitörü açın (9600 baud) ve mesafe değerlerini izleyin": "Open the serial monitor (9600 baud) and monitor the distance values",
    "LED'lerin mesafeye göre doğru şekilde yanıp yanmadığını kontrol edin": "Check if the LEDs light up correctly according to the distance",
    "Işıkların beklendiği gibi yanıp yanmadığını kontrol edin": "Check if the lights turn on and off as expected",
    "Aracın doğru yöne döndüğünü doğrulayın": "Verify that the car turns in the correct direction",
    "Projenizde karşılaşabileceğiniz yaygın sorunlar ve çözümleri": "Common problems you might encounter in your project and their solutions",
    "Projenizi daha da geliştirmek için yapabileceğiniz bazı öneriler": "Some suggestions to further enhance your project",
    "HC-05/HC-06 Bluetooth modülü ekleyerek akıllı telefondan kontrol": "Add HC-05/HC-06 Bluetooth module for smartphone control",
    "Özel bir mobil uygulama geliştirme": "Develop a custom mobile application",
    "Buzzer ekleyerek sesli geri bildirim": "Add a buzzer for audio feedback",
    "Mesafe azaldıkça artan frekans veya hızda bip sesi": "Increasing frequency or rate of beeps as distance decreases",
    "Engellerden kaçınmak için otomatik rota belirleme": "Automatic route determination to avoid obstacles",
    "Birden fazla ultrasonik sensör kullanarak 360° algılama": "Use multiple ultrasonic sensors for 360° detection",
    "PWM değerlerini daha hassas ayarlama": "More precise adjustment of PWM values",
    "Kademeli hızlanma ve yavaşlama fonksiyonları": "Gradual acceleration and deceleration functions",
    "SD kart modülü ile mesafe verilerini kaydetme": "Save distance data with SD card module",
    "Sensör verilerini analiz etmek için bilgisayar arayüzü": "Computer interface for analyzing sensor data",
    "Bu proje MIT lisansı altında lisanslanmıştır": "This project is licensed under the MIT License",
    "Detaylar için `LICENSE` dosyasına bakınız": "See the `LICENSE` file for details",
    "6-12V olmalı": "should be 6-12V"
}

class ReadmeHandler(FileSystemEventHandler):
    def __init__(self, src_file, dest_file):
        self.src_file = src_file
        self.dest_file = dest_file
        self.last_modified = os.path.getmtime(src_file) if os.path.exists(src_file) else 0
        self.translator = Translator()
        
        # İlk çalıştırmada dosyayı çevir
        self.translate_file()
        
    def on_modified(self, event):
        if not event.is_directory and event.src_path == os.path.abspath(self.src_file):
            current_modified = os.path.getmtime(self.src_file)
            if current_modified > self.last_modified:
                self.last_modified = current_modified
                print(f"\n{time.strftime('%Y-%m-%d %H:%M:%S')} - README.md değişiklik algılandı, çeviriliyor...")
                time.sleep(1)  # Dosyanın tam olarak yazılmasını bekle
                self.translate_file()

    def translate_file(self):
        try:
            with open(self.src_file, 'r', encoding='utf-8') as file:
                content = file.read()
            
            # Mevcut README_EN.md içeriğini oku (varsa)
            old_content = ""
            if os.path.exists(self.dest_file):
                with open(self.dest_file, 'r', encoding='utf-8') as file:
                    old_content = file.read()
            
            # Dil butonlarını koru
            header_match = re.search(r'(<div align="right">.*?</div>)', content, re.DOTALL)
            if header_match:
                header = header_match.group(1)
            else:
                header = '<div align="right">\n  <a href="README.md"><img src="https://img.shields.io/badge/Dil-T%C3%BCrk%C3%A7e-red.svg?style=for-the-badge"></a>\n  <a href="README_EN.md"><img src="https://img.shields.io/badge/Language-English-blue.svg?style=for-the-badge"></a>\n</div>'
            
            # Başlık ve rozetleri değiştir
            content = re.sub(r'# ArabaDIY Projesi', '# CarDIY Project', content)
            
            # Sözlük tabanlı çeviri
            translated_content = self._translate_with_dict(content)
            
            # Sonuç dosyasını oluştur
            with open(self.dest_file, 'w', encoding='utf-8') as file:
                file.write(translated_content)
                
            print(f"README_EN.md başarıyla güncellendi.")
            
        except Exception as e:
            print(f"Hata oluştu: {str(e)}")
    
    def _translate_with_dict(self, content):
        """Metni sözlüğe göre çevirir."""
        # Önce özel eşleştirmeleri uygula
        for tr_text, en_text in TRANSLATION_DICT.items():
            content = content.replace(tr_text, en_text)
            
        # İçindekiler bölümünü düzelt
        content = content.replace("## 📋 İçindekiler", "## 📋 Contents")
        
        # Başlık kısmını düzelt
        content = content.replace("# ArabaDIY Projesi", "# CarDIY Project")
        
        # Metinde kalan Türkçe bölümleri çevir (Büyük metinler için)
        # Bu kısım yavaş olabilir, gerekirse kapatabilirsiniz
        try:
            # Paragrafları bul ve çevir
            paragraphs = re.findall(r'([^\n]+)', content)
            for paragraph in paragraphs:
                # Eğer paragraf Türkçe karakterler içeriyorsa ve çevrilmediyse
                if any(c in paragraph for c in 'çğıöşüÇĞİÖŞÜ') and len(paragraph) > 5:
                    # Sözlükte yoksa çevir
                    is_in_dict = False
                    for tr_text in TRANSLATION_DICT.keys():
                        if tr_text in paragraph:
                            is_in_dict = True
                            break
                    
                    if not is_in_dict:
                        try:
                            translated = self.translator.translate(paragraph, src='tr', dest='en').text
                            content = content.replace(paragraph, translated)
                            print(f"Çevirildi: {paragraph[:30]}... -> {translated[:30]}...")
                        except Exception as e:
                            print(f"Çeviri hatası: {str(e)}")
        except Exception as e:
            print(f"Detaylı çeviri sırasında hata: {str(e)}")
            
        return content

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    src_file = os.path.join(script_dir, 'README.md')
    dest_file = os.path.join(script_dir, 'README_EN.md')
    
    if not os.path.exists(src_file):
        print(f"Hata: {src_file} bulunamadı!")
        sys.exit(1)
    
    print("README.md dosyası izleniyor... (Çıkmak için Ctrl+C)")
    print(f"Değişiklikler otomatik olarak {dest_file} dosyasına çevrilecek.")
    
    event_handler = ReadmeHandler(src_file, dest_file)
    observer = Observer()
    observer.schedule(event_handler, script_dir, recursive=False)
    observer.start()
    
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()

if __name__ == "__main__":
    main()
