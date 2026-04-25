# Smart Security System (Alarm Pendeteksi Maling)

## Identitas Anggota
| Nama                          | NIM        |
|------------------------------|------------|
| Eka Bintang Wicaksono        | H1D023054  |
| Dhimas Wildan Nur Zakariya   | H1D023050  |
| Putranto Surya Wijanarko     | H1D023048  |
| Muhammad Syahrial Hipdi      | H1D023047  |
| Raditya Yusuf Ramadhan       | H1D023057  |

## Deskripsi Projek
Sistem ini merupakan alarm keamanan berbasis Arduino yang menggunakan PIR sensor untuk mendeteksi gerakan dan Force Sensor untuk tekanan berupa injakan. Ketika gerakan terdeteksi dan terdapat injakan, sistem akan mengaktifkan buzzer sebagai alarm, menyalakan LED sebagai indikator visual, serta menampilkan pesan peringatan pada LCD melalui komunikasi I2C. Data status juga dikirim melalui komunikasi serial untuk monitoring. Ketika tombol ditekan maka system tidak lagi membaca, sangat berguna apabila ingin mematikan alarm. Suara buzzer bisa disetting dengan potensiometer

## Komponen
- Arduino UNO R3
- Breadboard
- Jumper
- PIR Sensor
- Force Sensor
- Buzzer (Piezo)
- LED
- LCD 16x2 I2C PCF8574-based, 39 (0x27)
- Resistor 220 Ω x2
- Push button
- Potensiometer

## Cara Kerja
Sistem akan mendeteksi gerakan menggunakan PIR sensor dan deteksi injakan dengan force.
Jika ada gerakan dan terdapat tekanan:
- Alarm (buzzer) berbunyi
- LED menyala
- LCD menampilkan peringatan
- Status dikirim ke Serial Monitor
- Jika perlu matikan dengan push button (dan sebaliknya) dan suara buzzer dengan potensiometer 

## Kalibrasi Analog

### Force Sensor
Berat tubuh manusia yang digunakan untuk deteks "maling" berada pada kisaran >46KG diibaratkan dengan 4.6N, sensor membaca dari 0.0 - 10.0N dengan resistensi berupa 220Ω maka didapatkan data sebagai berikut

| Pressure | ADC | Note      |
| -------- | --- | ----      |
| 0.0      | 0   | None      |
| 4.68     | 100 | Threshold |
| 10.0     | 159 | Max       |

### Potensiometer (untuk tone buzzer)
Dengan base resistance 250KΩ maka variabel freq berupa

| Knob      | ADC (freq)     |
| --------  | ---           |
| None      | 2000          | 
| Max       | 529   |

## Rangkaian
![](images/schematics.png)
