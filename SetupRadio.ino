void setupRadio() {
  Serial.println("Icializace radia .....");

  radio.begin();
  radio.setChannel(NRFchannel[chPointer]);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.enableAckPayload();
  radio.setRetries(5,5);
  radio.openWritingPipe(addresses[0]);

  Serial.println("Icializace radia provedena.");

}
