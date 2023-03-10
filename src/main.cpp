// This main.cpp has turn the relay on when the key is turn on and from the Bluetooth, you can turn it ON and OFF by 
// On OFF or On on the App after conntecting to the brelay bluetooth

#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // LCD librairy
#include <BluetoothSerial.h>
LiquidCrystal_I2C lcd(0x27,16,2);    // set the LCD address to 0x27 for a 16 chars and 2 line display
BluetoothSerial SerialBT;
int RELAYPIN = 4;                   // Set the pin of the LED 
String message;                    // The control message
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  SerialBT.begin("RELAY");       //Set Bluetooth the name to "RELAY"
  lcd.print("Relay started");
  lcd.setCursor(0, 1); 
  lcd.print("With Bluetooth!");
  pinMode(RELAYPIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (SerialBT.available())
  {
    char data = SerialBT.read();   // if there is data on the serial monitor, read it or print 
    if (data != '\n'){
       message += String(data);    // keep adding the Char untill EOC
    }
    else{
      message ="";
    }
    
    if (message == "ON")
    {
      digitalWrite(RELAYPIN, LOW);
       lcd.clear();                  // clear display
       lcd.setCursor(7, 0);         // move cursor to   (0, 0)
       lcd.print(message);         // print message at (0, 0)
    }
    else if (message == "OFF")
    {
      digitalWrite(RELAYPIN, HIGH);
      lcd.clear();                  // clear display
      lcd.setCursor(7, 0);         // move cursor to   (0, 0)
      lcd.print(message);         // print message at (0, 0)
    }
    
  }
  

}