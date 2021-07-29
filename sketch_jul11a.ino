

/*
 *  Created by Samia DEBBAB
 *  
 *  Email: samiadebbab18@gmail.com
 *  
 *  juil 2021
 *  
  */
 #include <SPI.h>
 #include <Ethernet2.h>
 // Ethernet library
 
 #include <ArduinoModbus.h>

// Modbus library

EthernetClient clients;            // 

ModbusTCPClient modbusTCPClient(clients);            // Modbus TCP/IP

IPAddress server(192, 168, 1, 10);


void setup(){

  // Ethernet setting:
  // 1- define MAC @ ( a9era fel module ida we ketebo ida makanch dir kima tehb ida mamchatelkch sema kayen haja wahedoukhera 3emedeha mm @ mac donc tebedlo berk heta temchilk )
  // 2- define IP @ pr modbus TCP/IP gnrlmnt yediro (192.168.1.22)
  // 3- define subnet mask gnrlmnt yekon (255.255.255.0)

  byte mac[]={0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEC};
  byte ip[]={192, 168, 1, 177};
  byte mask[]={255, 255, 255, 0};
  

  //initialize the ethernet device

  Ethernet.begin(mac, ip, mask);         //assign mac,ip,subnet
  Serial.begin(9600);                   // baude rate 9600

  
    


}

void loop() {
   if (!modbusTCPClient.connected()) {
    // client not connected, start the Modbus TCP client
    Serial.println("Attempting to connect to Modbus TCP server");
    
    if (!modbusTCPClient.begin(server, 502)) {
      Serial.println("Modbus TCP Client failed to connect!");
    } else {
      Serial.println("Modbus TCP Client connected");
    }
  } else {
    // client connected

    // write the value of 0x01, to the coil at address 0x00
    if (!modbusTCPClient.coilWrite(0x00, 0x01)) {
      Serial.print("Failed to write coil! ");
      Serial.println(modbusTCPClient.lastError());
    }

    // wait for 1 second
    delay(1000);

    // write the value of 0x00, to the coil at address 0x00
    if (!modbusTCPClient.coilWrite(0x00, 0x00)) {
      Serial.print("Failed to write coil! ");
      Serial.println(modbusTCPClient.lastError());
    }

    // wait for 1 second
    delay(1000);
  }
}
