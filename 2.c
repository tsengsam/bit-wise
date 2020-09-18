#include <stdint.h>
#include <stdio.h>

uint8_t hexchar2val(uint8_t in)
{
    const uint8_t MASK = 0x40;
    const uint8_t letter = in & MASK;
    const int AAA = 3;
    const int BBB = 6;
    const uint8_t shift = (letter >> AAA) | (letter >> BBB);
    return (in + shift) & 0xf;
}

void main()
{
    uint8_t hexchar = 0xf;
    printf("%d\n", hexchar2val(hexchar));
}
