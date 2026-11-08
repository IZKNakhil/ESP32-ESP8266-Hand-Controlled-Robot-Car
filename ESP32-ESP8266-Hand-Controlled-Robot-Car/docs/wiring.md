# Wiring Reference

## ESP32 / HC-SR04
- GPIO33 -> TRIG
- GPIO34 <- ECHO through suitable 5 V to 3.3 V level reduction
- 5V -> VCC
- GND -> GND

## ESP8266 / L298N
- D1 (GPIO5) -> IN1
- D2 (GPIO4) -> IN2
- D5 (GPIO14) -> IN3
- D6 (GPIO12) -> IN4
- GND -> GND
- ENA and ENB jumpers installed in the final full-speed build
