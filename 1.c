#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define PACKED_BYTE(b) (((uint64_t)(b) & (0xff)) * 0x0101010101010101u)

bool is_ascii(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    for (; i + 8 <= size; i += 8) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);
        if (payload & PACKED_BYTE(0x80))
            return false;
    }

    while (i < size) {
        if (str[i] & 0x80)
            return false;
        i++;
    }
    return true;
}

bool is_alphabet(const char str[], size_t size)
{
    if (size == 0)
        return false;

    int i = 0;
    while (i + 8 <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);

        uint64_t A = payload + PACKED_BYTE(128 - 'A');
        uint64_t Z = payload + PACKED_BYTE(127 - 'Z');
        uint64_t upper_mask =
            (A ^ Z) & PACKED_BYTE(0x80); /*Should be PACKED_BYTE(0x80) */
        uint64_t a = payload + PACKED_BYTE(128 - 'a');
        uint64_t z = payload + PACKED_BYTE(127 - 'z');
        uint64_t lower_mask =
            (a ^ z) & PACKED_BYTE(0x80); /*Should be PACKED_BYTE(0x80), too*/
        if ((upper_mask | lower_mask) ^ PACKED_BYTE(0x80))
            return false;
        i += 8;
    }

    while (i < size) {
        if (str[i] < 65 || str[i] > 122 || (str[i] > 90 && str[i] < 97))
            return false;
        i++;
    }
    return true;
}

int main()
{
    char str[] = "qqqqqa®sd123";
    char str2[] = "figil@gbjhdub";
    if (is_ascii(str, strlen(str))) {
        printf("All valid.\n");
    }else {
        printf("Not all valid.\n");
    }

    if (is_alphabet(str2, strlen(str2))) {
        printf("All are alphabet~.\n");
    }
    else {
        printf("Not all alphabet...\n");
    }
}
