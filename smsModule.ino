#include <SoftwareSerial.h>
SoftwareSerial sim(10, 11);
int _timeout;
String _buffer;
String number = "+48xxxxxxxxx";

void setup() {
  Serial.println("Module SMS:");
  delay(7000); //
  Serial.begin(9600);
  _buffer.reserve(50);
  sim.begin(9600);
  delay(1000);
}

void loop() {
  SendMessage();
  Serial.print("wyslano");
  delay(10000);
}

void SendMessage()
{
  Serial.println("SendMessage():");
  Serial.println("Setting function type as: SMS (AT+CMGF=1)");
  sim.println("AT+CMGF=1");
  delay(1000);
  Serial.println("Setting telefon number as :"+number);
  sim.println("AT+CMGS=\"" + number + "\"\r"); //
  delay(1000);
  Serial.println("Trying to send");
  //EDIT SMS TEKST
  String SMS = "SMS TEXT"; 
  sim.println(SMS);
  delay(100);
  sim.println((char)26); 
  // ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
}

String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000)
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}
