#include <scpiparser.h>
bool remote_control = false;

class SCPI {
  public:
  static struct scpi_parser_context ctx;
  unsigned char read_length;
  static float current_temperature;
  static float desired_temperature;
  static char line_buffer[256];
  
  void initializeSCPI(void);

  static scpi_error_t identify(struct scpi_parser_context* context, struct scpi_token* command);
  static scpi_error_t reset(struct scpi_parser_context* context, struct scpi_token* command);
  static scpi_error_t fetch(struct scpi_parser_context* context, struct scpi_token* command);
  static scpi_error_t configure(struct scpi_parser_context* context, struct scpi_token* command);
  static scpi_error_t setTemperature(struct scpi_parser_context* context, struct scpi_token* command);
  static scpi_error_t setRemote(struct scpi_parser_context* context, struct scpi_token* command);
};

float SCPI::current_temperature = 0;
float SCPI::desired_temperature = 23;
char SCPI::line_buffer[256];
struct scpi_parser_context SCPI::ctx;
SCPI scpi;

scpi_error_t SCPI::identify(struct scpi_parser_context* context, struct scpi_token* command)
{
  Serial.println("Arduino Nano TEC Controller");
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::reset(struct scpi_parser_context* context, struct scpi_token* command)
{

  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::fetch(struct scpi_parser_context* context, struct scpi_token* command)
{
  //AD7766::synchronizationCounter = 0;
  Serial.print("#");
  Serial.print(SCPI::current_temperature);
  Serial.println("$");
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

scpi_error_t SCPI::setRemote(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args = command;
  struct scpi_numeric command_data;
  
  
  while(args != NULL && args->type == 0)
  {
    args = args->next;
  }
  command_data = scpi_parse_numeric(args->value, args->length, 0, 0, 10e6);
  if(command_data.value == 0){
    remote_control = false;
  }
  else if(command_data.value == 1) {
    remote_control = true;
  }
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}
scpi_error_t SCPI::configure(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args = command;
  struct scpi_numeric command_data;
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}
scpi_error_t SCPI::setTemperature(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args = command;
  struct scpi_numeric command_data;
  
  while(args != NULL && args->type == 0)
  {
    args = args->next;
  }
  command_data = scpi_parse_numeric(args->value, args->length, 0, 0, 10e6);
  desired_temperature = (float) command_data.value;
  
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}


void SCPI::initializeSCPI(void) {
  scpi_init(&ctx);
  struct scpi_command* cfg;

  scpi_register_command2(ctx.command_tree, SCPI_CL_SAMELEVEL, "*IDN?", identify);
  scpi_register_command2(ctx.command_tree, SCPI_CL_SAMELEVEL, "FETCH?", fetch);
  
  cfg = scpi_register_command2(ctx.command_tree, SCPI_CL_SAMELEVEL, "CONFIGURE", configure);
  scpi_register_command2(cfg, SCPI_CL_CHILD, "REMOTE", setRemote);
  scpi_register_command2(cfg, SCPI_CL_CHILD, "TEMPERATURE", setTemperature);
}
