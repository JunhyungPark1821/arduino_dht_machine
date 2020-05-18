#include <SimpleDHT.h>
#include <LiquidCrystal.h>


// for DHT11, 
//      VCC: 3.5V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;  //Second pin receives the data from DHT11
SimpleDHT11 dht11;  //DHT11 electrical component


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  //set pin direction
  pinMode(4, OUTPUT);
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Temp: ");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  }

void loop() {
  //DHT11 read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    return;
  }

  //Relay conditions
  if ((int) humidity > 60) {  //If the humidity percentage is over 60%
      digitalWrite (4,HIGH); //Circuit is closed
  }
  else {
    digitalWrite (4, LOW); //Circuit is open
  }
  
  //LCD Display of temperature and humidity
  lcd.setCursor(6,0);
  lcd.print ((int)temperature);
  lcd.print (" 'C");
  lcd.setCursor(10,1);
  lcd.print ((int)humidity);
  lcd.print (" %");
  Serial.print((int)temperature); Serial.print(" 'C, ");
  Serial.print((int)humidity); Serial.println(" %");
  
  // DHT11 sampling rate is 1HZ.
  delay(5000);
}