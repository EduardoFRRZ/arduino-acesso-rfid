
#include <SPI.h>
#include <MFRC522.h>
#include <Ethernet.h>



byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// the dns server ip
IPAddress dnServer(192, 168, 0, 1);
// the router's gateway address:
IPAddress gateway(192, 168, 0, 1);
// the subnet:
IPAddress subnet(255, 255, 255, 0);

//the IP address is dependent on your network
IPAddress ip(192, 168, 0, 2);

EthernetClient client;
byte server[] = { 192, 168, 0, 101 };

String headerSeparator = "\r\n\r\n";

#define SS_PIN 6
#define RST_PIN 7

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;

// Init array that will store new NUID
byte nuidPICC[4];
const int led1 = 3;
const int led2 = 4;
const int led3 = 5;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);


  // initialize the ethernet device
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);
  //print out the IP address
  Serial.print("IP = ");
  Serial.println(Ethernet.localIP());


}

void loop() {

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  Serial.print(F("In hex: "));
  String uid = printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  delay(1000);
  autenticarServidor(uid);



  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}

void autenticarServidor(String uid) {
  if (client.connect(server, 8080)) {
    Serial.println("connected");
    client.println("GET /AutenticaCliente/autenticacao.php?uid=" + uid + " HTTP/1.0");
    client.println();
  } else {
    Serial.println("connection failed");
  }

  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);
        readString += c;
      }
    }
  }
  client.stop();

  int pos = readString.indexOf(headerSeparator) + headerSeparator.length();
  Serial.println(readString.substring(pos));

  if (readString.indexOf("zero") > 0) {
    Serial.println("bloqueado");
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }

  else if (readString.indexOf("um") > 0) {
    Serial.println("um__");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }

  else if (readString.indexOf("dois") > 0) {
    Serial.println("dois__");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
  }

  else if (readString.indexOf("tres") > 0) {
    Serial.println("tres__");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }


}


/**
   Helper routine to dump a byte array as hex values to Serial.
*/

String printHex(byte *buffer, byte bufferSize) {
  String key;
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
    key += buffer[i], HEX;
  }
  Serial.println("------------");
  Serial.println(key);
  return key;
}

/**
   Helper routine to dump a byte array as dec values to Serial.
*/
String printDec(byte *buffer, byte bufferSize) {
  String key;
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
    key += buffer[i], HEX;
  }
  return key;
}
