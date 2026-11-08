# ESP-NOW Communication Test

Before connecting the motors, verify the wireless link independently.

1. Put both boards in station mode.
2. Print/read the ESP8266 station MAC address.
3. Add that MAC as the ESP32 peer.
4. Send a small structure containing a command and test distance.
5. Confirm reception at 115200 baud on the ESP8266 Serial Monitor.

The final sketches use the same message structure, so successful communication at this stage removes an entire class of problems before motor integration.
