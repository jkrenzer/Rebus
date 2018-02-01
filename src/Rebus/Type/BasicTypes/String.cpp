/**
 * @Author: Jörn Krenzer <dastan>
 * @Date:   31-01-2018
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: String.cpp
 * @Last modified by:   dastan
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#include <Rebus/Type/BasicTypes/String.hpp>

namespace Rebus
{
  namespace Type
  {
    std::string Traits<std::string>::name()
    {
      return std::string("std::string");
    }

    std::string Traits<std::string>::description()
    {
      return std::string("A standard c++ std::string");
    }

    std::string Traits<std::string>::uuid()
    {
      return std::string("5d52e750-4d10-48be-a3dc-5270efd9ee9f");
    }
  }
}
