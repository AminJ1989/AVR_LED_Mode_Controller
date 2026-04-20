
#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    Red,
    Green_Blue
} Mode;

typedef struct
{
    bool red;
    bool green;
    bool blue;
} State;

Mode mode(bool Switch);
State Led_state(Mode m);

#endif
