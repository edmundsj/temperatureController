#define OFFSET 0
#define ISNS_HIGH A0
#define OFFSET_CURRENT 12.0
#define CURRENT_SAFETY_LIMIT 7.0 // absolute maximum current
#define SHUTDOWN_CURRENT 5.0
#define ALT_PIN 6

#define SENSE_RESISTANCE 0.2
#define TEMPERATURE_MAX 65.0
#define TEMPERATURE_MIN -25.0
//#define TEMPERATURE_RANGE TEMPERATURE_MAX - TEMPERATURE_MIN // for some reason dividing by this does not work
#define SAMPLES_TO_AVERAGE 25
#define CURRENT_MAX 4.0
#define CURRENT_MIN -4.0
//#define CURRENT_RANGE CURRENT_MAX - CURRENT_MIN // for some reason dividing by this does not work.

#define TEMPERATURE_MODE 0
#define CURRENT_MODE 1
#define VOLTAGE_MODE 2

#define TSET_PIN A1
#define DRIVE_PIN 5
#define RELAY_PIN 7

#define TEMP_SENSOR_ADDRESS 0x18
#define TEMP_READ_REGISTER 0b0101

class Controller {
  public:
  Controller();
  uint8_t control_mode; // SCPI-settable / measurable
  bool heating_mode;

  float Kp = 70.0;
  float Kpc = 360.0; // Kp for cooling.
  float Ti_ms = 1100; // Integral time constant, in ms
  float Tic_ms = 1100; // Integral time constant going from hot->cold

  uint16_t sampling_time_ms = 20;
  
  float temperature_setpoint; // SCPI-settable / measurable
  float measured_temperature; // SCPI-measurable
  float temperature_error; 
  float previous_temperature_error;
  float filtered_temperature;
  
  float current_setpoint; // SCPI-settable / measurable
  float measured_current; // SCPI-measurable
  float current_error;
  float previous_current_error;
  float filtered_current;

  float fractional_error;
  float previous_fractional_error;

  int voltage_setpoint; // SCPI-settable/measurable

  float drive_voltage; // Actual voltage being applied to the pin
  
  float filter_coefficient;

  float temperature_accuracy; // SCPI settable/gettable

  void measure(void); 
  void measure_current(void);
  void measure_temperature(void);
  
  void control(void);
  void control_current(void);
  void control_temperature(void);
  void control_voltage(void);
  
  void get_potentiometer_setpoint(void);
  int get_potentiometer_voltage(void);
  float get_potentiometer_current(void);
  float get_potentiometer_temperature(void);

  void reset(void);

  MCP9808 sensor;
};

Controller::Controller(void) {
  MCP9808 sensor;
  this->sensor = sensor;
  this->heating_mode = false;
  this->control_mode = TEMPERATURE_MODE;
  this->temperature_setpoint = 23.0;
  this->temperature_error = 0;
  this->previous_temperature_error = 0;
  this->measured_current = 0;
  this->current_setpoint = 0;
  this->current_error = 0;
  this->previous_current_error = 0;
  this->filter_coefficient = 0.9;
  this->sampling_time_ms = 50;
  this->voltage_setpoint = 0;
  this->temperature_accuracy = 0.2;
}

void Controller::reset(void) {
  this->heating_mode = false;
  this->control_mode = TEMPERATURE_MODE;
  this->temperature_setpoint = 23.0;
  this->temperature_error = 0;
  this->previous_temperature_error = 0;
  this->measured_current = 0;
  this->current_setpoint = 0;
  this->current_error = 0;
  this->previous_current_error = 0;
  this->filter_coefficient = 0.9;
  this->sampling_time_ms = 50;
  this->voltage_setpoint = 0;
}

////////////// BEGIN CONTROL FUNCTIONS //////////////

void Controller::control(void) {
  this->measure_temperature();
  this->measure_current();

  if(this->control_mode == VOLTAGE_MODE) {
    this->control_voltage();
  }
  else if(this->control_mode == CURRENT_MODE) {
    this->fractional_error = this->current_error / (CURRENT_MAX - CURRENT_MIN);
    this->previous_fractional_error = this->previous_current_error / (CURRENT_MAX - CURRENT_MIN);
    this->control_current();
  }
  else if(this->control_mode == TEMPERATURE_MODE) {
    this->fractional_error = this->temperature_error / (TEMPERATURE_MAX - TEMPERATURE_MIN);
    this->previous_fractional_error = this->previous_temperature_error / (TEMPERATURE_MAX - TEMPERATURE_MIN);
    this->control_temperature();
  }

  if(this->drive_voltage < -255) this->drive_voltage = -255;
  if(this->drive_voltage > 255) this->drive_voltage = 255;
  
  if (this->drive_voltage <= 0) this->heating_mode = false;
  else if(this->drive_voltage > 0) this->heating_mode = true;

  if(this->heating_mode == false) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }

  if(abs(measured_current) < CURRENT_SAFETY_LIMIT) {
     analogWrite(DRIVE_PIN, int(abs(this->drive_voltage)));
  }
  else { // safety shutdown
    //analogWrite(DRIVE_PIN, 0);
  }
}

