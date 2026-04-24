#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup(){
  pinMode(2, OUTPUT);
  pinMode(7, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" DETEKSI GERAK  ");
  lcd.setCursor(0,1);
  lcd.print("READY");
  delay(2000);
  lcd.clear();
}

void loop(){
  int gerak = digitalRead(7);

  if (gerak > 0) {
    lcd.setCursor(0,0);
    lcd.print("INFO");
    lcd.setCursor(0,1);
    lcd.print("ada maling weh");
    tone(2,1500,500);
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("INFO");
    lcd.setCursor(0,1);
    lcd.print("Aman");
    noTone(2);
  }
  delay(500);
}
