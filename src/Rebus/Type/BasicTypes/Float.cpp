/**
 * @Author: Jörn Krenzer <dastan>
 * @Date:   31-01-2018
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: Float.cpp
 * @Last modified by:   dastan
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#include <Rebus/Type/BasicTypes/Float.hpp>

namespace Rebus
{
  namespace Type
  {
    std::string Traits<float>::name()
    {
      return std::string("float");
    }

    std::string Traits<float>::description()
    {
      return std::string("A standard c++ float");
    }

    std::string Traits<float>::uuid()
    {
      return std::string("67a09aba-87de-4c1f-bae4-c65e46e1b970");
    }
  }
}
