/*
  Water Tank Level Controller
  ---------------------------
  An HC-SR04 ultrasonic sensor on top of the tank measures the
  distance down to the water surface. When the water falls to
  the LOW level the pump relay turns the pump ON; when it rises
  to the HIGH level the pump turns OFF. If the sensor reading
  is invalid the pump stays OFF. Relay is OFF on startup (safe
  default).

  Wiring:
    HC-SR04 TRIG: D9, ECHO: D10, VCC 5V, GND GND
    Pump relay  : D7 (active-LOW relay module)
    Status LED  : D13 (through a 220 ohm resistor to GND)
*/

// ---- Pin definitions ----
const int TRIG_PIN   = 9;   // HC-SR04 trigger
const int ECHO_PIN   = 10;  // HC-SR04 echo
const int RELAY_PIN  = 7;   // Pump relay IN1 (active LOW)
const int STATUS_LED = 13;  // Built-in / status LED

// ---- Tank levels (distance from sensor, in cm) ----
// The sensor looks DOWN, so a LARGER distance = LOWER water.
// Measure your tank and adjust: distance when tank is nearly
// empty (start pump) and when it is nearly full (stop pump).
const int START_DISTANCE_CM = 80;   // Water low  -> pump ON
const int STOP_DISTANCE_CM  = 20;   // Water high -> pump OFF
const int MAX_VALID_CM      = 200;  // Beyond this = bad reading

bool pumpOn = false;

void setPump(bool on) {
  pumpOn = on;
  digitalWrite(RELAY_PIN, on ? LOW : HIGH);  // LOW = relay ON
  digitalWrite(STATUS_LED, on ? HIGH : LOW);
  Serial.println(on ? "Pump ON - filling tank" : "Pump OFF");
}

int readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (duration == 0) return -1;  // No echo: invalid reading
  return (int)(duration * 0.0343 / 2.0);  // Sound speed -> cm
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);

  // Safe defaults: relay OFF, pump OFF on startup.
  digitalWrite(RELAY_PIN, HIGH);  // HIGH = relay OFF (active LOW)
  digitalWrite(STATUS_LED, LOW);

  Serial.begin(9600);
  Serial.println("Water Tank Level Controller ready.");
}

void loop() {
  int distance = readDistanceCm();

  if (distance < 0 || distance > MAX_VALID_CM) {
    // Never run the pump on a reading we cannot trust.
    if (pumpOn) setPump(false);
    Serial.println("Sensor reading invalid - pump held OFF");
    delay(1000);
    return;
  }

  Serial.print("Distance to water: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (!pumpOn && distance >= START_DISTANCE_CM) {
    setPump(true);   // Water is low: start filling
  } else if (pumpOn && distance <= STOP_DISTANCE_CM) {
    setPump(false);  // Tank is full: stop before it overflows
  }

  delay(1000);  // Check once a second
}
