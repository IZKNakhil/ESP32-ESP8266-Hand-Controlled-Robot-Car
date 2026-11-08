#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#define TRIG_PIN 33
#define ECHO_PIN 34

// IMPORTANT: Replace this with YOUR ESP8266 station MAC address.
uint8_t empfaengerMAC[] = {0xFC, 0xEA, 0xBC, 0x58, 0xAC, 0x7C};

typedef struct {
  char befehl[32];
  float abstand;
} Nachricht;

Nachricht senden;

float messeAbstand() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(3);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long dauer = pulseIn(ECHO_PIN, HIGH, 30000);
  if (dauer == 0) return -1;

  float abstand = dauer * 0.0343 / 2.0;
  if (abstand < 2 || abstand > 200) return -1;

  return abstand;
}

float messeAbstandGlaettet() {
  const int ANZAHL = 5;
  float summe = 0;
  int gueltigeMessungen = 0;

  for (int i = 0; i < ANZAHL; i++) {
    float wert = messeAbstand();
    if (wert > 0) {
      summe += wert;
      gueltigeMessungen++;
    }
    delay(30);
  }

  if (gueltigeMessungen < 3) return -1;
  return summe / gueltigeMessungen;
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("FEHLER: ESP-NOW Start fehlgeschlagen!");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, empfaengerMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("FEHLER: ESP8266 konnte nicht hinzugefuegt werden!");
    return;
  }

  Serial.println("ESP-NOW bereit!");
}

void loop() {
  senden.abstand = messeAbstandGlaettet();

  if (senden.abstand < 0) strcpy(senden.befehl, "STOP");
  else if (senden.abstand < 12) strcpy(senden.befehl, "RUECKWAERTS");
  else if (senden.abstand < 20) strcpy(senden.befehl, "STOP");
  else if (senden.abstand < 35) strcpy(senden.befehl, "VORWAERTS");
  else strcpy(senden.befehl, "STOP");

  esp_err_t result = esp_now_send(empfaengerMAC, (uint8_t *)&senden, sizeof(senden));

  Serial.print("Abstand: ");
  if (senden.abstand < 0) Serial.print("KEIN ECHO");
  else {
    Serial.print(senden.abstand, 1);
    Serial.print(" cm");
  }

  Serial.print(" | Befehl: ");
  Serial.print(senden.befehl);
  Serial.println(result == ESP_OK ? " | gesendet" : " | SENDEFEHLER");

  delay(100);
}
