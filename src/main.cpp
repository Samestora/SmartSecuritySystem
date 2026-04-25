/*
 * Smart Security System
 * Sistem keamanan menggunakan PIR, FSR, RGB LED, buzzer, LCD, dan interrupt button
*/

#include <Wire.h>                 // Library komunikasi I2C
#include <LiquidCrystal_I2C.h>   // Library untuk LCD I2C

LiquidCrystal_I2C lcd(0x27,16,2); // Inisialisasi LCD alamat 0x27, 16 kolom 2 baris

// ===== PIN =====
#define PIR 4        // Pin digital untuk sensor PIR (input gerakan)
#define BUZZER 5     // Pin digital untuk buzzer (output suara)
#define BUTTON 2     // Pin interrupt untuk push button

#define RED 9        // Pin PWM untuk LED merah
#define GREEN 10     // Pin PWM untuk LED hijau
#define BLUE 11      // Pin PWM untuk LED biru

#define PRESSURE A0  // Pin analog untuk sensor tekanan (FSR)
#define POT A3       // Pin analog untuk potensiometer

// ===== VAR =====
volatile bool systemActive = true; // Status sistem (aktif/nonaktif), volatile karena dipakai interrupt
bool ledState = false;             // Status untuk efek blink LED

// ===== INTERRUPT =====
void toggleSystem() {
  systemActive = !systemActive; // Membalik status sistem saat tombol ditekan
}

// ===== SETUP =====
void setup() {
  pinMode(PIR, INPUT);              // Set PIR sebagai input
  pinMode(BUZZER, OUTPUT);          // Set buzzer sebagai output
  pinMode(BUTTON, INPUT_PULLUP);    // Button pakai internal pull-up resistor

  pinMode(RED, OUTPUT);             // LED merah output
  pinMode(GREEN, OUTPUT);           // LED hijau output
  pinMode(BLUE, OUTPUT);            // LED biru output

  attachInterrupt(digitalPinToInterrupt(BUTTON), toggleSystem, FALLING);
  // Interrupt dipicu saat tombol ditekan (HIGH → LOW)

  Serial.begin(9600);               // Memulai komunikasi serial

  lcd.init();                       // Inisialisasi LCD
  lcd.backlight();                  // Menyalakan backlight LCD

  lcd.setCursor(0,0);               // Posisi kolom 0 baris 0
  lcd.print("ANTI MALING");         // Tampilkan judul
  delay(1500);                      // Tunda 1.5 detik
  lcd.clear();                      // Bersihkan layar LCD
}

// ===== LOOP =====
void loop() {
  int pirState = digitalRead(PIR);     // Membaca status PIR (HIGH/LOW)
  int pressureVal = analogRead(PRESSURE); // Membaca nilai tekanan (0–1023)
  int potVal = analogRead(POT);        // Membaca nilai potensiometer

  // mapping frekuensi buzzer dari potensiometer (500–2000 Hz)
  int freq = map(potVal, 0, 1023, 500, 2000);

  // ===== SERIAL (SELALU AKTIF) =====
  Serial.print("System: ");
  Serial.print(systemActive ? "ON" : "OFF");   // Status sistem
  Serial.print(" | PIR: ");
  Serial.print(pirState);                      // Status PIR
  Serial.print(" | Pressure: ");
  Serial.print(pressureVal);                   // Nilai ADC tekanan
  Serial.print(" | Freq: ");
  Serial.println(freq);                        // Frekuensi buzzer

  // ===== LOGIKA =====
  if (systemActive) { // Jika sistem aktif

    if (pirState == HIGH && pressureVal > 100) {
      // Jika ada gerakan DAN tekanan melebihi threshold

      // LCD
      lcd.setCursor(0,0);
      lcd.print("WARNING        ");  // Tampilkan peringatan
      lcd.setCursor(0,1);
      lcd.print("ADA MALING!    "); // Pesan alarm

      // Buzzer
      tone(BUZZER, freq); // Bunyi buzzer sesuai frekuensi

      // RGB BLINK (merah)
      ledState = !ledState; // Toggle untuk efek kedip

      if (ledState) {
        analogWrite(RED, 255);   // LED merah nyala
        analogWrite(GREEN, 0);   // Hijau mati
        analogWrite(BLUE, 0);    // Biru mati
      } else {
        analogWrite(RED, 0);     // Semua mati (blink)
        analogWrite(GREEN, 0);
        analogWrite(BLUE, 0);
      }

    } else {
      // kondisi aman (tidak ada gerakan atau tekanan kecil)

      lcd.setCursor(0,0);
      lcd.print("STATUS         "); // Status normal
      lcd.setCursor(0,1);
      lcd.print("AMAN           "); // Aman

      noTone(BUZZER); // Matikan buzzer

      // LED hijau stabil
      analogWrite(RED, 0);
      analogWrite(GREEN, 255);   // Hijau menyala
      analogWrite(BLUE, 0);
    }

  } else {
    // SYSTEM OFF (dari interrupt)

    lcd.setCursor(0,0);
    lcd.print("SYSTEM OFF     "); // Sistem dimatikan
    lcd.setCursor(0,1);
    lcd.print("DISABLED       "); // Alarm nonaktif

    noTone(BUZZER); // Buzzer mati

    // LED biru sebagai indikator OFF
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 255);
  }

  delay(300); // Delay untuk stabilisasi dan efek blink
}
