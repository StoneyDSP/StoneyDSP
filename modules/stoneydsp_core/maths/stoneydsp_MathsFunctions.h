/***************************************************************************//**
 * @file stoneydsp_MathsFunctions.h
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 1.0.0
 * @date 2024-02-21
 *
 * @copyright Copyright (c) 2024
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************/

namespace StoneyDSP
{
/** @addtogroup StoneyDSP
 *  @{
 */

namespace Maths
{
/** @addtogroup Maths
 *  @{
 */

/**
 * @brief Commonly used mathematical functions.
 *
*/
template <typename FloatType>
struct Functions
{
    /**
     * @brief Returns the value of 1.0L / x.
     *
    */
    static FloatType oneDivX(FloatType x)
    {
        return static_cast<FloatType> (1 / x);
    }

    /**
     * @brief Returns the value of 1.0L / x.
     *
    */
    static FloatType oneDivX(const FloatType& x)
    {
        return static_cast<FloatType> (1 / x);
    }
};

  /// @} group Maths
} // namespace Maths

  /// @} group StoneyDSP
} // namespace StoneyDSP
