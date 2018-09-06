
#include <SPI.h>
#include <MFRC522.h>
#include <Ethernet.h>

#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];

// Ethernet
// network configuration. dns server, gateway and subnet are optional.



String readString;
String headerSeparator = "\r\n\r\n";

void setup() { 
  Serial.begin(9600);
initRfid();
//initEthernet();
}
 
void loop() {

  // Look for new cards or Verify if the NUID has been readed
  if ( ! rfid.PICC_IsNewCardPresent() || ! rfid.PICC_ReadCardSerial())
    return;

  Serial.println(F("The NUID tag is:"));
  printHex(rfid.uid.uidByte, rfid.uid.size);
  printDec(rfid.uid.uidByte, rfid.uid.size);

  //autorizarNoServidor(rfid.uid.uidByte, rfid.uid.size);

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}

void autorizarNoServidor(byte *buffer, byte bufferSize){
  String chave; 
  for (byte i = 0; i < bufferSize; i++) {
    chave += buffer[i] < 0x10 ? " 0" : " ";
  }

  Serial.println("------");
  Serial.println(chave);
  Serial.println("------");
}

/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  Serial.print(F("In hex: "));
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
  Serial.println();
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  Serial.print(F("In dec: "));
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
  Serial.println();
}

void initEthernet(){
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);
  //print out the IP address
  Serial.print("IP = ");
  Serial.println(Ethernet.localIP());
}


void initRfid(){
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}
