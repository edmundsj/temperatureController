#include <SPI.h>
#define CHIP_SELECT_PIN 10
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
#define TSET_PIN A1
#define DRIVE_PIN 5

#define OFFSET 0
#define ISNS_HIGH A0
#define ISNS_LOW A2

#define TEMPERATURE_MAX 65
#define TEMPERATURE_MIN -25
#define SAMPLES_TO_AVERAGE 500
#define CURRENT_MAX 4
#define CURRENT_MIN 0

uint8_t command_byte = 0;
uint8_t data_byte = 0;
bool display_initialized = false;
float new_desired_temperature = 50.0;
float desired_temperature = 50.0;
float read_temperature = 20.0;
uint16_t raw_data = 0;
uint32_t total_data = 0;
float fractional_maximum = 0.0;
float measured_current = 0.0;
float desired_current = 0.25;
float current_error = 0;
float previous_current_error = 0;
float new_desired_current = 0;
float drive_voltage = 0.0;
float Zp = 2.0; // Units of Ohms, or V/A, determines the dynamics of the system.
float Ti = 10; // Integral time constant
float filter_coefficient = 0; // zero is equivalent to no filter.
float sampling_time = 0.02;


void setup() {
  // put your setup code here, to run once:
  pinMode(CHIP_SELECT_PIN, OUTPUT);
  pinMode(DRIVE_PIN, OUTPUT);
  pinMode(TSET_PIN, INPUT);
  pinMode(ISNS_HIGH, INPUT);
  pinMode(ISNS_LOW, INPUT);
  SPI.begin();
  Serial.begin(9600);
  Serial.print(measured_current);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(display_initialized == false) {
    

    // take the device out of shutdown mode and put it into display test mode
    SPIWrite(SHUTDOWN_REGISTER, 1);

    // Enable BCD decoding for each register
    SPIWrite(DECODE_MODE_REGISTER, 0xFF);

    // Drive all the display digits
    SPIWrite(SCAN_LIMIT_REGISTER, 0x05); 

    // Set the intensity (duty cycle) to 5/32.
    SPIWrite(INTENSITY_REGISTER, 0x02);

    display_initialized = true;
  }
  else {
    delay(sampling_time * 1000);
    measureCurrent();
    controlCurrent();
    //getTargetTemperature();
    //writeSetpointDisplayCurrent(desired_temperature);
    //writeActualDisplayCurrent(measured_temperature);
    //getTargetCurrent();
    getTargetVoltage();
    writeSetpointDisplayVoltage();
    writeActualDisplayCurrent(measured_current);
    Serial.println(measured_current);
  }
}

void SPIWrite(uint8_t command_byte, uint8_t data_byte) {
  digitalWrite(CHIP_SELECT_PIN, LOW);
  SPI.transfer(command_byte);
  SPI.transfer(data_byte);
  digitalWrite(CHIP_SELECT_PIN, HIGH);
}

void writeSetpointDisplayTemperature(float temperature) {
  if(temperature < 0) temperature = -1* temperature;
  SPIWrite(DIGIT0_REGISTER, int(temperature / 10));
  SPIWrite(DIGIT1_REGISTER, int(temperature) % 10 | 0b10000000);
  SPIWrite(DIGIT2_REGISTER, int(temperature * 10) % 10);
}

void writeActualDisplayTemperature(float temperature) {
  if(temperature < 0) temperature = -1* temperature;
  SPIWrite(DIGIT3_REGISTER, int(temperature / 10));
  SPIWrite(DIGIT4_REGISTER, int(temperature) % 10 | 0b10000000);
  SPIWrite(DIGIT5_REGISTER, int(temperature * 10) % 10);
}

void writeSetpointDisplayCurrent(float current) {
  SPIWrite(DIGIT0_REGISTER, int(current) | 0b10000000);
  SPIWrite(DIGIT1_REGISTER, int(current * 10) % 10);
  SPIWrite(DIGIT2_REGISTER, int(current * 100) % 10);
}

