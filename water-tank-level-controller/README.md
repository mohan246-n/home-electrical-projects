# Water Tank Level Controller

An automatic pump controller for an overhead water tank: it
starts the pump when the water level falls low and stops it
when the tank is full, with no manual switching and no
overflow.

## How it works

An HC-SR04 ultrasonic sensor mounted at the top of the tank,
pointing down, measures the distance to the water surface.
A larger distance means a lower water level. When the distance
reaches the low-level value the Arduino energises the pump
relay; when the water rises to the high-level distance it
turns the pump off. The two levels are far apart, so the pump
does not start and stop repeatedly. If the sensor gives no
echo or an impossible reading, the pump is held OFF — the
controller never runs the pump on a reading it cannot trust.

## Components

| Component | Value / spec | Qty |
|-----------|--------------|-----|
| Arduino Uno | — | 1 |
| Ultrasonic sensor | HC-SR04 | 1 |
| Relay module | 5 V, 1-channel, opto-isolated (rated for the pump) | 1 |
| Water pump | as per tank / supply, switched by the relay | 1 |
| Resistor | 220 Ω (status LED) | 1 |
| LED | 5 mm, status (pump running) | 1 |
| Breadboard, jumper wires | — | — |

## Circuit diagram (text)

```
HC-SR04 VCC ── Arduino 5V
HC-SR04 GND ── Arduino GND
HC-SR04 TRIG ─ Arduino D9
HC-SR04 ECHO ─ Arduino D10

Arduino D7 ── Relay IN1
Relay COM ─── Pump ─── Power supply
Relay NO ──── Power return
             (pump runs only when relay is energised)

Arduino D13 ── 220Ω ── Status LED ── GND
Arduino 5V/GND ── Relay VCC / GND
```

Relay logic: the code uses an **active-LOW** relay module (LOW =
relay ON). The relay is OFF on startup.

## Wiring steps

1. Mount the HC-SR04 at the top inside of the tank lid,
   pointing straight down at the water, clear of the walls
   and the inlet pipe. Keep its face dry.
2. Connect the sensor: VCC → 5 V, GND → GND, TRIG → D9,
   ECHO → D10.
3. Connect the relay module: VCC → 5 V, GND → GND, IN1 → D7.
4. Connect the pump through the relay's COM and NO terminals.
   **If the pump is mains-powered, get a qualified electrician
   to wire the AC side. For testing, use a small 12 V DC pump.**
5. Connect the status LED: D13 → 220 Ω → LED anode, cathode → GND.
6. Upload `water-tank-level-controller.ino` and open the
   Serial Monitor (9600 baud) to see the distance readings.

## Calibration

With the tank empty and full, note the Serial distance in cm
for each state. Set `START_DISTANCE_CM` (default 80) a little
below the empty reading, so the pump starts before the tank
runs dry, and `STOP_DISTANCE_CM` (default 20) a little above
the full reading, so it stops before overflow. Keep a good
gap between the two values. Long sensor wires can make HC-SR04
readings noisy — keep them as short as practical.

## Safety notes

- The relay is OFF on startup, and on any invalid sensor
  reading, so a reset or a failed sensor cannot leave the
  pump running and overflow the tank.
- Water and mains electricity are a dangerous mix. Keep the
  Arduino and relay dry, enclose the relay, and have a
  qualified electrician wire any mains pump.
- Use a relay (and fuse) rated for your pump's current —
  pump motors draw a high starting current.
- Fit a manual override / isolator switch so the pump can
  be turned off for maintenance.
