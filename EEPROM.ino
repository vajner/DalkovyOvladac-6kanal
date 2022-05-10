// Dalkovy ovladac k tanku
// Vajner Petr
// Email: vajner@seznam.cz
//      Nazev         Pozice v pameti
//--------------------------------------
#define ID_PRIJIMACE  0
#define NAZEV_RADIA   1 //-- "VaPet"
#define KOREKCE_LX    2
#define KOREKCE_LY    3
#define KOREKCE_RX    4
#define KOREKCE_RY    5


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

byte getSSIDRadia() {
  return EEPROM.read(NAZEV_RADIA);
}

void setSSIDRadia(byte SSID) {
  EEPROM.write(NAZEV_RADIA, SSID);
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
