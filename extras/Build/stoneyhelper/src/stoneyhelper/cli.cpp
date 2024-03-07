/***************************************************************************//**
 * @file cli.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 0.1
 * @date 2024-02-28
 *
 *
 * @copyright Copyright (c) 2024
 *
 ******************************************************************************/

// #include "StoneyDSP/stoneydsp.hpp"
#include "stoneyhelper/cli.hpp"

#include <stdexcept>
#include <vector>

#include <iostream>
#include <iomanip>

#include <filesystem>
#include <fstream>

#include <string>
#include <sstream>

#include <climits> // INT_MAX

namespace StoneyDSP {

static std::vector<std::string>         _input_args;

static Mode                             _mode              = Mode::MODE_STRING;
static bool                             _mode_is_set       = false;

static bool                             _show_version      = false;
static bool                             _show_help         = false;
static bool                             _show_usage        = false;

#define __STDOUT_GAP_40 std::setw(40) << std::setfill(' ')

#define __STDOUT_USAGE_LINE(args, info) \
  std::cout << __STDOUT_GAP_40 << args << "  "; std::cout << info << std::endl;

void parse(int argc, char* argv[])
{

    if (argc < 2) {
        throw std::runtime_error("Missing input parameters!");
    }

    if (argc > 64) {
        throw std::runtime_error("Too many input parameters!");
    }

    // Args passed validation - pass them to an array...
    const std::vector<std::string> args(argv + 1, argv + argc);

    for (const auto& arg : args) {

        if (_input_args.empty()) {

            if (arg == "-v" || arg == "--version") {
                if (_show_version) {
                    throw std::runtime_error(
                        "Cannot use -v/--version parameter twice!"
                    );
                }
                _show_version = true;
                continue;
            }

            if (arg == "-h" || arg == "--help") {
                if (_show_help) {
                    throw std::runtime_error(
                        "Cannot use -h/--help parameter twice!"
                    );
                }
                _show_help = true;
                continue;
            }

            if (arg == "--usage") {
                if (_show_usage) {
                    throw std::runtime_error(
                        "Cannot use --usage parameter twice!"
                    );
                }
                _show_usage = true;
                continue;
            }

            if (arg == "--string") {
                if (_mode_is_set) {
                    throw std::runtime_error(
                        "Cannot use --string/--file mode switch twice!"
                    );
                }
                StoneyDSP::set_mode(MODE_STRING);
                _mode_is_set = true;
                continue;
            }

            if (arg == "--file") {
                if (_mode_is_set) {
                    throw std::runtime_error(
                        "Cannot use --string/--file mode switch twice!"
                    );
                }
                StoneyDSP::set_mode(MODE_FILE);
                _mode_is_set = true;
                continue;
            }
        }

        _input_args.push_back(arg);
    }
}

static int mode_string(std::istringstream& input_arg, std::string line, int line_count)
{
    while (std::getline(input_arg, line)) {

        // Encode it (note: new string per line found)...
        std::string input_data;
        input_data.reserve(line.size());

        try {

            input_data += line.data();

        } catch(const std::exception& x) {

            std::cout << x.what() << std::endl;
            std::cerr << "Could not stream input arg '" << line_count << "'!\n";
            input_data.clear();
            return EXIT_FAILURE;

        }

        // This is the main print-out to stdout
        for (auto x : input_data)
            std::cout << x;

        std::cout << '\n';

        input_data.clear();
    }

    return EXIT_SUCCESS;
}

static int mode_file(std::ifstream& input_arg, std::string line, int line_count)
{
    while (std::getline(input_arg, line)) {

        // Encode it (note: new string per line found)...
        std::string input_data;
        input_data.reserve(line.size());

        try {
            // SUCCESS
            input_data += line.data();
        } catch(const std::exception& x) {
            // FAILURE
            std::cout << x.what() << std::endl;
            return EXIT_FAILURE;
        }

        // This is the main print-out to stdout
        for (auto x : input_data)
            std::cout << x;

        std::cout << '\n';

        input_data.clear();
    }

    return EXIT_SUCCESS;
}

int process(int argc, char* argv[])
{
    int status = 0;

    // Parse command-line arguments...
    try {

        StoneyDSP::parse(argc, argv);

    } catch (const std::exception& x) {

        StoneyDSP::print_err_exception(x);
        return EXIT_FAILURE;
    }


    if (StoneyDSP::show_version()) {
        StoneyDSP::print_version();
        return EXIT_SUCCESS;
    }

    if (StoneyDSP::show_help()) {
        StoneyDSP::print_help();
        return EXIT_SUCCESS;
    }

    if (StoneyDSP::show_usage()) {
        StoneyDSP::print_usage();
        return EXIT_SUCCESS;
    }

    // Return the args that were passed in to 'parse()'
    // and iterate through them...
    for (const auto& input_arg : StoneyDSP::input_args()) {

        std::string         line;
        int                 line_count      = 1;

        // if(get_mode() == MODE::MODE_FILE)
        //     std::ifstream       input_file      (input_arg.data(), std::ios::in);

        // if(get_mode() == MODE::MODE_STRING)
        //     std::istringstream  input_string    (input_arg.data(), std::ios::in);

        // std::istream        input_stream    (input_arg.data(), std::ios::in);
        std::ifstream       input_file      (input_arg.data(), std::ios::in);
        std::istringstream  input_string    (input_arg.data(), std::ios::in);

        switch(StoneyDSP::get_mode())
        {
            case MODE_STRING:
            status = StoneyDSP::mode_string(input_string, line, line_count);
            break;

            case MODE_FILE:
            status = StoneyDSP::mode_file(input_file, line, line_count);
            break;

            default:
            status = StoneyDSP::mode_string(input_string, line, line_count);
            break;
        }

        line.clear();
        input_string.clear();
        input_file.close();
    }

    return status;
}

void set_mode(const MODE& m) {
    _mode = m;
    _mode_is_set = true;
}

MODE get_mode() {
    return _mode;
}

const std::vector<std::string>& input_args() {
    return _input_args;
}

bool show_version() {
    return _show_version;
}

bool show_help() {
    return _show_help;
}

bool show_usage() {
    return _show_usage;
}

void print_usage() {
    std::cout << "usage: <prog> [OPTION]... [FILE]..." << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "" << std::endl;
    __STDOUT_USAGE_LINE("[--string]",       "String args mode.")
    __STDOUT_USAGE_LINE("[--file]",         "File args mode.")
    __STDOUT_USAGE_LINE("[-v|--version]",   "Show program version and exit.")
    __STDOUT_USAGE_LINE("[-h|--help]",      "Show program commands and exit.")
    __STDOUT_USAGE_LINE("[--usage]",        "Show program options and exit.")
}

void print_help() {
    std::cout << "usage: <prog> [OPTION]... [FILE]..." << std::endl;
}

void print_version() {
    std::cout << "<prog> v." << /** PROJECT_VERSION */ "1.0.0" << std::endl;
}

void print_err_exception(const std::exception& x) {
    std::cerr << x.what() << '\n';
    std::cerr << "usage: <prog> [OPTION]... [FILE]...\n";
}

} // namespace StoneyDSP
