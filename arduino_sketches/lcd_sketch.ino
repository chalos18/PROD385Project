#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
};

const char* messages[] = {
  "Climbing now!",
  "Back in one hour",
  "Love you"
};

int messageCount = 3;
int messageIndex = 0;

void showMessage(const char* text) {
  lcd.clear();

  lcd.setCursor(16, 0);
  lcd.print(text);


  for (int i = 0; i < 32; i++) {
    lcd.scrollDisplayLeft();
    lcd.write(byte(0));
    delay(300);
  }

  delay(1500);
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, heart);
}

void loop() {
  showMessage(messages[messageIndex]);

  messageIndex++;
  if (messageIndex >= messageCount) {
    messageIndex = 0;
  }
}
