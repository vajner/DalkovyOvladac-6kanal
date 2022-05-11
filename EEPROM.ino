// Dalkovy ovladac k tanku
// Vajner Petr
// Email: vajner@seznam.cz
//      Nazev         Pozice v pameti
//--------------------------------------
#define ID_PRIJIMACE    0
#define SIFROVACI_KLIC  1 //-- "VaPet"
#define KOREKCE_LX      11
#define KOREKCE_LY      12
#define KOREKCE_RX      13
#define KOREKCE_RY      14


//#define NAZEV_RADIA "VaPet"

byte getIdPrijimace() {
  byte value = EEPROM.read(ID_PRIJIMACE);
  if (isnan(value)) {
    value = 1;
    setIdPrijimace(value);
  }
  return value;
}

void setIdPrijimace(byte idPrijimace) {
  EEPROM.write(ID_PRIJIMACE, idPrijimace);
}

String getSSIDRadia() {
  String nazev = TextFromEEPROM(SIFROVACI_KLIC, 10);
  if(nazev.length() == 0) {
    nazev = "Nezadano";
    TextToEEPROM(SIFROVACI_KLIC, 10, nazev);
  }
  return nazev;
}

void setSSIDRadia(String nazev) {
  TextToEEPROM(SIFROVACI_KLIC, 10, nazev);
}

int getKorekceLx() {
  int value = EEPROM.read(KOREKCE_LX);
  if (isnan(value)) {
    value = 0;
    setKorekceLx(value);
  }
  if(value > 90) {
    value = 0;
    setKorekceLx(value);
  }
  return value;
}

void setKorekceLx(int korekceLx) {
  EEPROM.write(KOREKCE_LX, korekceLx);
}


int getKorekceLy() {
  int value = EEPROM.read(KOREKCE_LY);
  if (isnan(value)) {
    value = 0;
    setKorekceLy(value);
  }
  if(value > 90) {
    value = 0;
    setKorekceLy(value);
  }
  return value;
}

void setKorekceLy(int korekceLy) {
  EEPROM.write(KOREKCE_LY, korekceLy);
}

int getKorekceRx() {
  int value = EEPROM.read(KOREKCE_RX);
  if (isnan(value)) {
    value = 0;
    setKorekceRx(value);
  }
  if(value > 90) {
    value = 0;
    setKorekceRx(value);
  }
  return value;
}

void setKorekceRx(int korekceRx) {
  EEPROM.write(KOREKCE_RX, korekceRx);
}

int getKorekceRy() {
  int value = EEPROM.read(KOREKCE_RY);
  if (isnan(value)) {
    value = 0;
    setKorekceRy(value);
  }
  if(value > 90) {
    value = 0;
    setKorekceRy(value);
  }
  return value;
}

void setKorekceRy(int korekceRy) {
  EEPROM.write(KOREKCE_RY, korekceRy);
}

void TextToEEPROM(int adresa, int maxVelikost, String text) {
  for (int i = 0;i < text.length();i++) {
    EEPROM.write(adresa + i, (byte)text[i]);
  }
  for (int i = text.length();i < maxVelikost;i++) {
    EEPROM.write(adresa + i, ' ');
  }  
}

String TextFromEEPROM(int adresa, int maxVelikost) {
  String TextFromEEPROM = "";
  for (int i = 0;i < maxVelikost;i++) {
    char znak = (char)EEPROM.read(adresa + i);
    if (isAlphaNumeric(znak) or znak == '-') {
      TextFromEEPROM = TextFromEEPROM + String(znak);  
    } else {
      //Serial.print("nahrazujeme znak:");
      //Serial.println(znak);
      TextFromEEPROM = TextFromEEPROM + " ";  
    }
    //Serial.println(TextFromEEPROM);
  }
  while (TextFromEEPROM[TextFromEEPROM.length() - 1] == ' ') {  
    TextFromEEPROM = TextFromEEPROM.substring(0,TextFromEEPROM.length() - 1);
  }
  return  TextFromEEPROM;
}
