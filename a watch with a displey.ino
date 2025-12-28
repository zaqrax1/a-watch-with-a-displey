#include <Wire.h>                   // Для I2C
#include <LiquidCrystal_I2C.h>      // Для дисплея
#include <iarduino_RTC.h>           // Для RTC

// Создаём объект для DS1302 (пины: RST=6, CLK=8, DAT=7)
iarduino_RTC time(RTC_DS1302, 6, 8, 7);

// Создаём объект для LCD 1602 по I2C (адрес 0x27, 16 столбцов, 2 строки)
LiquidCrystal_I2C LCD(0x27, 16, 2);

void setup() {
  delay(300);
  LCD.init();                      // Инициализация дисплея
  LCD.backlight();                 // Включение подсветки
  time.begin();                    // Инициализация часов
  // Установка времени: секунды, минуты, часы, день, месяц, год, день недели
  time.settime(0, 14, 16, 27, 12, 25, 6); // 0сек, 14мин, 16ч, 27.12.2025, четверг
}

void loop() {
  // Более надежный способ обновления каждую секунду
  static unsigned long lastMillis = 0;
  if (millis() - lastMillis >= 1000) {
    lastMillis = millis();
    
    LCD.setCursor(0, 0);
    LCD.print(time.gettime("d M Y, D")); // Дата: "12 Jun 2020, Thu"
    LCD.setCursor(4, 1);
    LCD.print(time.gettime("H:i:s"));    // Время: "18:30:00"
  }
}
