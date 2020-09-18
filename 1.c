#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
/*bool is_ascii(const char str[], size_t size)
{
    if (size == 0) return false;

    for (int i = 0; i<size; i++) {
        if (str[i] & 0x80) return false;
    }
    return true;
}*/

/* Check the whole string in a time
 * size of string
 *
 *
 */
bool is_ascii(const char str[], size_t size) {
  if (size == 0)
    return false;
  int i = 0;
  while ((i + 8) <= size) {
    uint64_t payload;
    memcpy(&payload, str + i, 8);
    uint64_t MMM = 0x8080808080808080;
    if (payload & MMM)
      return false;
    i++;
  }
  while (i < size) {
    if (str[i] & 0x80)
      return false;
    i++;
  }
  return true;
}
int main()
{
  char s[] = "abc*®+_|]";
  if (is_ascii(s, 11)) {
    printf("all characters valid\n");
  } else {
    printf("Not all valid\n");
  }
  return 0;
}