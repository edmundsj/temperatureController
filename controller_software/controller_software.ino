#include <SPI.h>
#include "Seeed_MCP9808.h"
#include "displays.h"
#include <elapsedMillis.h>
#include "nano_scpi.h"

elapsedMillis display_time_elapsed;
elapsedMillis measurement_time_elapsed;

#define TSET_PIN A1
#define DRIVE_PIN 5
#define RELAY_PIN 7

#define TEMP_SENSOR_ADDRESS 0x18
#define TEMP_READ_REGISTER 0b0101

#define OFFSET 0
#define ISNS_HIGH A0
#define OFFSET_CURRENT 12.0
#define CURRENT_SAFETY_LIMIT 7.0 // absolute maximum current
#define SHUTDOWN_CURRENT 5.0

#define SENSE_RESISTANCE 0.2
#define TEMPERATURE_MAX 65
#define TEMPERATURE_MIN -25
#define SAMPLES_TO_AVERAGE 25
#define CURRENT_MAX 4
#define CURRENT_MIN 0


#define MEASUREMENT_PERIOD 50

bool heat_mode = true;
uint8_t command_byte = 0;
uint8_t data_byte = 0;

float new_desired_temperature = 23.0;
float desired_temperature = 23.0;
float temperature_error = 0;
float previous_temperature_error = 0;
uint16_t raw_data = 0;
uint32_t total_data = 0;
float fractional_maximum = 0.0;
float measured_current = 0.0;
float desired_current = 0.25;
float current_error = 0;
float previous_current_error = 0;
float new_desired_current = 0;
float drive_voltage = 0.0;
float filter_coefficient = 0.9; // zero is equivalent to no filter, 1 is an infinite time filter.
uint16_t sampling_time_ms = 20;
float filtered_current = 0;

float Kp = 0.778;
float Kpc = 2.0; // Kp for cooling.
float Ti_ms = 1100; // Integral time constant, in ms
float Tic_ms = 2900; // Integral time constant going from hot->cold

float measured_temperature = 0;
bool heating_mode = true;

MCP9808 sensor;

Display setpoint_display(DIGIT0_REGISTER, DIGIT1_REGISTER, DIGIT2_REGISTER);
Display actual_display(DIGIT3_REGISTER, DIGIT4_REGISTER, DIGIT5_REGISTER);

