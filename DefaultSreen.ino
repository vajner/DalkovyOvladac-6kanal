// Dalkovy ovladac k tanku
// Vajner Petr
// Email: vajner@seznam.cz



void printDefaultSreen() {
  //lcd.clear();
  String radek1 = txtRadek1;
  radek1.replace("%batL%", getStringValue(lBateryVal));
  radek1.replace("%batR%", getStringValue(rBateryVal));
  radek1 += getStringValue(idPrijimace);
  lcd.setCursor(0,0);
  lcd.print(radek1);

  String radek2 = "";
  if(spojeno) {
    radek2 = "Spojeni:" + nazevZarizeni;
  } else {
    radek2 = "Spojeni: Chyba  ";
  }
  lcd.setCursor(0,1);
  lcd.print(radek2);
}
