/**
 * @Author: Jörn Krenzer <dastan>
 * @Date:   31-01-2018
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: Char.hpp
 * @Last modified by:   dastan
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#include <Rebus/Type/BasicTypes/Char.hpp>

namespace Rebus
{
  namespace Type
  {
    std::string Traits<char>::name()
    {
      return std::string("char");
    }

    std::string Traits<char>::description()
    {
      return std::string("A standard c++ char");
    }

    std::string Traits<char>::uuid()
    {
      return std::string("d1509004-48ce-4455-b74c-b9fe0ee07017");
    }
  }
}
