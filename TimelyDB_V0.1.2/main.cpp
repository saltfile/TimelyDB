#include "_startup.h"



//
int main() {
    if (CONFIG_INIT() < 0)
        return -10;
    return 1;
}
