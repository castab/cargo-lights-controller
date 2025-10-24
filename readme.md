# Ford Cargo Bed Light Controller

A custom ATtiny85-based controller for aftermarket cargo bed lights, designed to provide a factory-style look and feel for Ford trucks without built-in cargo light support.

## Overview

This project adds intelligent control to cargo bed lights using an ATtiny85 microcontroller. It features smooth fade effects, button control, and automatic timeout functionality to prevent battery drain.

## Features

- **Smooth Fade Effects**: Professional-looking fade-in and fade-out transitions
- **Button Toggle Control**: Simple on/off control via a single button
- **Auto-Timeout**: Automatically turns off lights after 10 minutes to preserve battery life
- **Status LED**: Visual indicator mirroring the cargo light state
- **Debounced Input**: Reliable button operation without false triggers

## Hardware Requirements

- ATtiny85 microcontroller
- MOSFET (for controlling high-current LED strips)
- Push button switch
- Status LED (optional, for visual feedback)
- Resistors as needed for LED and pull-up/pull-down configurations
- Cargo bed LED strips/lights

## Pin Configuration

| Pin | Function | Description |
|-----|----------|-------------|
| 0 | Status LED | Small indicator LED showing system state |
| 1 | Button Input | Push button for on/off control (active low with internal pull-up) |
| 2 | MOSFET Gate | PWM output to control cargo lights via MOSFET |

## Wiring Diagram

```
ATtiny85
   |
   ├─ Pin 0 ──[Resistor]── Status LED ── GND
   |
   ├─ Pin 1 ── Button ── GND
   |
   └─ Pin 2 ── MOSFET Gate
                  |
              MOSFET Drain ── LED Strip ── 12V+
                  |
              MOSFET Source ── GND
```

## Operation

1. **Turning On**: Press the button once. Lights fade on over approximately 250ms
2. **Turning Off**: Press the button again. Lights fade off smoothly
3. **Auto-Timeout**: If left on, lights automatically fade off after 10 minutes

## Configuration

You can adjust these parameters in the code to customize behavior:

```cpp
const int fadeDelay = 5;              // Speed of fade effect (lower = faster)
const int fadeSteps = 50;             // Smoothness of fade (higher = smoother)
const unsigned long timeoutDuration = 600000;  // Auto-off time in milliseconds
const unsigned long debounceDelay = 50;        // Button debounce time
```

## Programming the ATtiny85

1. Install the ATtiny board support in Arduino IDE
2. Select **Tools > Board > ATtiny25/45/85**
3. Select **Tools > Processor > ATtiny85**
4. Select **Tools > Clock > Internal 8 MHz**
5. Connect your programmer (USBtinyISP, Arduino as ISP, etc.)
6. Upload the sketch

## Installation in Ford F150

1. Mount the ATtiny85 circuit in a weatherproof enclosure
2. Connect to cargo bed lights
3. Run button wire to desired location (recommend near bed access or tailgate)
4. Connect to vehicle 12V+ (consider using a fused connection to accessory power)
5. Ground to chassis

**Note**: Ensure all connections are properly insulated and sealed against moisture.

## Power Consumption

- **Active (lights on)**: Depends on connected LED strip current
- **Standby**: <1mA (ATtiny85 sleep mode not currently implemented)

## Future Enhancements

Potential improvements for future versions:
- Sleep mode for even lower standby power consumption
- Integration with door switches for automatic activation
- Adjustable brightness levels
- Memory to recall last brightness setting

## Safety Notes

⚠️ **Important Safety Information**:
- Use appropriate gauge wire for LED strip current requirements
- Install inline fuse for fire safety
- Ensure MOSFET is rated for the current draw to power the lights
- Properly heat-sink MOSFET if necessary
- Keep all electronics away from moisture

## License

This project is open source. Feel free to modify and adapt for your own use.

## Acknowledgments

Designed for Ford truck owners who want factory-quality cargo lighting control without factory pricing but with factory-like (or better) function.

---

**Questions or Issues?** Feel free to open an issue or submit a pull request with improvements!