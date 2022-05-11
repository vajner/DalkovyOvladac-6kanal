void setupRadio() {
  Serial.println("Icializace radia .....");

  radio.begin();
  radio.setChannel(NRFchannel[chPointer]);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.enableAckPayload();
  radio.setRetries(5,5);
  //radio.openWritingPipe(addresses[0]);
  //radio.openWritingPipe(addressa);


  String adresa = getAdresaKanalu();
  byte adresaKanalu[6] = "";
  Serial.println(adresa);
  adresa.getBytes(adresaKanalu, 6);
  radio.openWritingPipe(adresaKanalu);

  Serial.println("Icializace radia provedena.");

}


String getAdresaKanalu() {
  String klic = getSSIDRadia();
  String cisloStanice = String(getIdPrijimace());

  if(cisloStanice.length() == 1) {
    klic = klic.substring(0, 4) + cisloStanice;
  } else {
    klic = klic.substring(0, 3) + cisloStanice;
  }
  return klic;
}
