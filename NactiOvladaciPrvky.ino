void nactiOvladaciPrvky() {
  idPrijimace = getIdPrijimace();
  data.lJoyX=getValLX() + getKorekceLx();
  data.lJoyY=getValLY() + getKorekceLy();
  data.rJoyX=getValRX() + getKorekceRx();
  data.rJoyY=getValRY() + getKorekceRy();
  data.lJoyBtn=getValLjBtn();
  data.rJoyBtn=getValRjBtn();
  
  
  valMenuSw = getValBtnMenu();
}

int getValLX(){
  return map(analogRead(analogPinLX), 0, 1023, 0, 180);
}

int getValLY(){
  return map(analogRead(analogPinLY), 0, 1023, 0, 180);
}

int getValRX() {
  return map(analogRead(analogPinRX), 0, 1023, 0, 180);
}

int getValRY(){
  return map(analogRead(analogPinRY), 0, 1023, 0, 180);
}


int getValLjBtn(){
  return digitalRead(digitalJoyLSwitch);
}

int getValRjBtn(){
  return digitalRead(digitalJoyRSwitch);
}

int getValBtnMenu(){
  return digitalRead(digitalMenuSw);
}
