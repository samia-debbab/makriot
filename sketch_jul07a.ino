
#include <enc28j60.h>
#include <EtherCard.h>

/*
 *  Created by Samia DEBBAB
 *  
 *  Email: samiadebbab18@gmail.com
 *  
 *  juil 2021
 */                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              

 #include <SPI.h>
 #include <Ethernet2.h>   // nesiyi hadi ida maselhetch nedir ethernet2

 // Ethernet library
 
 #include <ArduinoModbus.h>

// Modbus library

EthernetServer etherServer(502);            // TCP port

ModbusTCPServer modbusTCPServer;            // Modbus TCP/IP

const int ledPin = LED_BUILTIN;     //juste pr tester

unsigned long holdingResult, inputResult, h, t, tf, hi, hif, i;

void setup(){

  // Ethernet setting:
  // 1- define MAC @ ( a9era fel module ida we ketebo ida makanch dir kima tehb ida mamchatelkch sema kayen haja wahedoukhera 3emedeha mm @ mac donc tebedlo berk heta temchilk )
  // 2- define IP @ pr modbus TCP/IP gnrlmnt yediro (192.168.1.22)
  // 3- define subnet mask gnrlmnt yekon (255.255.255.0)

  byte mac[]={0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  byte ip[]={192, 168, 1, 22};
  byte mask[]={255, 255, 255, 0};
  

  //initialize the ethernet device

  Ethernet.begin(mac, ip, mask);         //assign mac,ip,subnet
  Serial.begin(9600);                   // baude rate 9600

  
   // start the server
  etherServer.begin();                 //  start listening for cliente

  
 // modbusTCPServer.begin();         nesiyi methode lokhera ida maselehetch nedir hadi
 

 // start the Modbus TCP server
  if (!modbusTCPServer.begin()) {
    Serial.println("Failed to start Modbus TCP Server!");
    while (1);
  }
  
  // define holding register:

  holdingResult = modbusTCPServer.configureHoldingRegisters(0,100);      // reserver des register pour stocker les donnees
  inputResult = modbusTCPServer.configureInputRegisters(0,100);         //  reserve input registers
  Serial.println("holding reg init result");
  Serial.println(holdingResult);
  Serial.println("input result");
  Serial.println(inputResult);
  Serial.println(Ethernet.localIP());           // afficher l'@ ip du serveur modbus

  // configure a single coil at address 0x00
  modbusTCPServer.configureCoils(0x00, 1);

   // configure the LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
}

void loop(){
  // listen for incoming clients
  EthernetClient client = etherServer.available();
  
  if (client) {
    // a new client connected
    Serial.println("new client");

    // let the Modbus TCP accept the connection 
    modbusTCPServer.accept(client);

    while (client.connected()) {
      // poll for Modbus TCP requests, while client connected
      modbusTCPServer.poll();

      //lire la temperature et l'hmidite
      updateTH();
    }

    Serial.println("client disconnected");
  }
}

void updateTH(){

   // read the current value of the coil          nesiyi led apres nchof 
  int coilValue = modbusTCPServer.coilRead(0x00);

  if (coilValue) {
    // coil value set, turn LED on
    digitalWrite(ledPin, HIGH);
  } else {
    // coild value clear, turn LED off
    digitalWrite(ledPin, LOW);
  }

  
}
 
