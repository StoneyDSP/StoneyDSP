#include <stoneydsp/core/core.h>

int main (void)
{
  const stoneydsp_float_t value = stoneydsp_float_c (1.0F);
  const stoneydsp_float_t one_bit_gain
      = stoneydsp_float_bits_to_gain (stoneydsp_float_c (1.0F));
  const stoneydsp_double_t unity_decibels
      = stoneydsp_double_gain_to_decibels (stoneydsp_double_c (1.0));

  return value == stoneydsp_float_lowest () || one_bit_gain != 2.0F
                 || unity_decibels != 0.0
             ? 1
             : 0;
}
