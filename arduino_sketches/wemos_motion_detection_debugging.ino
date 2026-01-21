#define PIR_PIN D2
#define LED_PIN D4

unsigned long motionStart = 0;
unsigned long motionEnd   = 0;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // LED off (inverted)
  Serial.begin(115200);
  delay(2000);
  Serial.println("\nBoot OK – PIR timing debug");
}

void loop() {
  static bool motionDetected = false;
  static unsigned long lastLowTime = 0;

  int pirState = digitalRead(PIR_PIN);
  unsigned long now = millis();

  if (pirState == HIGH && !motionDetected) {
    motionDetected = true;
    motionStart = now;
    digitalWrite(LED_PIN, LOW);

    Serial.print("[");
    Serial.print(now);
    Serial.print(" ms] Motion detected (LOW gap ");
    Serial.print(now - lastLowTime);
    Serial.println(" ms)");
  }

  if (pirState == LOW && motionDetected) {
    motionDetected = false;
    motionEnd = now;
    lastLowTime = now;
    digitalWrite(LED_PIN, HIGH);

    Serial.print("[");
    Serial.print(now);
    Serial.print(" ms] Motion ended (HIGH lasted ");
    Serial.print(motionEnd - motionStart);
    Serial.println(" ms)");
  }

  delay(50);
}
