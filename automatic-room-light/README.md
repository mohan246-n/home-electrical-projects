# Automatic Room Light

A room light that turns itself on only when it is needed:
someone is in the room AND it is dark. It turns off again a
minute after the last movement, so it never wastes power on
an empty or sunlit room.

## How it works

An LDR measures how dark the room is, and a PIR sensor detects
movement. The Arduino reads both: if the PIR sees motion and
the LDR reading is below the dark threshold, the relay turns
the light on and starts a timer. Every new movement restarts
the timer. When no motion has been seen for the full timeout
the light goes off. Because both conditions are required, the
light stays off in daylight even in a busy room. The PIR is
ignored for its first 30 seconds, while it settles.

## Components

| Component | Value / spec | Qty |
|-----------|--------------|-----|
| Arduino Uno | — | 1 |
| PIR motion sensor | HC-SR501 | 1 |
| LDR | e.g. GL5528 | 1 |
| Resistor | 10 kΩ (LDR divider) | 1 |
| Relay module | 5 V, 1-channel, opto-isolated | 1 |
| Lamp | 12 V DC LED (safe option) or 230 V AC lamp via relay | 1 |
| Resistor | 220 Ω (status LED) | 1 |
| LED | 5 mm, status | 1 |
| Breadboard, jumper wires | — | — |

## Circuit diagram (text)

```
5V ── LDR ──┬── A0 (Arduino)
            │
            └── 10k resistor ── GND

PIR VCC ── Arduino 5V
PIR GND ── Arduino GND
PIR OUT ── Arduino D3

Arduino D7 ── Relay IN1
Relay COM ─── Lamp ─── Power (12 V DC, or AC live via relay)
Relay NO ──── Power return / AC neutral side

Arduino D13 ── 220Ω ── Status LED ── GND
Arduino 5V/GND ── Relay VCC / GND
```

Relay logic: the code uses an **active-LOW** relay module (LOW =
relay ON). The relay is OFF on startup.

## Wiring steps

1. Build the LDR divider: 5 V → LDR → A0 node → 10 kΩ → GND.
   Put the LDR where it sees room light, not in the lamp's
   direct beam, or the light will switch itself off and on.
2. Connect the PIR: VCC → 5 V, GND → GND, OUT → D3, and point
   it at the part of the room people move through.
3. Connect the relay module: VCC → 5 V, GND → GND, IN1 → D7.
4. Connect the lamp to the relay's COM and NO terminals.
   **For a 230 V AC lamp, get a qualified electrician to wire
   the AC side. For testing, use a 12 V DC LED lamp.**
5. Connect the status LED: D13 → 220 Ω → LED anode, cathode → GND.
6. Upload `automatic-room-light.ino` and open the Serial
   Monitor (9600 baud). Wait 30 s for the PIR to settle.

## Calibration

Watch the LDR value in the Serial Monitor with the room lights
on and off. Set `DARK_THRESHOLD` (default 400) between the two
readings. Change `OFF_TIMEOUT_MS` (default 60000 = 1 minute)
for a longer or shorter stay-on time — a bathroom may want 2–3
minutes, a hallway 30 seconds. Use the PIR's own pots for
sensitivity and its minimum hardware delay.

## Safety notes

- Relays switch the lamp, not the Arduino. Never let mains
  wiring touch the Arduino or the breadboard.
- Relay is OFF on startup, so the lamp stays off if the
  Arduino resets.
- If using a 230 V AC lamp, keep the relay module enclosed
  and unplug it before touching any AC wiring.
- Do not use this as the only light control on stairs or in
  other places where a sudden light-off could cause a fall.
