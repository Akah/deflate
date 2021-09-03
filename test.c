#include "test.h"

int t_run = 0;
int t_pass = 0;

bool failed = false;

void result() {
    printf("[%d/%d] tests passed\n", t_pass, t_run);
}

void run_tests()
{
    // __check();

    result();
}
