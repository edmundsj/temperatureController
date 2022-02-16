#include "Vrekrer_scpi_parser.h"
#include "controller.h"

class SCPI {
  public: // methods
  void initialize(void);
  static void identify(SCPI_C, SCPI_P, Stream&);
  static void reset(SCPI_C, SCPI_P, Stream&);
  
  static void set_remote_control(SCPI_C, SCPI_P, Stream&);
  static void get_remote_control(SCPI_C, SCPI_P, Stream&);
  static void set_control_mode(SCPI_C, SCPI_P, Stream&);
  static void get_control_mode(SCPI_C, SCPI_P, Stream&);
  
  static void set_temperature_setpoint(SCPI_C, SCPI_P, Stream&);
  static void get_temperature_setpoint(SCPI_C, SCPI_P, Stream&);
  static void set_current_setpoint(SCPI_C, SCPI_P, Stream&);
  static void get_current_setpoint(SCPI_C, SCPI_P, Stream&);
  static void set_voltage_setpoint(SCPI_C, SCPI_P, Stream&);
  static void get_voltage_setpoint(SCPI_C, SCPI_P, Stream&);
  
  static void get_temperature(SCPI_C, SCPI_P, Stream&);
  static void get_temperature_error(SCPI_C, SCPI_P, Stream&);
  static void get_current(SCPI_C, SCPI_P, Stream&);
  static void get_current_error(SCPI_C, SCPI_P, Stream&);
  static void get_voltage(SCPI_C, SCPI_P, Stream&);

  static void measure_temperature(SCPI_C, SCPI_P, Stream&);
  static void measure_current(SCPI_C, SCPI_P, Stream&);

  static void get_ready(SCPI_C, SCPI_P, Stream&);
  
  static SCPI_Parser parser;

  // variables
  static bool remote_control;
  static Controller controller;
  
  private:
  
};

static bool SCPI::remote_control = false;
static SCPI_Parser SCPI::parser;
static Controller SCPI::controller;

static void SCPI::identify(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(F("Arduino Nano TEC Controller"));
}

static void SCPI::reset(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  SCPI::remote_control = false;
  SCPI::controller.reset();
}

static void SCPI::set_remote_control(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  if (parameters.Size() > 0) {
    SCPI::remote_control = (bool) (String(parameters[0]).toInt());
  }
}

static void SCPI::get_remote_control(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  if (SCPI::remote_control == true) {
    interface.println('1');
  }
  else if (SCPI::remote_control == false) {
    interface.println('0');
  }
}

static void SCPI::set_control_mode(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  if (parameters.Size() > 0) {
    String control_mode = parameters[0];
    if(control_mode == "voltage") {
      SCPI::controller.control_mode = VOLTAGE_MODE;
    }
    else if (control_mode == "current") {
      SCPI::controller.control_mode = CURRENT_MODE;
    }
    else if (control_mode == "temperature") {
      SCPI::controller.control_mode = TEMPERATURE_MODE;
    }
    
  }
  else if (SCPI::remote_control == false) {
    interface.println('0');
  }
}

static void SCPI::get_control_mode(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  if (SCPI::controller.control_mode == VOLTAGE_MODE) {
    interface.println("voltage");
  }
  else if (SCPI::controller.control_mode == CURRENT_MODE) {
    interface.println("current");
  }
  else if (SCPI::controller.control_mode == TEMPERATURE_MODE) {
    interface.println("temperature");
  }
}

// BEGIN SETPOINT METHODS //

static void SCPI::set_voltage_setpoint(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  if (parameters.Size() > 0) {
    SCPI::controller.voltage_setpoint = String(parameters[0]).toInt();
  }
}

static void SCPI::get_voltage_setpoint(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(SCPI::controller.voltage_setpoint);
}

static void SCPI::set_current_setpoint(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  if (parameters.Size() > 0) {
    SCPI::controller.current_setpoint = String(parameters[0]).toFloat();
  }
}

