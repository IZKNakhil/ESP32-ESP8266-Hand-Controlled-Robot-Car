# Development Journey

The project was deliberately developed subsystem-by-subsystem rather than assembled all at once.

1. Establish ESP-NOW communication between ESP32 and ESP8266.
2. Validate HC-SR04 distance measurement independently.
3. Validate L298N forward/reverse/stop behavior.
4. Integrate received wireless commands with motor functions.
5. Diagnose four-motor startup problems by reducing the drivetrain to one motor pair.
6. Identify power delivery as the primary issue.
7. Move from the original four-AA prototype supply to the final eight-AA series configuration used in the photographed build.
8. Experiment with PWM; reject it for the final prototype after unreliable startup/buzzing.
9. Add distance averaging and safer command zones.
10. Complete real-world floor testing.

This staged approach made it possible to distinguish software, communication, sensor, drivetrain, and power problems.
