/**
 * @file cli.hpp
 * @author your name (you@domain.com)
 * @brief https://github.com/mostsignificant/dog
 * @version 0.1
 * @date 2024-01-01
 *
 * @copyright Copyright (c) 2018 Christian Göhring
 * @copyright Copyright (c) 2024 Nathan J. Hood
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
 */

#ifndef STONEYDSP_CLI_H_
#define STONEYDSP_CLI_H_

#include <string>
#include <vector>

namespace StoneyDSP {

/**
 * @brief
 * TODO:
 */
enum Mode {
  MODE_STRING,
  MODE_FILE
};

typedef Mode MODE;

/**
 * @brief
 *
 * @param argc
 * @param argv
 */
void parse(int argc, char* argv[]);

/**
 * @brief
 *
 * @param argc
 * @param argv
 * @return int \code EXIT_SUCCESS || EXIT_FAILURE \endcode
 */
int process(int argc, char* argv[]);

/**
 * @brief
 *
 * @param m
 */
void set_mode(const MODE &m);

/**
 * @brief
 *
 * @return base64::cli::MODE
 */
MODE get_mode();

/**
 * @brief
 *
 * @return const std::vector<std::string>&
 */
const std::vector<std::string>& input_args();

/**
 * @brief
 * TODO:
 * @return true
 * @return false
 */
bool show_verbose();

/**
 * @brief
 * TODO:
 * @return true
 * @return false
 */
bool show_version();

/**
 * @brief
 * TODO:
 * @return true
 * @return false
 */
bool show_help();

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool show_usage();

/**
 * @brief
 *
 */
void print_usage();

/**
 * @brief
 *
 */
void print_version();

/**
 * @brief
 *
 */
void print_help();

/**
 * @brief
 *
 * @param x
 */
void print_err_exception(const std::exception& x);

} // namespace StoneyDSP

#endif // STONEYDSP_CLI_H_
