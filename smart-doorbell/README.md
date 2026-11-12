# Smart Doorbell

A doorbell that plays a two-step buzzer chime and lights an LED
when a visitor presses the button, with an optional PIR motion
sensor that gives a soft beep when someone approaches the door.

## How it works

The button is wired between a digital pin and ground, using the
Arduino's internal pull-up, so a press reads LOW. On a press
(with debouncing) the Arduino sounds the active buzzer in a
ding-dong pattern and lights the LED, then waits for the button
to be released so one press gives one chime. The optional PIR
senses a person approaching and beeps once briefly; a 30-second
cooldown stops repeated beeps while the person is standing at
the door, and the PIR is ignored for its first 60 seconds while
it warms up.

## Components

| Component | Value / spec | Qty |
|-----------|--------------|-----|
| Arduino Uno | — | 1 |
| Push button | momentary, for the door | 1 |
| Buzzer | 5 V active buzzer | 1 |
| PIR motion sensor | HC-SR501 (optional) | 1 |
| LED | 5 mm | 1 |
| Resistor | 220 Ω (LED) | 1 |
| Breadboard, jumper wires | — | — |

## Circuit diagram (text)

```
Button ── Arduino D2 and GND (no resistor needed, uses
          the internal pull-up; pressed = LOW)

PIR VCC ── Arduino 5V      (optional)
PIR GND ── Arduino GND
PIR OUT ── Arduino D3

Arduino D8 ── Buzzer + (buzzer - to GND)
Arduino D13 ── 220Ω ── LED ── GND
```

The buzzer and LED are OFF on startup.

## Wiring steps

1. Connect the button between D2 and GND.
2. Connect the buzzer: + → D8, − → GND.
3. Connect the LED: D13 → 220 Ω → LED anode, LED cathode → GND.
4. Optional PIR: VCC → 5 V, GND → GND, OUT → D3. Set its
   sensitivity and delay pots to the shortest delay to start.
5. Upload `smart-doorbell.ino`, then open the Serial Monitor
   (9600 baud) to see doorbell and motion messages.
6. Press the button — you should hear the two-step chime.

## Calibration

This project needs almost no calibration. If the PIR beeps
when nobody is there, lower its sensitivity pot and keep it
away from direct sunlight and hot air vents. If one button
press gives two chimes, increase `DEBOUNCE_MS` (default 50).
To stop PIR beeps altogether, leave the PIR unconnected — the
button chime works on its own. Adjust `CHIME_TONE_MS` for a
longer or shorter ring.

## Safety notes

- This build is low-voltage DC only — keep the door wiring on
  the Arduino side, and never connect it to a mains-powered
  doorbell transformer circuit.
- Buzzer and LED are OFF on startup, so a reset never leaves
  the buzzer sounding.
- If you run wires from the door to the Arduino, use insulated
  cable and keep the run away from mains wiring.
- A doorbell is a convenience device — it does not replace a
  door lock or any security system.
