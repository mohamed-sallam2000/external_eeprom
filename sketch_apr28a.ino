#include <Wire.h>

#define EEPROM_ADDR 0x50  // I2C address of EEPROM

void setup() {
  Wire.begin();  // Initialize I2C
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  // Write data to EEPROM
  byte data[] = {0x01, 0x23, 0x45, 0x67, 0x89};  // Data to be written
  unsigned int addr = 0x1234;  // Address to write the data to

  // Send write request to EEPROM
  Wire.beginTransmission(EEPROM_ADDR);
  Wire.write((int)(addr >> 8));  // Send MSB of address
  Wire.write((int)(addr & 0xFF));  // Send LSB of address
  Wire.write(data, sizeof(data));  // Send data to be written
  Wire.endTransmission();

  delay(1000);  // Wait for EEPROM to finish writing

  // Read data from EEPROM
  byte readData[sizeof(data)];  // Array to store read data

  // Send read request to EEPROM
  Wire.beginTransmission(EEPROM_ADDR);
  Wire.write((int)(addr >> 8));  // Send MSB of address
  Wire.write((int)(addr & 0xFF));  // Send LSB of address
  Wire.endTransmission();

  // Read data from EEPROM
  Wire.requestFrom(EEPROM_ADDR, sizeof(readData));
  for (int i = 0; i < sizeof(readData); i++) {
    readData[i] = Wire.read();
  }

  // Print data to serial monitor
  Serial.print("Data written: ");
  for (int i = 0; i < sizeof(data); i++) {
    Serial.print(data[i], HEX);
    Serial.print(" ");
    
  }
  Serial.println();
  Serial.print("Data read: ");
  for (int i = 0; i < sizeof(readData); i++) {
    Serial.print(readData[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  delay(1000);  // Wait before writing and reading data again
}
