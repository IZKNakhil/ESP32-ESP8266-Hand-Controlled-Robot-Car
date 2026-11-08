# Power Supply and Debugging Notes

## What happened

The original complete robot was tested with four AA cells in series, approximately 6 V nominal with 1.5 V cells. Individual subsystems worked, but the complete four-motor system did not operate reliably under load.

Observed symptoms included motor buzzing, better operation with the wheels off the floor, and successful operation of one motor pair while all four motors struggled.

## Isolation test

One L298N output channel was disconnected so only two motors were driven. Those motors started strongly. This pointed toward a power-delivery problem rather than ESP-NOW or command-decoding software.

## Final prototype configuration

The final photographed prototype uses eight AA cells electrically in series, approximately 12 V nominal with 1.5 V cells. This configuration produced successful operation in the completed build.

## Electrical warning

Eight cells in series increase voltage; they do not simply represent "more current." Never apply ~12 V directly to an ESP8266 3V3 pin. Logic electronics require an appropriate regulated supply path. Measure the real pack voltage and regulator outputs before connecting the microcontroller.

The L298N also introduces voltage loss and heat, and motor startup/stall current can be much higher than free-running current. A future revision should use a properly engineered power architecture sized from measured motor current and the ratings of the exact motors used.
