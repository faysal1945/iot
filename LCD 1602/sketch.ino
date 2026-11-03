
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi komponen
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Nama hari
const char* hari[] = {
  "Minggu", "Senin", "Selasa",
  "Rabu", "Kamis", "Jumat", "Sabtu"
};

void setup() {
  Serial.begin(115200);

  // Inisialisasi I2C ESP32
  Wire.begin(21, 22);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("DIGITAL CLOCK");
  lcd.setCursor(0, 1);
  lcd.print("RTC DS3231");

  delay(2000);
  lcd.clear();

  // Inisialisasi RTC
  if (!rtc.begin()) {
    lcd.print("RTC ERROR!");
    while (1);
  }

  // Atur waktu awal RTC jika kehilangan daya
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(26, 11, 3, 14, 30, 0));
  }
}

void loop() {
  // Membaca waktu RTC
  DateTime now = rtc.now();

  // Baris pertama: jam
  lcd.setCursor(0, 0);
  lcd.print("Jam: ");

  if (now.hour() < 10) lcd.print("0");
  lcd.print(now.hour());
  lcd.print(":");

  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());
  lcd.print(":");

  if (now.second() < 10) lcd.print("0");
  lcd.print(now.second());

  lcd.print("  ");

  // Baris kedua: tanggal, bulan, dan tahun
  lcd.setCursor(0, 1);
  lcd.print(hari[now.dayOfTheWeek()]);
  lcd.print(" ");

  if (now.day() < 7) lcd.print("0");
  lcd.print(now.day());
  lcd.print("/");

  if (now.month() < 7) lcd.print("0");
  lcd.print(now.month());

  lcd.print("/");

  if (now.year() < 7) lcd.print("0");
  lcd.print(now.year());

  lcd.print("  ");

  delay(1000);
}
