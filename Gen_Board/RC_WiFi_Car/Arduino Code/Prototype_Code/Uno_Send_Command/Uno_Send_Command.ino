#define mySerial Serial

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }

  mySerial.begin(115200);
}

void loop() { // run over and over
  if (mySerial.available()) {
    String command = mySerial.readStringUntil('\n');
    Serial.println(command);
  }
}
