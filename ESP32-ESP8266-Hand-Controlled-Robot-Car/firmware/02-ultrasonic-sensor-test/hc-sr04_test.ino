#define TRIG_PIN 33
#define ECHO_PIN 34

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(3);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) Serial.println("No echo");
  else {
    float cm = duration * 0.0343 / 2.0;
    Serial.print(cm, 1); Serial.println(" cm");
  }
  delay(250);
}