static void SCPI::get_current_setpoint(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(SCPI::controller.current_setpoint);
}

static void SCPI::set_temperature_setpoint(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  if (parameters.Size() > 0) {
    SCPI::controller.temperature_setpoint = String(parameters[0]).toFloat();
  }
}

static void SCPI::get_temperature_setpoint(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(SCPI::controller.temperature_setpoint);
}

// BEGIN MEASUREMENT METHODS 
static void SCPI::get_temperature(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(SCPI::controller.measured_temperature);
}

static void SCPI::get_temperature_error(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(SCPI::controller.temperature_error);
}

static void SCPI::get_current(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(SCPI::controller.measured_current);
}

static void SCPI::get_current_error(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(SCPI::controller.current_error);
}

static void SCPI::get_voltage(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(SCPI::controller.drive_voltage);
}

static void SCPI::measure_temperature(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  float temp = 0;
  SCPI::controller.sensor.get_temp(&temp);
  interface.println(temp);
}

static void SCPI::measure_current(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  int voltage_drop_reading = analogRead(ISNS_HIGH) - 0; // Our 'LOW' point is ground. Makes life easy.
  float voltage = voltage_drop_reading * 4.8 / 1023.0; // Approximate real voltage measured
  float measured_current = voltage / SENSE_RESISTANCE - OFFSET_CURRENT;
  interface.println(measured_current);
}

static void SCPI::get_ready(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  if(abs(SCPI::controller.temperature_error) < 0.2) {
    interface.println("1");
  }
  else {
    interface.println("0");
  }
}


void SCPI::initialize(void){
  SCPI::parser.RegisterCommand("*IDN?", &SCPI::identify);
  SCPI::parser.RegisterCommand("REMOTE?", &SCPI::get_remote_control);
  SCPI::parser.RegisterCommand("REMOTE", &SCPI::set_remote_control);
  SCPI::parser.RegisterCommand("*RST", &SCPI::reset);
  SCPI::parser.RegisterCommand("MODE?", &SCPI::get_control_mode);
  SCPI::parser.RegisterCommand("MODE", &SCPI::set_control_mode);
  SCPI::parser.RegisterCommand("READY?", &SCPI::get_ready);
  SCPI::parser.RegisterCommand("TEMPERATURE?", &SCPI::get_temperature);
  SCPI::parser.RegisterCommand("TEMPERATURE:ERROR?", &SCPI::get_temperature_error);
  SCPI::parser.RegisterCommand("CURRENT?", &SCPI::get_current);
  SCPI::parser.RegisterCommand("CURRENT:ERROR?", &SCPI::get_current_error);
  SCPI::parser.RegisterCommand("VOLTAGE?", &SCPI::get_voltage);
  SCPI::parser.SetCommandTreeBase("SOURCE");
  SCPI::parser.RegisterCommand(":VOLTAGE", &SCPI::set_voltage_setpoint);
  SCPI::parser.RegisterCommand(":VOLTAGE?", &SCPI::get_voltage_setpoint);
  SCPI::parser.RegisterCommand(":CURRENT", &SCPI::set_current_setpoint);
  SCPI::parser.RegisterCommand(":CURRENT?", &SCPI::get_current_setpoint);
  SCPI::parser.RegisterCommand(":TEMPERATURE", &SCPI::set_temperature_setpoint);
  SCPI::parser.RegisterCommand(":TEMPERATURE?", &SCPI::get_temperature_setpoint);

  //SCPI::parser.RegisterCommand(":ACCURACY?", &SCPI::get_accuracy);
 // SCPI::parser.RegisterCommand(":ACCURACY", &SCPI::set_accuracy);
  SCPI::parser.SetCommandTreeBase("MEASURE");
  SCPI::parser.RegisterCommand(":TEMPERATURE?", &SCPI::measure_temperature);
  SCPI::parser.RegisterCommand(":CURRENT?", &SCPI::measure_current);
  
  SCPI::controller.sensor.init();
}

SCPI scpi;
