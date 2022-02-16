#include <SPI.h>
#include "Seeed_MCP9808.h"
#include "displays.h"
#include <elapsedMillis.h>
#include "nano_scpi_2.h"

elapsedMillis display_time_elapsed;
elapsedMillis measurement_time_elapsed;

Display setpoint_display(DIGIT0_REGISTER, DIGIT1_REGISTER, DIGIT2_REGISTER);
Display actual_display(DIGIT3_REGISTER, DIGIT4_REGISTER, DIGIT5_REGISTER);

void setup() {
  // put your setup code here, to run once:
  pinMode(CHIP_SELECT_PIN, OUTPUT);
  pinMode(DRIVE_PIN, OUTPUT);
  pinMode(TSET_PIN, INPUT);
  pinMode(ISNS_HIGH, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(ALT_PIN, INPUT);
    
  SPI.begin();
  Serial.begin(115200);

  // Setup the tempertature sensor interface
  initializeDisplayDriver();
  scpi.initialize();
}

void loop() {
  if(measurement_time_elapsed > SCPI::controller.sampling_time_ms) {
    SCPI::controller.control(); // chooses between temp, current, and voltage
    measurement_time_elapsed = 0;
  }

  if(display_time_elapsed > DISPLAY_REFRESH_PERIOD) {
    if(SCPI::remote_control == false) { 
      SCPI::controller.get_potentiometer_setpoint(); // gets the setpoint based on the current mode
    }
    
    setpoint_display.writeTemperature(SCPI::controller.temperature_setpoint);
    actual_display.writeTemperature(SCPI::controller.measured_temperature);
    display_time_elapsed = 0;
  }    
  if(Serial.available()) {
    SCPI::parser.ProcessInput(Serial, "\n");
  }
}