void Controller::control_temperature(void) {
  
  if(this->drive_voltage <= 0) { // We are actuating the cooling action of the TEC. Cooling dynamics are relevant
    this->drive_voltage += this->Kpc*((1 + this->sampling_time_ms / this->Tic_ms)*this->fractional_error - this->previous_fractional_error);
  }
  else if(this->drive_voltage > 0) { // We are actuating the heating action of the TEC. Heating dynamics are relevant
    this->drive_voltage += this->Kp*((1 + this->sampling_time_ms / this->Ti_ms)*this->fractional_error - this->previous_fractional_error);
  }
}


/*Implements a P-I controller for controlling the current. Currently only uni-directional: need to update. */
void Controller::control_current(void) {
  if(this->drive_voltage <= 0) { // We are actuating the cooling action of the TEC. Cooling dynamics are relevant
    this->drive_voltage += this->Kpc*((1 + this->sampling_time_ms / this->Tic_ms)*this->fractional_error - this->previous_fractional_error);
  }
  else if(this->drive_voltage > 0) { // We are actuating the heating action of the TEC. Heating dynamics are relevant
    this->drive_voltage += this->Kp*((1 + this->sampling_time_ms / this->Ti_ms)*this->fractional_error - this->previous_fractional_error);
  }
}

void Controller::control_voltage(void) {
  this->drive_voltage = this->voltage_setpoint;
}

////////////// BEGIN MEASUREMENT FUNCTIONS //////////////

void Controller::measure_temperature(void) {
  this->previous_temperature_error = this->temperature_error;
  
  this->sensor.get_temp(&this->measured_temperature);
  
  this->temperature_error = this->temperature_setpoint - this->measured_temperature;
  this->filtered_temperature = this->filter_coefficient * this->filtered_temperature +
    (1 - this->filter_coefficient) * this->measured_temperature;
}

/* Measure the current flowing through the TIA using the voltage drop across
 * an 0.2Ohm sense resistor. It also filters the current.
 */
void Controller::measure_current(void) {
  this->previous_current_error = this->current_error;
  
  int voltage_drop_reading = analogRead(ISNS_HIGH) - 0; // Our 'LOW' point is ground. Makes life easy.
  float voltage = voltage_drop_reading * 4.8 / 1023.0; // Approximate real voltage measured
  this->measured_current = voltage / SENSE_RESISTANCE - OFFSET_CURRENT;
  
  this->current_error = this->current_setpoint - this->measured_current;
  this->filtered_current = this->filter_coefficient * this->filtered_current + 
    (1 - this->filter_coefficient) * this->measured_current;
}



////////////// BEGIN POTENTIOMETER FUNCTIONS //////////////
/*
 * Measures the setpoint from a potentiometer given the mode of the controller
 */
void Controller::get_potentiometer_setpoint(void) {
  if (this->control_mode == VOLTAGE_MODE) {
    this->voltage_setpoint = this->get_potentiometer_voltage();
  }
  else if (this->control_mode == CURRENT_MODE) {
    this->current_setpoint = this->get_potentiometer_current();
  }
  else if (this->control_mode == TEMPERATURE_MODE) {
    this->temperature_setpoint = this->get_potentiometer_temperature();
  }
}

float Controller::get_potentiometer_temperature(void) {
  float total_data = 0;
  for(int i=0; i<SAMPLES_TO_AVERAGE; i++) {
    total_data += 1023 - analogRead(TSET_PIN);
  }
  
  float fractional_maximum = (total_data / SAMPLES_TO_AVERAGE) / 1023.0;
  float new_temperature_setpoint = TEMPERATURE_MIN + fractional_maximum * (TEMPERATURE_MAX - TEMPERATURE_MIN);
  
  // Add in a bit of hysteresis so that the display doesn't fluctuate
  if(abs(new_temperature_setpoint - this->temperature_setpoint) < 0.15) {
    new_temperature_setpoint = this->temperature_setpoint;
  }
  return new_temperature_setpoint;
}

float Controller::get_potentiometer_current(void) {
  float total_data = 0;
  for(int i=0; i<SAMPLES_TO_AVERAGE; i++) {
    total_data += 1023 - analogRead(TSET_PIN);
  }
  
  float fractional_maximum = (total_data / SAMPLES_TO_AVERAGE) / 1023.0;
  float new_desired_current = CURRENT_MIN + fractional_maximum * (CURRENT_MAX - CURRENT_MIN);
  
  // Add in a bit of hysteresis so that the display doesn't fluctuate
  if(abs(new_desired_current - this->current_setpoint) <= ( CURRENT_MAX - CURRENT_MIN) * 0.01) {
     new_desired_current = this->current_setpoint;
  }
  return new_desired_current;
}

int Controller::get_potentiometer_voltage(void) {
  int total_data = 0;
  for(int i=0; i<SAMPLES_TO_AVERAGE; i++) {
    total_data += 1023 - analogRead(TSET_PIN);
  }
  
  float fractional_maximum = (total_data / SAMPLES_TO_AVERAGE) / 1023.0;
  int drive_voltage = (int) (fractional_maximum * 255);
  return drive_voltage;
}
