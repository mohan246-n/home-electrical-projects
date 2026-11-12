/*
  Smart Doorbell
  --------------
  A visitor presses the doorbell button and the buzzer plays a
  short two-tone chime while an LED lights up. An optional PIR
  motion sensor gives a single soft beep when someone approaches
  the door, before they even press the button.
  Buzzer and LED are OFF on startup (safe default).

  Wiring:
    Button    : D2 (other side to GND, uses internal pull-up)
    PIR OUT   : D3 (optional, VCC 5V, GND GND)
    Buzzer    : D8 (active buzzer, + to D8, - to GND)
    LED       : D13 (through a 220 ohm resistor to GND)
*/

// ---- Pin definitions ----
const int BUTTON_PIN = 2;   // Doorbell push button (to GND)
const int PIR_PIN    = 3;   // Optional PIR motion sensor
const int BUZZER_PIN = 8;   // Buzzer
const int LED_PIN    = 13;  // Status / chime LED

// ---- Timing (ms) ----
const unsigned long CHIME_TONE_MS  = 350;   // Length of each chime tone
const unsigned long PIR_COOLDOWN_MS = 30000; // Min. gap between PIR beeps
const unsigned long DEBOUNCE_MS    = 50;

bool lastButtonState = HIGH;
unsigned long lastPirBeep = 0;
bool pirReady = false;

void chime() {
  // Two-step chime: on, short pause, on again, using the active
  // buzzer at two different pulse rates to suggest two tones.
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(CHIME_TONE_MS);
  digitalWrite(BUZZER_PIN, LOW);
  delay(120);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(CHIME_TONE_MS);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  Serial.println("Ding-dong! Visitor at the door.");
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // Safe defaults: buzzer and LED OFF on startup.
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);
  Serial.println("Smart Doorbell ready. PIR warming up (30-60 s)...");
}

void loop() {
  // Doorbell button: pressed = LOW (pull-up wiring).
  bool buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(DEBOUNCE_MS);  // Debounce
    if (digitalRead(BUTTON_PIN) == LOW) {
      chime();
      // Wait for release so one press = one chime.
      while (digitalRead(BUTTON_PIN) == LOW) {
        delay(10);
      }
    }
  }
  lastButtonState = digitalRead(BUTTON_PIN);

  // Optional PIR: one soft beep when someone approaches.
  if (!pirReady && millis() > 60000UL) {
    pirReady = true;  // PIR output is unreliable during warm-up
    Serial.println("PIR ready.");
  }
  if (pirReady && digitalRead(PIR_PIN) == HIGH &&
      millis() - lastPirBeep > PIR_COOLDOWN_MS) {
    lastPirBeep = millis();
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Motion near the door.");
  }

  delay(10);
}
