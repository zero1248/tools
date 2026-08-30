#include <stdint.h>

#define TOHOST (*(volatile uint32_t *)0x10000000u)
#define GPIO   (*(volatile uint32_t *)0x10000004u)

int main(void)
{
    volatile uint32_t *ram = (volatile uint32_t *)0x00001000u;
    uint32_t sum = 0;
    for (uint32_t i = 1; i <= 10; ++i)
        sum += i;

    ram[0] = sum;
    GPIO = sum;
    TOHOST = (ram[0] == 55u) ? 1u : 0xffu;
    return 0;
}