void setup() {
  // put your setup code here, to run once:
  pinMode(CHIP_SELECT_PIN, OUTPUT);
  pinMode(DRIVE_PIN, OUTPUT);
  pinMode(TSET_PIN, INPUT);
  pinMode(ISNS_HIGH, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
    
  SPI.begin();
  Serial.begin(115200);

  // Setup the tempertature sensor interface
  
  if(sensor.init())
    {
        Serial.println("sensor init failed!!");
    }
    //Serial.println("sensor init!!");
    initializeDisplayDriver();
  scpi.initializeSCPI();
}

void loop() {
  if(heating_mode == false) digitalWrite(RELAY_PIN, LOW);
  else digitalWrite(RELAY_PIN, HIGH);
  
        
    if(measurement_time_elapsed > MEASUREMENT_PERIOD) {
      measured_current = measureCurrent();
      previous_temperature_error = temperature_error;
      measured_temperature = measureTemperature();
      temperature_error = desired_temperature - measured_temperature;
      
      controlTemperature();
      measurement_time_elapsed = 0;
      
    if(display_time_elapsed > DISPLAY_REFRESH_PERIOD) {
      if(remote_control == false) { 
        desired_temperature = getTargetTemperature();
      }
      else {
        desired_temperature = SCPI::desired_temperature;
      }
      
      setpoint_display.writeTemperature(desired_temperature);
      actual_display.writeTemperature(measured_temperature);
      display_time_elapsed = 0;
    }    
  }
  if(Serial.available()) {
    int read_length = Serial.readBytesUntil('\n', SCPI::line_buffer, 256);
    if(read_length > 0) {
        scpi_execute_command(&SCPI::ctx, SCPI::line_buffer, read_length);
    }
  }
}


// Gets the target temperature by reading our analog potentiometer.
// A read value of 0V (0%) corresponds to -25C, and a value of 5V (100%)
// corresponds to +65C
float getTargetTemperature(void) {
  total_data = 0;
  for(int i=0; i<SAMPLES_TO_AVERAGE; i++) {
    total_data += 1023 - analogRead(TSET_PIN);
  }
  
  raw_data = total_data / SAMPLES_TO_AVERAGE;
  fractional_maximum = raw_data / 1023.0;
  new_desired_temperature = TEMPERATURE_MIN + fractional_maximum * (TEMPERATURE_MAX - TEMPERATURE_MIN);
  
  // Add in a bit of hysteresis so that the display doesn't fluctuate
  if(abs(new_desired_temperature - desired_temperature) < 0.15) {
    new_desired_temperature = desired_temperature;
  }
  return new_desired_temperature;
}

void getTargetCurrent(void) {
  total_data = 0;
  for(int i=0; i<SAMPLES_TO_AVERAGE; i++) {
    total_data += 1023 - analogRead(TSET_PIN);
  }
  
  raw_data = total_data / SAMPLES_TO_AVERAGE;
  fractional_maximum = raw_data / 1023.0;
  new_desired_current = fractional_maximum * CURRENT_MAX;
  
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
float measureCurrent(void) {
  previous_current_error = current_error;
  int high_current_reading = analogRead(ISNS_HIGH);
  int delta_reading = high_current_reading;
  float voltage = delta_reading * 4.8 / 1023.0;
  float current = voltage / SENSE_RESISTANCE - OFFSET_CURRENT;
  current_error = desired_current - current;
  filtered_current = filter_coefficient * filtered_current + (1 - filter_coefficient) * current;
  return current;
}

float measureTemperature(void) {
  
  float temp=0;
  //Get temperature ,a float-form value.
  sensor.get_temp(&temp);
  SCPI::current_temperature = temp;
  return temp;
}

/*
 * Implements a P-I controller for controlling the current.
 */
void controlCurrent(void) {
  current_error = desired_current - measured_current;
  if(measured_current < CURRENT_SAFETY_LIMIT) {
    // Implements PI control of our current
    drive_voltage += Kp*((1 + sampling_time_ms / Ti_ms )*current_error - previous_current_error); 
    
    if(drive_voltage < 0) drive_voltage = 0;
    if(drive_voltage > 255) drive_voltage = 255;
    
    analogWrite(DRIVE_PIN, int(drive_voltage));
    previous_current_error = current_error;
  } else if(measured_current > SHUTDOWN_CURRENT) { // emergency shutdown due to over-current
    drive_voltage = 0;
    analogWrite(DRIVE_PIN, 0);
  }
}

void controlTemperature(void) {
  float increase_amount = 0;
  if(drive_voltage <= 0) { // We are actuating the cooling action of the TEC. Cooling dynamics are relevant
    heating_mode = false;
    increase_amount = Kpc*((1 + sampling_time_ms / Tic_ms)*temperature_error - previous_temperature_error);
  }
  else if(drive_voltage > 0) { // We are actuating the heating action of the TEC. Heating dynamics are relevant
    heating_mode = true;
    increase_amount = Kp*((1 + sampling_time_ms / Ti_ms)*temperature_error - previous_temperature_error);
  }
  
  if(measured_current < CURRENT_SAFETY_LIMIT) {
    drive_voltage += increase_amount;
    if(drive_voltage < -255) drive_voltage = -255;
    if(drive_voltage > 255) drive_voltage = 255;
    analogWrite(DRIVE_PIN, int(abs(drive_voltage)));
  }
}

void controlVoltage(uint8_t voltage_pwm) {
  analogWrite(DRIVE_PIN, voltage_pwm);
}
