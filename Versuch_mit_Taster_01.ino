#define RED 11
#define GRN 12
#define BLU 13
#define BUTTON_PIN 8  // Beispiel-Pin für den Taster, ändere ihn entsprechend deiner Verkabelung

int mode = 0;  // Variable zur Speicherung des aktuellen Modus (0 = mit Kleidung, 1 = ohne Kleidung)
int lastButtonState = HIGH;  // Variable zur Speicherung des vorherigen Tasterzustands

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GRN, OUTPUT);
  pinMode(BLU, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Pull-up-Widerstand aktivieren

  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  // Wenn der Taster gedrückt wurde (von HIGH auf LOW wechselt)
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Wechsle den Modus
    mode = 1 - mode;  // Toggle-Logik zwischen 0 und 1
    delay(50);  // Kleine Verzögerung zur Entprellung des Tasters
  }

  float sensorValue = analogRead(A0);
  float sensorVoltage = sensorValue / 1024 * 5.0;

  Serial.print("sensor reading = ");
  Serial.print(sensorValue);
  Serial.print("        sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.print(" V        Mode = ");
  Serial.println(mode);

  // Je nach Modus unterschiedliche RGB-LED-Farben anzeigen
  if (mode == 0) {
    // Modus mit Kleidung
    if (sensorVoltage >= 0.01) {
      // Blaue Farbe
      digitalWrite(RED, LOW);
      digitalWrite(GRN, LOW);
      digitalWrite(BLU, HIGH);
    } else {
      // Rote Farbe
      digitalWrite(RED, HIGH);
      digitalWrite(GRN, LOW);
      digitalWrite(BLU, LOW);
    }
  } else {
    // Modus ohne Kleidung
    // Dauerhaft grüne Farbe
    digitalWrite(RED, LOW);
    digitalWrite(GRN, HIGH);
    digitalWrite(BLU, LOW);
  }

  // Weitere Logik und Aktionen entsprechend deinen Anforderungen

  lastButtonState = buttonState;  // Aktuellen Tasterzustand für die nächste Iteration speichern
  delay(1000);
}
