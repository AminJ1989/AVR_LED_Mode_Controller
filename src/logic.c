
#include "../include/logic.h"

Mode mode(bool Switch)
{
    return Switch ? Red : Green_Blue;
}

State Led_state(Mode m)
{
    State s = {false, false, false};

    if (m == Red) {
        s.red = true;
    } else {
        s.blue = true;
        s.green = true;
    }

    return s;
}
