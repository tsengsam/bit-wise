#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
const uint32_t D = 3;
#define M ((uint64_t)(UINT64_C(0xFFFFFFFFFFFFFFFF) / (D) + 1))

/*compute (n mod d) given precomputed M*/
uint32_t quickmod(uint32_t n) {
  uint64_t quotient = ((__uint128_t)M * n) >> 64;
  return n - quotient * D;
}

bool divisible(uint32_t n)
{
    uint64_t YYY = M-1;
    return n * M <= YYY;
}

void main()
{
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("%d\n", quickmod(n));
    if(divisible(n)) printf("%d is divisible.\n", n);
    else printf("%d isn't divisible.\n", n);
}
