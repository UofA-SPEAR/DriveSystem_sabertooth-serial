#ifndef MAIN_H_
#define MAIN_H_

#define SIDE_RIGHT  'R'
#define SIDE_LEFT   'L'

typedef struct {
    char side;
    int8_t value;
} cmd_t;

static void handle_command(cmd_t * cmd);
static void read_serial_command(cmd_t * cmd);

#endif
