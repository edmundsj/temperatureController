# TEC Temperature Controller PCB
This PCB is designed to monitor and control the temperature of an object heated or cooled with a thermoelectric cooler (TEC), and is capable of driving up to 8A

## Features
- TEC temperature regulation within 0.1C using PI control
- Max TEC Voltage/current of 3.6V/6A when powered off 5V
- 1% settling time of ~90s 
- Bidirectional temp. control (heating and cooling) 
- 6A max current with 8-bit current monitoring (~25mA accuracy)
- Computer-independent measurement and temperature control using on-board interface
- Can be powered over USB (current limited by driving source)
- Closed-loop control of temperature using MCP9808 remote temperature sensor
- Two 3-digit 7-segment displays for temperature setpoint and measured value
- Knob potentiometer for setting target temperature
- Passive cooling (~4K/W thermal resistance) with 1.5" radial heatsink
- Arduino nano-based

![Populated PCB](./images/temperature_controller_populated_pcb.png)
Fully populated PCB

![Unpopulated PCB](./images/temperature_controller_unpopulated_pcb.png)
Unpopulated, as-fabricated PCB


## Getting Started
Kicad design files for this PCB are located in the ``kicad/`` folder. Gerbers
can be generated directly for fabrication, or you can find the latest gerbers
in the ``gerbers/`` directory. The parts required can be found in ``bom.csv``.
Software can be found in the ``controller_software/`` directory, which can be
copied to your local machine, and uploaded to an Arduino nano via the Arduino
IDE. This system is rated to work at 5V, so make sure the power adapter used is
rated for 5V, and as much current as is required. For the TEC I built this
system around, that is ~6A.

## Issues
### Issues in Version 1
- [FIXED v2] Need VDD, GND connections on header going to MCP9808 board in addition to SDA and SCL.
- [FIXED v2] Need to make sure the ordering and connector matches that of the device PCB.
- [FIXED v2] In the future, a couple of accessible header GND connections would be nice, even just for probing.
- [FIXED v2] Should edit the silkscreen to include the directionality of the Arduino Nano's USB. 
- [FIXED v2] Should swap out MOSFET for a more linear BJT
- [FIXED v2] Swap out MOSFET for transistor with much lower thermal resistance
- [FIXED v2] My choice of resistor is not sufficient, the thing heats up and starts to smoke after a couple seconds at ~5A. 

### Issues in Version 2
- [FIXED v3] R4 is too close to the heatsink, difficult to access. Moved.
- [FIXED v3] Added capacitor for filtering of input drive voltage
- [FIXED v3] Added 2x2 ground header pins for probing
- [FIXED v3] Added relay with drive transistor to allow bidirectional current flow through TEC
- [FIXED v3] Added silkscreen + courtyard + mounting holes for main heatsink
- [FIXED v3] Current sensing is unreliable due to ADC being near rails, added opamp buffer + biasing

### Issues in Version 3
- Standoffs should be as far to the outside to avoid tipping the board when using screw terminals
- Need to add test piont for VDR_F. 
- C4 should be removed. We have no business filtering a voltage going to the base of the BJT.
- Add probe points for communication interface for easier debugging. 
- Add probe points for ground silkscreen
- Decouple VDD of arduino and TEC.

## Acknowledgements
