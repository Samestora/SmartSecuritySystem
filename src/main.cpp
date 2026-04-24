#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define BUZZER 2
#define PIR 7
#define BUTTON 3
#define POT A0

volatile bool systemActive = true;

void toggleSystem() {
  systemActive = !systemActive;
}

void setup(){
  pinMode(BUZZER, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON), toggleSystem, FALLING);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print(" DETEKSI GERAK ");
  lcd.setCursor(0,1);
  lcd.print("READY");
  delay(2000);
  lcd.clear();
}

void loop(){
  int gerak = digitalRead(PIR);
  int nilaiADC = analogRead(POT);
  int frek = map(nilaiADC, 0, 1023, 500, 2000);

  // ===== SERIAL MONITOR =====
  Serial.print("System: ");
  Serial.print(systemActive ? "ON" : "OFF");
  Serial.print(" | Gerak: ");
  Serial.print(gerak ? "ADA" : "AMAN");
  Serial.print(" | ADC: ");
  Serial.print(nilaiADC);
  Serial.print(" | Frek: ");
  Serial.println(frek);

  // ===== LOGIKA UTAMA =====
  if (systemActive) {
    if (gerak > 0) {
      lcd.setCursor(0,0);
      lcd.print("INFO          ");
      lcd.setCursor(0,1);
      lcd.print("Ada maling!   ");
      tone(BUZZER, frek);
    } else {
      lcd.setCursor(0,0);
      lcd.print("INFO          ");
      lcd.setCursor(0,1);
      lcd.print("Aman          ");
      noTone(BUZZER);
    }
  } else {
    lcd.setCursor(0,0);
    lcd.print("SYSTEM OFF    ");
    lcd.setCursor(0,1);
    lcd.print("Alarm mati    ");
    noTone(BUZZER);
  }

  delay(500);
}
