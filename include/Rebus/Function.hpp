/**
 * @Author: Jörn Krenzer <jkrenzer>
 * @Date:   03-07-2017
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: Function
 * @Last modified by:   jkrenzer
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#ifndef VISITOR_FUNCTION_HPP
#define VISITOR_FUNCTION_HPP
#include <iostream>
#include <functional>

namespace Rebus
{
    namespace Visitor
    {
        /**
         * @brief Function to declare visitable class method function
         *
         * @param Action p_Action:...
         * @param ReturnType Type which is returned by the visited function
         * @param Arguments Multiple argument-types of function
         * @param name p_name:...
         */
        template <class Action, typename ReturnType, typename... Arguments>
        void method(Action& action,  std::function<ReturnType(Arguments...)> method, const std::string& name)
        {
            action.execute<ReturnType, Arguments...>(method,  name);
        }
    }
}

#endif
