# Troubleshooting

## Motors buzz but do not start
Check the battery state, voltage under load, terminal connections, motor wiring, and mechanical load. Test one motor pair before all four.

## Motors work with wheels lifted but not on the floor
The drivetrain needs more torque/current under real load. Check supply sag and battery capability before changing software.

## ESP-NOW packets are not received
Verify the ESP8266 station MAC address, peer configuration, matching message structure, board packages, and Serial Monitor output.

## Robot drives in the wrong direction
Motor polarity differs between chassis builds. Swap the two wires for the affected side or invert that channel in software.

## Unstable ultrasonic readings
Check sensor alignment, wiring, common ground, ECHO voltage level shifting, and nearby reflecting surfaces. The final firmware averages multiple valid readings.

## ESP resets when motors start
This strongly suggests a power-distribution or electrical-noise problem. Check supply voltage during startup, grounding, regulators, wiring resistance, and decoupling.
