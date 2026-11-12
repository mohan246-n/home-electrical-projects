/*
  Automatic Room Light
  --------------------
  A PIR motion sensor and an LDR work together: the light only
  turns on when someone is in the room AND it is dark enough to
  need it. When motion stops, the light stays on for a set
  timeout, then turns off. Relay is OFF on startup (safe
  default).

  Wiring:
    LDR divider: 5V - LDR - A0 - 10k resistor - GND
    PIR OUT    : D3 (VCC 5V, GND GND)
    Relay IN1  : D7 (active-LOW relay module)
    Status LED : D13 (through a 220 ohm resistor to GND)
*/

// ---- Pin definitions ----
const int LDR_PIN    = A0;  // LDR voltage divider
const int PIR_PIN    = 3;   // PIR motion sensor output
const int RELAY_PIN  = 7;   // Relay module IN1 (active LOW)
const int STATUS_LED = 13;  // Built-in / status LED

// ---- Thresholds and timing ----
// Room is "dark" when the LDR reading falls below DARK_THRESHOLD.
const int DARK_THRESHOLD = 400;
const unsigned long OFF_TIMEOUT_MS = 60000;  // Light stays on 1 min after last motion
const unsigned long PIR_WARMUP_MS  = 30000;  // PIR settle time after power-on

bool lightOn = false;
unsigned long lastMotion = 0;

void setLight(bool on) {
  lightOn = on;
  digitalWrite(RELAY_PIN, on ? LOW : HIGH);  // LOW = relay ON
  digitalWrite(STATUS_LED, on ? HIGH : LOW);
  Serial.println(on ? "Room light ON" : "Room light OFF");
}

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);

  // Safe defaults: relay OFF, lamp OFF on startup.
  digitalWrite(RELAY_PIN, HIGH);  // HIGH = relay OFF (active LOW)
  digitalWrite(STATUS_LED, LOW);

  Serial.begin(9600);
  Serial.println("Automatic Room Light ready. PIR warming up (30 s)...");
}

void loop() {
  // Ignore the PIR while it settles after power-on.
  if (millis() < PIR_WARMUP_MS) {
    delay(200);
    return;
  }

  int ldrValue = analogRead(LDR_PIN);
  bool dark = ldrValue < DARK_THRESHOLD;
  bool motion = digitalRead(PIR_PIN) == HIGH;

  if (motion) {
    lastMotion = millis();
    if (dark && !lightOn) {
      setLight(true);
    }
  }

  // Turn off once nobody has moved for the full timeout.
  if (lightOn && millis() - lastMotion > OFF_TIMEOUT_MS) {
    setLight(false);
  }

  Serial.print("LDR: ");
  Serial.print(ldrValue);
  Serial.print("  Motion: ");
  Serial.print(motion ? "yes" : "no");
  Serial.print("  Light: ");
  Serial.println(lightOn ? "ON" : "OFF");

  delay(500);  // Check twice a second
}
