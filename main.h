#ifndef MAIN_H_
#define MAIN_H_


typedef enum {
    CMD_POWER,
    CMD_TURNING
} cmd_type_t;

typedef struct {
    cmd_type_t type;
    int8_t value;
} cmd_t;

static void handle_command(cmd_t * cmd);
static void read_serial_command(cmd_t * cmd);

#endif
