/**
 * @Author: Jörn Krenzer <jkrenzer>
 * @Date:   03-07-2017
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: Visitor
 * @Last modified by:   jkrenzer
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#ifndef VISITOR_HPP
#define VISITOR_HPP
#include <iostream>

namespace Rebus
{
    namespace Visitor
    {
        /**
        * @brief Function to declare visitable members of classes.
        *
        * @param Action p_Action:...
        * @param MemberType p_MemberType:...
        * @param action p_action:...
        * @param member p_member:...
        * @param name p_name:...
        */
        template <class Action, typename MemberType>
        void member(Action& action, MemberType& member, const std::string& name)
        {
            action(member,  name);
        }

        template <class Action, typename MemberType>
        void hasOne(Action& action, MemberType* member, const std::string& name)
        {
            action.link(member,  name);
        }

        template <class Action, typename MemberType, template <typename> class STLContainerType>
        void hasMany(Action& action, STLContainerType<MemberType>& members, const std::string& name)
        {
            action.links(members,  name); //TODO What do we do to get the members?
        }

        /**
         * @brief Function to declare inheritance of members and methods of a parent class
         *
         * @param Action p_Action:...
         * @param CurrentType Type of current class
         * @param ParentType Type of parent class
         */
        template <class ParentType, class Action, class CurrentType>
        void inherit(Action& action, CurrentType* currentThis)
        {
            ParentType* inherited = static_cast<ParentType*>(currentThis);
            inherited->description(action);
        }
    }
}
#endif
