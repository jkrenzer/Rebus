/**
 * @Author: Jörn Krenzer <jkrenzer>
 * @Date:   20-04-2017
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: Exception
 * @Last modified by:   jkrenzer
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */

/**
 * @file Exception.hpp
 * @brief Headerfile for Rebus exceptions and exception-debugging
 *
 */

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

namespace Rebus
{
    namespace Exception
    {
        class Exception : public std::exception
        {
        protected:

            std::string _message;
            std::string _description;
            std::string _fileName;
            int _lineNumber;

        public:

            explicit Exception(const char* message) : _message(message), _fileName(), _lineNumber(-1), _description(std::string("N/A"))
            {}

            explicit Exception(const std::string& message) : _message(message), _fileName(), _lineNumber(-1), _description(std::string("N/A"))
            {}

            explicit Exception(std::string& fileName, int lineNumber, const std::string& message, const std::string& description=std::string("N/A")) : _message(message), _fileName(fileName), _lineNumber(lineNumber), _description(description)
            {}

            virtual ~Exception() throw()
            {}

            virtual const char* what() const throw()
            {
                return this->_message.c_str();
            }

            virtual const char* file() const throw()
            {
                return this->_fileName.c_str();
            }

            virtual const char* description() const throw()
            {
                return this->_description.c_str();
            }

            virtual const int line() const throw()
            {
                return this->_lineNumber;
            }

        };

        std::string getErrorMessage(Exception& e)
        {
            return std::string("[") + std::string(e.file()) + std::string(":") + std::to_string(e.line()) + std::string("] ") + std::string(e.what());
        }

        std::string getErrorReport(Exception& e)
        {
            return std::string("[") + std::string(e.file()) + std::string(":") + std::to_string(e.line()) + std::string("] ") + std::string(e.what() + std::string("\n" + std::string(e.description())));
        }
    }
}

/* Preprocessor macros */

#define RebusThrow(exc, ...) throw(exc(__FILE__,__LINE__,__VA_ARGS__))

#endif
