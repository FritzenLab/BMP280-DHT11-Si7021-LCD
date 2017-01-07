/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMEP280 Breakout 
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required 
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

// BMP280
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10

// DTH11
#include "DHT.h"   
#define DHTPIN 2 
#define DHTTYPE DHT11  // DHT 11  

// Si7021
#include <Artekit_SI7021.h> 

Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
DHT dht(DHTPIN, DHTTYPE);
Artekit_SI7021 si7021; 

float temperature;  
float humidity; 
  
void setup() {

  Wire.begin();
  dht.begin();
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));
  
  if (!bme.begin()) {  
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  
}

void loop() {

    // BEGIN of BMP280
    
       
    // END of BMP280

    // BEGIN of DHT11
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)  
  float h = dht.readHumidity();  
  // Read temperature as Celsius (the default)  
  float t = dht.readTemperature();  
  // END of DHT11

  // BEGIN of Si7021
    /* Read relative humidity and temperature */  
  humidity = si7021.ReadHumidity();    
  /* By setting true in the next function, we read the  
   * temperature from the previous RH measurement.  
   * Otherwise it will perform a new temperature measurement.  
   */  
  temperature = si7021.ReadTemperature(true);  
  // END of Si7021
  
  Serial.println("---");  
  Serial.print("Si7021 Temperatura: ");  
  Serial.print(temperature);
  Serial.print(" *C ");
  Serial.print(" || BMP280 Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.print(" *C ");
  Serial.print(" || DHT11 Temperatura: ");  
  Serial.print(t);  
  Serial.println(" *C");
  Serial.println("---");

  Serial.println("---");
  Serial.print("DHT11 Umidade: ");  
  Serial.print(h);  
  Serial.print(" %RH ");
  Serial.print(" || Si7021 Umidade: ");  
  Serial.print(humidity); 
  Serial.println(" %RH");  
  Serial.println("---");
       
  Serial.print("BMP280 Pressure = ");
  Serial.print(bme.readPressure());
  Serial.print(" Pa ");

  Serial.print(" || BMP280 Approx altitude = ");
  Serial.print(bme.readAltitude()); // this should be adjusted to your local forcase
  Serial.println(" m");

   
  Serial.println("---");
  
  delay(2000);
}
