


// Dalkovy ovladac k tanku
// Vajner Petr
// Email: vajner@seznam.cz

// připoj knihovny
#include <EEPROM.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <RF24.h>
#include <nRF24L01.h>


//
// =======================================================================================================
// PIN ASSIGNMENTS & GLOBAL VARIABLES
// =======================================================================================================
//

  //#define DEBUG // if not commented out, Serial.print() is active! For debugging only!!
  //#define DEBUG_JOY

  // Is the radio or IR transmission mode active?
  byte transmissionMode = 1; // Radio mode is active by default
  
  // Select trannsmitter operation mode
  //byte operationMode = 0; // Start in transmitter mode (0 = transmitter mode, 1 = tester mode, 2 = game mode)
  
  // Vehicle address
  int vehicleNumber = 1; // Vehicle number one is active by default
  
  // Radio channels (126 channels are supported)
  byte chPointer = 0; // Channel 1 (the first entry of the array) is active by default
  const byte NRFchannel[] {
    1, 2
  };



RF24 radio(9, 10); // CE, CSN
//const byte addresses[][6] = {"00001", "00002"};
//const byte addresses[][10] = {"VaPet-A", "VaPet-B"};
byte addressa[6] = "VaPe3";


// inicializace knihovny displeje 
LiquidCrystal_I2C lcd(0x27,16,2);      // nastavit adresu displeje na 0x27 pro 1602 modry displej, zeleny je 0x3f
// menu
byte sipkaDolu[8] = {
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b10101, // * * *
  0b01110, //  ***
  0b00100  //   *
};
byte sipkaNahoru[8] = {
  0b00100, //   *
  0b01110, //  ***
  0b10101, // * * *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100  //   *
};

byte menuCursor[8] = {
  B01000, //  *
  B00100, //   *
  B00010, //    *
  B00001, //     *
  B00010, //    *
  B00100, //   *
  B01000, //  *
  B00000  //
};


// displej
String txtRadek1 = "Bat:%batL%%/%batR%% R:";
String radek2 = "";
boolean spojeno = false;
boolean rezimMenu = false;
int pauza = 500;
int limitniDobaStisku = 5000; // milisekund


// nastaveni pinu procesoru
const byte analogPinLX        = A0;   // Levy  Joystick osa X
const byte analogPinLY        = A1;   // Levy  Joystick osa Y
const byte analogPinRX        = A2;   // Pravy Joystick osa X
const byte analogPinRY        = A3;   // Pravy Joystick osa Y
const byte digitalJoyLSwitch  = 2; // Levy switch - D2
const byte digitalJoyRSwitch  = 4; // Pravy switch - D4
const byte digitalMenuSw      = 3;    // tlacitko pro vstup do menu PD7

// promenne
byte pruchodRBtn = 0;
byte valMenuSw = 0;
boolean ready = false;
String nazevZarizeni="";
int lBateryVal = 0;
int rBateryVal = 0;
byte idPrijimace = 0;
String prijato;
boolean intro = true;

struct Data_Info {
  char nazevZarizeni[9]="";
  byte urovenBaterie = 0;
  byte channel = 1; // the channel number
};

struct Data_Command {
  byte rJoyX;
  byte rJoyY;
  byte lJoyX;
  byte lJoyY;
  byte rJoyBtn;
  byte lJoyBtn;
};

Data_Command  data;
Data_Info     dataInfo;

boolean transmissionState;

void setup() {
  //Serial.begin(9600);                 //  setup serial
  Serial.begin(115200);
  #ifdef DEBUG
    Serial.println("Inicializace ....... ");
    //printf_begin();
    //delay(3000);
  #endif

  setupRadio();
  
  lcd.init();                         // inicializace lcd
  lcd.backlight();                    // zapnout podsvícení 
  lcd.begin(16, 2);
  lcd.clear();
  lcd.createChar(0, menuCursor);
  lcd.createChar(1, sipkaNahoru);
  lcd.createChar(2, sipkaDolu);
  pinMode(digitalJoyLSwitch, INPUT);
  pinMode(digitalJoyRSwitch, INPUT);
  pinMode(digitalMenuSw, INPUT_PULLUP);

  if(intro) {
    zobrazIntro();
    intro=false;
  }
}

void loop() {
  if (Serial.available() > 0) {
    String prijato = Serial.readString();  
    if(prijato.length() > 0) {
      zpracujPrichoziPrikaz(prijato);
    }
  }
  
  nactiOvladaciPrvky();
  odesliAPrijmiData();
  printDisplay();
  testVstupuDoMenu();
}

void prijmiData() {
  //delay(10);
  radio.startListening();
  if (radio.available()) {
    spojeno = true;
    radio.read(&dataInfo, sizeof(Data_Info));
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
  } else {
    spojeno=false;
    nazevZarizeni = "";
    rBateryVal = 0;
  }
}

void printDisplay() {
  if(rezimMenu) {
    vykresliMenu();
    nakresliKuzor();
    operaceMenu();
  } else {
    printDefaultSreen();
  }
}

String getStringValue(int hodnota) {
  int soucet = 100+hodnota;
  String sHodnota = (String)soucet;
  String vystup = sHodnota.substring(1, 3);
  return vystup;
}
