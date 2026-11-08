#include <ESP8266WiFi.h>
#include <espnow.h>

#define IN1 D1
#define IN2 D2
#define IN3 D5
#define IN4 D6

typedef struct {
  char befehl[32];
  float abstand;
} Nachricht;

Nachricht empfangen;

void motorStop() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  Serial.println("MOTOREN: STOP");
}

void motorVorwaerts() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  Serial.println("MOTOREN: VORWAERTS - VOLLE LEISTUNG");
}

void motorRueckwaerts() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  Serial.println("MOTOREN: RUECKWAERTS - VOLLE LEISTUNG");
}

void onDataRecv(uint8_t *mac, uint8_t *data, uint8_t len) {
  if (len != sizeof(Nachricht)) {
    Serial.println("FEHLER: Falsche Nachrichtengroesse!");
    motorStop();
    return;
  }

  memcpy(&empfangen, data, sizeof(empfangen));
  empfangen.befehl[31] = '\0';

  Serial.print("Empfangen: ");
  Serial.print(empfangen.befehl);
  Serial.print(" | Abstand: ");
  Serial.print(empfangen.abstand, 1);
  Serial.println(" cm");

  if (strcmp(empfangen.befehl, "VORWAERTS") == 0) motorVorwaerts();
  else if (strcmp(empfangen.befehl, "RUECKWAERTS") == 0) motorRueckwaerts();
  else motorStop();
}

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  motorStop();

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("FEHLER: ESP-NOW konnte nicht gestartet werden!");
    motorStop();
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(onDataRecv);

  Serial.println("ESP-NOW bereit. Warte auf ESP32...");
}

void loop() {}
