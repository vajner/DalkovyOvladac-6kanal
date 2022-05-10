void odesliAPrijmiData() {

  static boolean previousTransmissionState;
  static float previousRxVcc;
  static float previousRxVbatt;
  static boolean previousBattState;
  static unsigned long previousSuccessfulTransmission;

  //radio.stopListening();

  // Send radio data and check if transmission was successful
  if (radio.write(&data, sizeof(struct Data_Command)) ) {
    if (radio.isAckPayloadAvailable()) {
      radio.read(&dataInfo, sizeof(struct Data_Info)); // read the payload, if available
      previousSuccessfulTransmission = millis();
    }
  }
  
  // Switch channel for next transmission
  chPointer ++;
  if (chPointer >= sizeof((*NRFchannel) / sizeof(byte))) chPointer = 0;
  radio.setChannel(NRFchannel[chPointer]);

  // if the transmission was not confirmed (from the receiver) after > 1s...
  if (millis() - previousSuccessfulTransmission > 1000) {
    //greenLED.on();
    transmissionState = false;
    memset(&dataInfo, 0, sizeof(dataInfo)); // clear the payload array, if transmission error
    spojeno = false;
      
    #ifdef DEBUG
      Serial.println("Chyba pri odeslani dat. Zkontrolujte prijimac!");
    #endif
  } else {
    //greenLED.flash(30, 100, 0, 0); //30, 100
    transmissionState = true;
    spojeno = true;
    if(nazevZarizeni = "") {
    nazevZarizeni = dataInfo.nazevZarizeni;
    rBateryVal = dataInfo.urovenBaterie;
    if(nazevZarizeni.length() < 8) {
      int pocetMezer = 8-nazevZarizeni.length();
      for(int i=1; i < pocetMezer; i++){
        nazevZarizeni += " ";
      }
    }
  }
  #ifdef DEBUG
        //Serial.println("Data successfully transmitted");
  #endif
}

/*if (!displayLocked) { // Only allow display refresh, if not locked ----
  // refresh transmission state on the display, if changed
  if (transmissionState != previousTransmissionState) {
    previousTransmissionState = transmissionState;
    drawDisplay();
  }

  // refresh Rx Vcc on the display, if changed more than +/- 0.05V
  if (payload.vcc - 0.05 >= previousRxVcc || payload.vcc + 0.05 <= previousRxVcc) {
    previousRxVcc = payload.vcc;
    drawDisplay();
  }

  // refresh Rx V Batt on the display, if changed more than +/- 0.3V
  if (payload.batteryVoltage - 0.3 >= previousRxVbatt || payload.batteryVoltage + 0.3 <= previousRxVbatt) {
    previousRxVbatt = payload.batteryVoltage;
    drawDisplay();
  }

  // refresh battery state on the display, if changed
  if (payload.batteryOk != previousBattState) {
    previousBattState = payload.batteryOk;
    drawDisplay();
  }
}*/

  #ifdef DEBUG_JOY
      Serial.print(data.lJoyX);
      Serial.print("\t");
      Serial.print(data.lJoyY);
      Serial.print("\t");
      Serial.print(data.rJoyX);
      Serial.print("\t");
      Serial.print(data.rJoyY);
      Serial.print("\t");
      Serial.print(dataInfo.nazevZarizeni);
      Serial.print("\t");
      
      Serial.println(F_CPU / 1000000, DEC);
  #endif
}