void writeActualDisplayCurrent(float current) {
  SPIWrite(DIGIT3_REGISTER, int(current) | 0b10000000);
  SPIWrite(DIGIT4_REGISTER, int(current * 10) % 10);
  SPIWrite(DIGIT5_REGISTER, int(current * 100) % 10);
}

void writeSetpointDisplayVoltage(void) {
  SPIWrite(DIGIT0_REGISTER, int(int(drive_voltage) / 100 % 10));
  SPIWrite(DIGIT1_REGISTER, int(int(drive_voltage) / 10) % 10);
  SPIWrite(DIGIT2_REGISTER, int(int(drive_voltage) % 10));
}


// Gets the target temperature by reading our analog potentiometer.
// A read value of 0V (0%) corresponds to -25C, and a value of 5V (100%)
// corresponds to +65C
void getTargetTemperature(void) {
  total_data = 0;
  for(int i=0; i<SAMPLES_TO_AVERAGE; i++) {
    total_data += 1023 - analogRead(TSET_PIN);
  }
  
  raw_data = total_data / SAMPLES_TO_AVERAGE;
  fractional_maximum = raw_data / 1023.0;
  new_desired_temperature = TEMPERATURE_MIN + fractional_maximum * (TEMPERATURE_MAX - TEMPERATURE_MIN);
  
  // Add in a bit of hysteresis so that the display doesn't fluctuate
  if(abs(new_desired_temperature - desired_temperature) > 0.15) {
    desired_temperature = new_desired_temperature;
  }
}

void getTargetCurrent(void) {
  total_data = 0;
  for(int i=0; i<SAMPLES_TO_AVERAGE; i++) {
    total_data += 1023 - analogRead(TSET_PIN);
  }
  
  raw_data = total_data / SAMPLES_TO_AVERAGE;
  fractional_maximum = raw_data / 1023.0;
  new_desired_current = CURRENT_MIN + fractional_maximum * (CURRENT_MAX - CURRENT_MIN);
  
  // Add in a bit of hysteresis so that the display doesn't fluctuate
  if(abs(new_desired_current - desired_current) > CURRENT_MAX * 0.01) {
    desired_current = new_desired_current;
  }
}

void getTargetVoltage(void) {
  total_data = 0;
  for(int i=0; i<SAMPLES_TO_AVERAGE; i++) {
    total_data += 1023 - analogRead(TSET_PIN);
  }
  
  raw_data = total_data / SAMPLES_TO_AVERAGE;
  fractional_maximum = raw_data / 1023.0;
  drive_voltage = fractional_maximum * 255;
}

/* Measure the current flowing through the TIA using the voltage drop across
 * an 0.2Ohm sense resistor. It also filters the current.
 */
void measureCurrent(void) {
  int high_current_reading = analogRead(ISNS_HIGH);
  int low_current_reading = analogRead(ISNS_LOW);
  //Serial.println(high_current_reading - low_current_reading);
  measured_current = filter_coefficient * measured_current + 
    (1 - filter_coefficient)* (high_current_reading - low_current_reading)/1023.0 * 4.8 / 0.2;
}

/*
 * Implements a P-I controller for controlling the current.
 */
void controlCurrent(void) {
  current_error = desired_current - measured_current;

  // Implements PI control of our current
  drive_voltage += 255 / 5.0 * Zp *((1 + sampling_time / Ti )*current_error - previous_current_error); 
  
  //TEMPORARY HACK - REMOVE
  //drive_voltage = desired_current / CURRENT_MAX * 255;
  
  if(drive_voltage < 0) drive_voltage = 0;
  if(drive_voltage > 255) drive_voltage = 255;
  
  analogWrite(DRIVE_PIN, int(drive_voltage));
  previous_current_error = current_error;
}

void controlVoltage(void) {
  analogWrite(DRIVE_PIN, drive_voltage);
}
