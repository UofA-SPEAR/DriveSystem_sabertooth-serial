#ifndef MAIN_H_
#define MAIN_H_

#define SIDE_RIGHT  'R'
#define SIDE_LEFT   'L'
#define SIDE_TOP    'T'
#define SIDE_BOTTOM 'B'

#define WHEEL_TOP_LEFT     'Q'
#define WHEEL_TOP_RIGHT    'W'
#define WHEEL_BOTTOM_LEFT  'A'
#define WHEEL_BOTTOM_RIGHT 'S'

typedef struct {
    char side;
    int8_t value;
} cmd_t;

typedef enum {
    CMD_SUCCESS,
    CMD_ERR_INVALID,
} cmd_err_t;

static void handle_timeout(void);
static void handle_command(cmd_t * cmd);
static cmd_err_t read_serial_command(cmd_t * cmd);

#endif
