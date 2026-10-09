#include "config.h"

void setup() {
  Serial.begin(115200);

  //USB serial port to load first, we wait
  while (!Serial && millis() < 30000) { //Solange die Serielle Verbindung nicht abgeschlossen ist und wir unter 3sec warten
    delay(10); 
  }

  Serial.println("Device booting...");
  // TODO: print relevant info: like the PSRAM size or other functions on the `ESP` object.
}

void loop() {
  // Later, this is where the three steps go: check the button, react to changes, do the current state’s work.
}
