#include "HX711.h" 
#define DOUT A0 
#define CLK A1
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 
HX711 scale;
float calibration_factor = 578; 
float GRAM; // Pastikan menggunakan float untuk mendapatkan hasil lebih presisi

void setup() { 
  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  // Inisialisasi Serial dan HX711
  Serial.begin(9600); 
  scale.begin(DOUT, CLK); // Inisialisasi HX711 dengan pin DOUT dan CLK
  scale.set_scale(); 
  scale.tare(); // Mengatur pembacaan awal menjadi 0
  
  // Inisialisasi pin output
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() { 
  scale.set_scale(calibration_factor);
  GRAM = scale.get_units(5); // Mengambil nilai berat dalam gram dengan rata-rata 5 kali pembacaan
  Serial.println(GRAM);

  // Logika kontrol berdasarkan nilai GRAM
  if (GRAM >= 500) {
    lcd.clear(); 
    digitalWrite(3, HIGH); 
    digitalWrite(2, LOW); 
    lcd.setCursor(0, 0);
    lcd.print("OVERWEIGHT"); 
    lcd.setCursor(0, 1); 
    lcd.print("OVER="); 
    lcd.setCursor(6, 1); 
    lcd.print(GRAM - 250); 
    lcd.setCursor(9, 1); 
    lcd.print("gram");
  }
  else if (GRAM <= 10) { 
    lcd.clear();
    digitalWrite(2, LOW); 
    digitalWrite(3, LOW); 
    lcd.setCursor(0, 0); 
    lcd.print("MENUNGGU"); 
    lcd.setCursor(0, 1); 
    lcd.print("BARANG");
  }
  else if (GRAM > 10 && GRAM < 500) { 
    lcd.clear(); 
    digitalWrite(2, HIGH); 
    digitalWrite(3, LOW); 
    lcd.setCursor(0, 0); 
    lcd.print("TERISI"); 
    lcd.setCursor(0, 1); 
    lcd.print("Total="); 
    lcd.setCursor(7, 1); 
    lcd.print(GRAM); 
    lcd.setCursor(10, 1); 
    lcd.print("gram");
  }

  // Delay untuk memberikan waktu pembacaan yang cukup
  delay(500); 
}