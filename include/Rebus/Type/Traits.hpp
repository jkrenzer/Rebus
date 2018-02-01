/**
 * @Author: Jörn Krenzer <dastan>
 * @Date:   20-04-2017
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: Traits
 * @Last modified by: jkrenzer
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <iostream>
#include <string>
#include <typeinfo>

namespace Rebus
{
    /**
     * @brief Namespace containing all Rebus-Type related stuff.
     */
    namespace Type
    {
        /**
         * @brief Interface-class for type-traits
         */
        class TraitsInterface
        {
        public:
            /**
             * @brief Retrieve library-scope name of the type
             * @returns std::string with name
             */
            virtual std::string name() = 0;

            /**
             * @brief Get library-scope description of the type
             * @returns std::string with description
             */
            virtual std::string description() = 0;
            /**
             * @brief Get the UUID of the type as std::string
             * @return [description]
             */
            virtual std::string uuid() = 0;
        };

        /**
         * @brief Template-implementation of the Traits-class for all types.
         * @see Traits
         */
        template <class T>
        class Traits : public TraitsInterface
        {

          static_assert(true, "Rebus::Type::Traits<...> not specialized for this type! Please write your own specialisation.");

        public:
            /**
             * @brief Retrieve library-scope name of the type
             * @returns std::string with name
             */
            virtual std::string name() = 0;

            /**
             * @brief Get library-scope description of the type
             * @returns std::string with description
             */
            virtual std::string description() = 0;
            /**
             * @brief Get the UUID of the type as std::string
             * @return [description]
             */
            virtual std::string uuid() = 0;
        };
    }
}

#endif
