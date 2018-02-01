/**
 * @Author: Jörn Krenzer <jkrenzer>
 * @Date:   31-01-2018
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: Action
 * @Last modified by:   jkrenzer
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#ifndef ACTION_HPP
#define ACTION_HPP
#include <iostream>

namespace Rebus
{
    namespace Action
    {
        class Print
        {
        public:

            template <typename Type>
            void operator()(Type& ref, const std::string& name)
            {
                std::cout << name << ": " << ref << std::endl;
            }
        };
    }
}
#endif
