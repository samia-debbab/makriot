int vari= -1;
char msg[15]= "allumer la led";

void setup() {
Serial.begin(9600);

}

void loop() {
Serial.write(vari);
delay(5000);

Serial.write(msg,15);
delay(5000);
}
