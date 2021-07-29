const int ledPin = LED_BUILTIN;
int variable = 0;
char message[20];

void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.println(variable);
  

}

void loop() {
  variable= Serial.read();
  Serial.println(variable);
  if(variable == 1){
    digitalWrite(ledPin, HIGH);
  }else{
    digitalWrite(ledPin, LOW);
  }
  Serial.readBytes(message,20);
  Serial.println(message);

}
