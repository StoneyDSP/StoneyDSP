#include <stoneydsp/core/core.h>

int main (void)
{
  const stoneydsp_float_t value = stoneydsp_float_c (1.0F);
  return value == stoneydsp_float_lowest () ? 1 : 0;
}
