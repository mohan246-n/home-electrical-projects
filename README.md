# Home Electrical Projects

A collection of 5 practical, beginner-friendly Arduino-based electrical
projects for the home, built for learning, home use, and portfolio /
college work. Each project lives in its own folder with its own README,
working Arduino code (`.ino`), and a text circuit diagram.

## Projects

| # | Project | What it does |
|---|---------|--------------|
| 1 | [automatic-street-light](automatic-street-light/) | Street light turns on automatically at dusk and off at dawn, using an LDR sensor and a relay. |
| 2 | [home-automation-relay](home-automation-relay/) | 4-channel relay board controls lights and a fan, with a manual override switch for each channel. |
| 3 | [smart-doorbell](smart-doorbell/) | Push button rings a two-tone buzzer chime with an LED, and an optional PIR beeps when someone approaches the door. |
| 4 | [automatic-room-light](automatic-room-light/) | Room light turns on only when someone is present and it is dark, and off again after a timeout with no motion. |
| 5 | [water-tank-level-controller](water-tank-level-controller/) | Ultrasonic sensor watches the tank level and runs the pump between low and high levels, with no overflow. |

## How to use

1. Pick a project folder and read its `README.md` first — it lists the
   exact components, wiring, and safety notes for that project.
2. Open the `.ino` file in the Arduino IDE (or Arduino CLI / VS Code
   with the Arduino extension).
3. Select your board (Arduino Uno unless the project says ESP32) and
   the correct port, then upload.
4. Wire the circuit exactly as described in the project README.
   **Do not power the circuit until you have double-checked the wiring.**
5. Open the Serial Monitor at 9600 baud (where the project uses it)
   to see readings and status messages.

## Common components and tools

- Arduino Uno (projects 1, 3, 4, 5) / ESP32 DevKit (project 2)
- Breadboard, jumper wires, USB cable
- Resistors: 10 kΩ, 1 kΩ, 220 Ω (see each project for exact values)
- 5 V relay module(s), LEDs, buzzer, push buttons / switches
- LDR, PIR motion sensor (HC-SR501), HC-SR04 ultrasonic sensor
- Multimeter, wire stripper, screwdriver, soldering iron (optional)

## ⚠️ Safety warnings — read before building anything

- **Mains voltage (230 V AC in India / 110–240 V AC elsewhere) can kill.**
  Projects in this repo switch mains loads only through an enclosed
  relay module, and the low-voltage Arduino side must be kept fully
  separate from the mains side. If you are not confident working with
  mains wiring, get a qualified electrician to wire the AC side, or
  build the project with a low-voltage DC load (e.g. a 12 V lamp)
  instead.
- Never touch the relay module's screw terminals or mains wires while
  the circuit is powered. Always unplug / switch off at the wall
  before changing wiring.
- Check every connection with a multimeter before first power-up.
- Keep water away from electronics: for the water tank project, keep
  the Arduino and relay dry and enclose them outside the tank.
- A pump relay and fuse must be rated for the pump's current — pump
  motors draw a high starting current.
- PIR and ultrasonic sensors are convenience sensors, not safety
  devices. Do not rely on them as your only control for stairs
  lighting or for a pump with no manual isolator switch.

## Repo layout

```
home-electrical-projects/
├── README.md
├── LICENSE
├── .gitignore
├── automatic-street-light/
├── home-automation-relay/
├── smart-doorbell/
├── automatic-room-light/
└── water-tank-level-controller/
```

## Pushing to GitHub

```bash
git init
git add .
git commit -m "Add 5 Arduino home electrical projects"
git branch -M main
git remote add origin https://github.com/<your-username>/home-electrical-projects.git
git push -u origin main
```

## License

MIT — see [LICENSE](LICENSE).
