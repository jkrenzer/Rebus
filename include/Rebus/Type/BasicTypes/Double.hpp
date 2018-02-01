/**
 * @Author: Jörn Krenzer <dastan>
 * @Date:   31-01-2018
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: Double.hpp
 * @Last modified by:   dastan
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#include <iostream>

#include <Rebus/Type/Traits.hpp>

namespace Rebus
{

  namespace Type
  {

    template <>
    class Traits<double>
    {
    public:
      virtual std::string name();

      virtual std::string description();

      virtual std::string uuid();
    };

  }
}
