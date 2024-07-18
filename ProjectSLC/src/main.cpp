/***************************************************
SLC (Self Learning Cube) Project

 ***************************************************
 Wiring Diagram
 Node MCU      RFID Reader
    D4            SDA
    D5            SCK
    D7            MOSI
    D6            MISO
    GND           GND
    D3            RST
    3V            3.3V
    
 Node MCU      DF Player Mini
    D1            TX
    D2            RX (Series with 1k ohm resistor)
    GND           GND

 This Porject using 2x Batery 18650 for powering DF Player Mini and Node MCU
 This code is tested on Node MCU Lolin, RFID MFRC 522, DF Player Mini

 Created May 2022
 By
 [Andi Saputra](3332190032)
 [Arif Alfian](3332190055)
 [Andre Januar Sibarani](3332190096)

 Teknik Elektro, Universitas Sultan Ageng Tirtayasa
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <SPI.h>
#include <MFRC522.h>

SoftwareSerial mySoftwareSerial(D1, D2); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

String tag;
int angkaPertama, angkaKedua, opearasi, hasil;
bool isOperator = false;
bool isPanggilHasil = false;

void setup()
{
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522

  if (!myDFPlayer.begin(mySoftwareSerial,1,0)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
//    while(true);
  }
  myDFPlayer.volume(100);
  Serial.println("SLC Ready");
}


void playLagu(int kiriman){
  myDFPlayer.play(kiriman);
}

void bacarfid() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    if (tag == "20421117174") { //Tiger
      playLagu(45);
      Serial.println("tiger");
    }if (tag == "2314011850"){ // Elephant
      playLagu(42);
      Serial.println("elephant");
    }if (tag == "751129178"){ // Frog
      playLagu(43);
      Serial.println("frog");
    }if (tag == "6080129175"){ // Chicken
      playLagu(44);
      Serial.println("chicken");
    }if (tag == "525416186"){ // Cat
      playLagu(41);
      Serial.println("cat");
    }
    if (tag == "2520736163"){ //Tambah
      isOperator = true;
      opearasi = 1;
      playLagu(40);
      Serial.println("tambah");
    }
    if (tag == "6016325556"){ //Kurang
      isOperator = true;
      opearasi = 2;
      playLagu(39);
      Serial.println("kurang");
    }
    if (tag == "1452133038"){ //Kali
      isOperator = true;
      opearasi = 3;
      playLagu(38);
      Serial.println("kali");
    }
    if (tag == "167419899"){ // Angka 1
      if(!isOperator){
        angkaPertama = 1;
      }
      else{
        angkaKedua = 1;
        isOperator = false;
        isPanggilHasil = true;
      }
      playLagu(1);
      delay(1000);
      Serial.println("satu");
    }
    if (tag == "91806246"){ // Angka 2
      if(!isOperator){
        angkaPertama = 2;
      }
      else{
        angkaKedua = 2;
        isOperator = false;
        isPanggilHasil = true;
      }
      playLagu(2);
      delay(1000);
      Serial.println("dua");
    }
    if (tag == "21115324123"){ // Angka 3
      if(!isOperator){
        angkaPertama = 3;
      }
      else{
        angkaKedua = 3;
        isOperator = false;
        isPanggilHasil = true;
      }
      playLagu(3);
      delay(1000);
      Serial.println("tiga");
    }
    if (tag == "2271507423"){ // Angka 4
      if(!isOperator){
        angkaPertama = 4;
      }
      else{
        angkaKedua = 4;
        isOperator = false;
        isPanggilHasil = true;
      }
      playLagu(4);
      delay(1000);
      Serial.println("empat");
    }
    if (tag == "6723813921"){ // Angka 5
      if(!isOperator){
        angkaPertama = 5;
      }
      else{
        angkaKedua = 5;
        isOperator = false;
        isPanggilHasil = true;
      }
      playLagu(5);
      delay(1000);
      Serial.println("lima");
    }
    if (tag == "2271404723"){ // Angka 6
      if(!isOperator){
        angkaPertama = 6;
      }
      else{
        angkaKedua = 6;
        isOperator = false;
        isPanggilHasil = true;
      }
      playLagu(6);
      delay(1000);
      Serial.println("enam");
    }
    if((opearasi == 1) && (isPanggilHasil == true)){
      hasil = angkaPertama + angkaKedua;
      playLagu(37);
      delay(1500);
      playLagu(hasil);
      isPanggilHasil = false;
    }
    else if((opearasi == 2) && (isPanggilHasil == true)){
      hasil = angkaPertama - angkaKedua;
      playLagu(37);
      delay(1500);
      playLagu(hasil);
      isPanggilHasil = false;
    }
    else if((opearasi == 3) && (isPanggilHasil == true)){
      hasil = angkaPertama * angkaKedua;
      playLagu(37);
      delay(1500);
      playLagu(hasil);
      isPanggilHasil = false;
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}

void loop()
{
  bacarfid();
}