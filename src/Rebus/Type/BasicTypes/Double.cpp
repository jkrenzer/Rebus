/**
 * @Author: Jörn Krenzer <dastan>
 * @Date:   31-01-2018
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: Double.cpp
 * @Last modified by:   dastan
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#include <Rebus/Type/BasicTypes/Double.hpp>

namespace Rebus
{
  namespace Type
  {
    std::string Traits<double>::name()
    {
      return std::string("double");
    }

    std::string Traits<double>::description()
    {
      return std::string("A standard c++ double");
    }

    std::string Traits<double>::uuid()
    {
      return std::string("86de80ed-72eb-4dc0-9d90-5dd209ee7d12");
    }
  }
}
