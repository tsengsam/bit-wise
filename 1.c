#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define PACKED_BYTE(b) (((uint64_t)(b) & (0xff)) * 0x0101010101010101u)

/*bool is_ascii(const char str[], size_t size)
{
    if (size == 0) return false;

    for (int i = 0; i<size; i++) {
        if (str[i] & 0x80) return false;
    }
    return true;
}*/

bool is_ascii(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);
        uint64_t MMM = 0x8080808080808080;
        if (payload & MMM)
            return false;
        i += 8;
    }
    while (i < size) {
        if (str[i] & 0x80)
            return false;
        i++;
    }
    return true;
}

bool is_alphabet(char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
	memcpy(&payload, str + i, 8);
	uint64_t A = payload + PACKED_BYTE(128 - 'A');
	uint64_t Z = payload + PACKED_BYTE(127 - 'Z');
	uint64_t upper_mask = (A^Z) & PACKED_BYTE(0x80);/*If one byte is 80 then the corresponding character is upper alphabet*/
	uint64_t a = payload + PACKED_BYTE(128 - 'a');
	uint64_t z = payload + PACKED_BYTE(127 - 'z' );
	uint64_t lowwer_mask = (a ^ z) & PACKED_BYTE(0x80);
	if ((upper_mask | lowwer_mask) ^ PACKED_BYTE(0x80))
	    return false;
	i += 8;
    }

    for (; i<size; i++) {
        if (str[i] < 65 || str[i] > 122 || (str[i] > 90 && str[i] < 97))
	    return false;
    }

    return true;

}

int main()
{
    char str[] = "as12!@[}~~";
    char str2[] = "Aaasdf@asi";
    printf("str = %s\n", str);
    if (is_ascii(str, 10)) {
        printf("All valid\n");
    } else {
        printf("Not all valid\n");
    }

    printf("\nstr2 = %s\n", str2);
    if (is_alphabet(str2, 10)) {
        printf("All character are alphabets\n");
    } else {
        printf("Ohh, there are some other character.\n");
    }
        

    return 0;
}
