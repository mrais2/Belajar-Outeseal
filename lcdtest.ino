#include <Wire.h> // Library komunikasi I2C 
#include <LiquidCrystal_I2C.h> // Library modul I2C LCD

// default address 0x27 
// tipe LCD 16x2 (16,2)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 

void setup() {
  // inisialisasi LCD:
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Modul I2C LCD"); 
  lcd.setCursor(0, 1); 
  lcd.print("www.ardutech.com");
}

void loop() {
 
}