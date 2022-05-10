// Dalkovy ovladac k tanku
// Vajner Petr
// Email: vajner@seznam.cz
//https://www.instructables.com/Arduino-Uno-Menu-Template/


//Menu

String menuItems[] = {"Prijimac", "  Korekce os", "Leva X", "Leva Y", "Prava X", "Prava Y"};

// Navigation button variables
int readKey;

// Menu control variables
int menuPage = 0;
int maxMenuPages = round(((sizeof(menuItems) / sizeof(String)) / 2) + .5);
int cursorPosition = 0;
boolean inMenu = false;

void testVstupuDoMenu() {
  if(getValBtnMenu() == LOW) {
    pruchodRBtn ++;
  } else {
    pruchodRBtn = 0;
  }
  if(pruchodRBtn >= 10) {
    rezimMenu = true;
    lcd.clear();
  }
  
}

void vykresliMenu() {
  //Serial.print(menuPage);
  //lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(menuItems[menuPage]);
  lcd.setCursor(1, 1);
  lcd.print(menuItems[menuPage + 1]);
  if (menuPage == 0) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
  } else if (menuPage > 0 and menuPage < maxMenuPages) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  } else if (menuPage == maxMenuPages) {
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  }
}



void nakresliKuzor() {
  for (int x = 0; x < 2; x++) {     // Erases current cursor
    lcd.setCursor(0, x);
    lcd.print(" ");
  }

  // The menu is set up to be progressive (menuPage 0 = Item 1 & Item 2, menuPage 1 = Item 2 & Item 3, menuPage 2 = Item 3 & Item 4), so
  // in order to determine where the cursor should be you need to see if you are at an odd or even menu page and an odd or even cursor position.
  if (menuPage % 2 == 0) {
    if (cursorPosition % 2 == 0) {  // If the menu page is even and the cursor position is even that means the cursor should be on line 1
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {  // If the menu page is even and the cursor position is odd that means the cursor should be on line 2
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
  }
  if (menuPage % 2 != 0) {
    if (cursorPosition % 2 == 0) {  // If the menu page is odd and the cursor position is even that means the cursor should be on line 2
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {  // If the menu page is odd and the cursor position is odd that means the cursor should be on line 1
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
  }
}

void operaceMenu() {
  inMenu = true;
  while(inMenu) {
    if(getValRY() < 80) {
      dolu();
      refreshDisplay();
    }
    if(getValRY() > 100) {
      nahoru();
      refreshDisplay();
    }
    if(getValLjBtn() == HIGH) {
      inMenu = false;
      rezimMenu = false;
      lcd.clear();
    }
    if(getValRjBtn() == HIGH) {
      switch (cursorPosition) {
        case 0:
          menuPrijimac(cursorPosition);
          break;
        case 1:
          menuKorekceLx(cursorPosition-1);
          break;
        case 2:
          menuKorekceLx(cursorPosition);
          break;
        case 3:
          menuKorekceLy(cursorPosition);
          break;
        case 4:
          menuKorekceRx(cursorPosition);
          break;
        case 5:
          menuKorekceRy(cursorPosition);
          break;
      }   
    }
    refreshDisplay();
    delay(300);
  }
}

void menuPrijimac(int cursorPosition) {
  boolean zmena = false;
  inMenu = true;
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print(menuItems[cursorPosition]);
  lcd.setCursor(0, 1);
  lcd.print("ID stanice:");
  byte idStanice = idPrijimace;
  while(inMenu) {
    delay(300);
    if(getValRjBtn() == HIGH and zmena) {
      // potvrzeni OK - ulozime hodnotu do pameti
      setIdPrijimace(idStanice);
      inMenu = false;
    }
    if(getValLjBtn() == HIGH) {
      inMenu = false;
    }
    if(getValRY() > 170) {
        idStanice ++;
        zmena = true;          
    }
    if(getValRY() < 50 and idStanice > 1) {
      idStanice --;
      zmena = true;
    }
    String txtIdStanice = getStringValue(idStanice);
    lcd.setCursor(11, 1);
    lcd.print(txtIdStanice);
  }
  lcd.clear();
  refreshDisplay();
}


void menuKorekceLx(int cursorPosition) {
  boolean zmena = false;
  int korekce = getKorekceLx();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(menuItems[cursorPosition] + " Stav:" + String(getValLX()));
  while(inMenu) {
    if(getValRjBtn() == HIGH and zmena) {
      // potvrzeni OK - ulozime hodnotu do pameti
      setKorekceLx(korekce);
      inMenu = false;
    }
    if(getValLjBtn() == HIGH) {
      inMenu = false;
    }
    if(getValRY() > 170) {
        korekce ++;
        zmena = true;
    }
    if(getValRY() < 50) {
      korekce --;
      zmena = true;
    }
    Serial.println("getValRX():" + String(getValRX()));
    String text = "Kor:";
    if(korekce > 0) {
      text=text+"+";
    }
    text = text + String(korekce) + " Novy:" + String(getValLX() + korekce);
    Serial.println(text);
    
    lcd.setCursor(0, 1);
    lcd.print(text);
    delay(300);
  }
  lcd.clear();
  refreshDisplay();
}

void menuKorekceLy(int cursorPosition) {
  boolean zmena = false;
  int korekce = getKorekceLy();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(menuItems[cursorPosition] + " Stav:" + String(getValLY()));
  while(inMenu) {
    if(getValRjBtn() == HIGH and zmena) {
      // potvrzeni OK - ulozime hodnotu do pameti
      setKorekceLy(korekce);
      inMenu = false;
    }
    if(getValLjBtn() == HIGH) {
      inMenu = false;
    }
    if(getValRY() > 170) {
        korekce ++;
        zmena = true;
    }
    if(getValRY() < 50) {
      korekce --;
      zmena = true;
    }
    String text = "Kor:";
    if(korekce > 0) {
      text=text+"+";
    }
    text = text + String(korekce) + " Novy:" + String(getValLY() + korekce);
    lcd.setCursor(0, 1);
    lcd.print(text);
    delay(300);
  }
  lcd.clear();
  refreshDisplay();
}

void menuKorekceRx(int cursorPosition) {
  boolean zmena = false;
  int korekce = getKorekceRx();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(menuItems[cursorPosition] + " Stav:" + String(getValRX()));
  while(inMenu) {
    if(getValRjBtn() == HIGH and zmena) {
      // potvrzeni OK - ulozime hodnotu do pameti
      setKorekceRx(korekce);
      inMenu = false;
    }
    if(getValLjBtn() == HIGH) {
      inMenu = false;
    }
    if(getValRY() > 170) {
        korekce ++;
        zmena = true;
    }
    if(getValRY() < 50) {
      korekce --;
      zmena = true;
    }
    String text = "Kor:";
    if(korekce > 0) {
      text=text+"+";
    }
    text = text + String(korekce) + " Novy:" + String(getValRX() + korekce);
    lcd.setCursor(0, 1);
    lcd.print(text);
    delay(300);
  }
  lcd.clear();
  refreshDisplay();
}

void menuKorekceRy(int cursorPosition) {
  boolean zmena = false;
  int korekce = getKorekceRy();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(menuItems[cursorPosition] + " Stav:" + String(getValRY()));
  while(inMenu) {
    if(getValRjBtn() == HIGH and zmena) {
      // potvrzeni OK - ulozime hodnotu do pameti
      setKorekceRy(korekce);
      inMenu = false;
    }
    if(getValLjBtn() == HIGH) {
      inMenu = false;
    }
    if(getValRY() > 170) {
        korekce ++;
        zmena = true;
    }
    if(getValRY() < 50) {
      korekce --;
      zmena = true;
    }
    String text = "Kor:";
    if(korekce > 0) {
      text=text+"+";
    }
    text = text + String(korekce) + " Novy:" + String(getValRY() + korekce);
    lcd.setCursor(0, 1);
    lcd.print(text);
    delay(300);
  }
  lcd.clear();
  refreshDisplay();
}




void dolu() {
  Serial.println("------- Dolu --------");
  if (menuPage % 2 == 0 and cursorPosition % 2 != 0) {
    menuPage = menuPage + 1;
    menuPage = constrain(menuPage, 0, maxMenuPages);
  }

  if (menuPage % 2 != 0 and cursorPosition % 2 == 0) {
    menuPage = menuPage + 1;
    menuPage = constrain(menuPage, 0, maxMenuPages);
  }

  cursorPosition = cursorPosition + 1;
  cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
  lcd.clear();
}

void nahoru() {
  Serial.println("------- Nahoru --------");
  if (menuPage == 0) {
    cursorPosition = cursorPosition - 1;
    cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
  }
  if (menuPage % 2 == 0 and cursorPosition % 2 == 0) {
    menuPage = menuPage - 1;
    menuPage = constrain(menuPage, 0, maxMenuPages);
  }

  if (menuPage % 2 != 0 and cursorPosition % 2 != 0) {
    menuPage = menuPage - 1;
    menuPage = constrain(menuPage, 0, maxMenuPages);
  }

  cursorPosition = cursorPosition - 1;
  cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
  lcd.clear();
}

void refreshDisplay() {
  vykresliMenu();
  nakresliKuzor();
}
