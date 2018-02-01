/**
 * @Author: Jörn Krenzer <dastan>
 * @Date:   31-01-2018
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: Int.cpp
 * @Last modified by:   dastan
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#include <Rebus/Type/BasicTypes/Int.hpp>

namespace Rebus
{
  namespace Type
  {
    std::string Traits<int>::name()
    {
      return std::string("Int");
    }

    std::string Traits<int>::description()
    {
      return std::string("A standard c++ integer");
    }

    std::string Traits<int>::uuid()
    {
      return std::string("cf6b96cf-867a-4af0-b332-5b2bdbc36103");
    }
  }
}
