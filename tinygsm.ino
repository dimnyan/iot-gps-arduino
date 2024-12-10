// RX, TX
// (5, 4); 

/**************************************************************
 *
 * This script tries to auto-detect the baud rate
 * and allows direct AT commands access
 *
 * TinyGSM Getting Started guide:
 *   https://tiny.cc/tinygsm-readme
 *
 **************************************************************/

// Select your modem:
// #define TINY_GSM_MODEM_SIM800
#define TINY_GSM_MODEM_SIM900
// #define TINY_GSM_MODEM_ESP8266

// Set serial for debug console (to the Serial Monitor, speed 115200)
#define SerialMon Serial

// Set serial for AT commands (to the module)
// Use Hardware Serial on Mega, Leonardo, Micro
#ifndef __AVR_ATmega328P__
#define SerialAT Serial1

// or Software Serial on Uno, Nano
#else
#include <SoftwareSerial.h>
SoftwareSerial SerialAT(5, 4);  // RX, TX
#endif

#define TINY_GSM_DEBUG SerialMon

#include <TinyGsmClient.h>

// Module baud rate
uint32_t rate = 9600;  // Set to 0 for Auto-Detect
// TinyGsm modem(SerialAT);
// TinyGsmClient client(modem);
// #define GSM_PIN = 5;
// String apn = "M2MINTERNET";    // apn
// String gprsUser = "dimasnyoman1@gmail.com";  // apn username
// String gprsPass = "IOT888888";  // apn password
// String server = "broker.emqx.io";  
// String port = "1883";

void setup() {
  // Set console baud rate
  SerialMon.begin(9600);
  // modem.init();
  // modem.simUnlock(GSM_PIN);
  // modem.waitForNetwork(600000L);
  // modem.gprsConnect(apn, gprsUser, gprsPass)
  // client.connect(server, port)
  delay(6000);
}

void loop() {
  if (!rate) { rate = TinyGsmAutoBaud(SerialAT); }

  if (!rate) {
    SerialMon.println(
        F("***********************************************************"));
    SerialMon.println(F(" Module does not respond!"));
    SerialMon.println(F("   Check your Serial wiring"));
    SerialMon.println(
        F("   Check the module is correctly powered and turned on"));
    SerialMon.println(
        F("***********************************************************"));
    delay(30000L);
    return;
  }

  SerialAT.begin(rate);

  // Access AT commands from Serial Monitor
  SerialMon.println(
      F("***********************************************************"));
  SerialMon.println(F(" You can now send AT commands"));
  SerialMon.println(
      F(" Enter \"AT\" (without quotes), and you should see \"OK\""));
  SerialMon.println(
      F(" If it doesn't work, select \"Both NL & CR\" in Serial Monitor"));
  SerialMon.println(
      F("***********************************************************"));

  while (true) {
    if (SerialAT.available()) { SerialMon.write(SerialAT.read()); }
    if (SerialMon.available()) { SerialAT.write(SerialMon.read()); }
    delay(0);
  }
}