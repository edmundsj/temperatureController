#define SHUTDOWN_REGISTER 0x0C
#define DIGIT0_REGISTER 0x01
#define DIGIT1_REGISTER 0x02
#define DIGIT2_REGISTER 0x03
#define DIGIT3_REGISTER 0x04
#define DIGIT4_REGISTER 0x05
#define DIGIT5_REGISTER 0x06
#define DIGIT6_REGISTER 0x07
#define DIGIT7_REGISTER 0x08
#define DECODE_MODE_REGISTER 0x09
#define SCAN_LIMIT_REGISTER 0x0B
#define INTENSITY_REGISTER 0x0A
#define DISPLAY_REFRESH_PERIOD 100
#define CHIP_SELECT_PIN 10

#include <SPI.h>

bool display_initialized = false;

void SPIWrite(uint8_t command_byte, uint8_t data_byte) {
  digitalWrite(CHIP_SELECT_PIN, LOW);
  SPI.transfer(command_byte);
  SPI.transfer(data_byte);
  digitalWrite(CHIP_SELECT_PIN, HIGH);
}

class Display {
  public:
  Display(uint8_t, uint8_t, uint8_t);
  void writeTemperature(float);
  void writeCurrent(float);
  void writeVoltage(float);
  uint8_t digit1_register;
  uint8_t digit2_register;
  uint8_t digit3_register;
  
};

Display::Display(uint8_t digit1, uint8_t digit2, uint8_t digit3) {
  this->digit1_register = digit1;
  this->digit2_register = digit2;
  this->digit3_register = digit3;
}

void Display::writeTemperature(float temperature) {
  if(temperature < 0) temperature = -1* temperature;
  SPIWrite(this->digit1_register, int(temperature / 10));
  SPIWrite(this->digit2_register, int(temperature) % 10 | 0b10000000);
  SPIWrite(this->digit3_register, int(temperature * 10) % 10);
}

void Display::writeCurrent(float current) {
  SPIWrite(this->digit1_register, int(current) | 0b10000000);
  SPIWrite(this->digit2_register, int(current * 10) % 10);
  SPIWrite(this->digit3_register, int(current * 100) % 10);
}

void Display::writeVoltage(float voltage) {
  SPIWrite(this->digit1_register, int(int(voltage) / 100 % 10));
  SPIWrite(this->digit2_register, int(int(voltage) / 10) % 10);
  SPIWrite(this->digit3_register, int(int(voltage) % 10));
}

void initializeDisplayDriver(void) {
    SPIWrite(SHUTDOWN_REGISTER, 1);

    // Enable BCD decoding for each register
    SPIWrite(DECODE_MODE_REGISTER, 0xFF);

    // Drive all the display digits
    SPIWrite(SCAN_LIMIT_REGISTER, 0x05); 

    // Set the intensity (duty cycle) to 5/32.
    SPIWrite(INTENSITY_REGISTER, 0x02);

    display_initialized = true;
}
