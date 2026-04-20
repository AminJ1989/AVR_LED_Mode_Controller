
#include <assert.h>
#include "../include/logic.h"
#include <stdio.h>

static void test_mode(void)
{
    assert(mode(false) == Green_Blue);
    assert(mode(true) == Red);
}

static void test_led_state(void)
{
    State s;

    s = Led_state(Red);
    assert(s.red == true);
    assert(s.green == false);
    assert(s.blue == false);

    s = Led_state(Green_Blue);
    assert(s.red == false);
    assert(s.green == true);
    assert(s.blue == true);
}

int main(void)
{
    test_mode();
    test_led_state();
    printf("All tests passed\n");
    return 0;
}