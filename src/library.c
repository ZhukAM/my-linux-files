#include <stddef.h>
#include <string.h>
#include "library.h"

int stringStat(const char *string, size_t multiplier, int *count)
{
   (*count)++;
   return multiplier * strlen(string);;   
}

