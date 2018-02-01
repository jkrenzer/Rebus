/**
 * @Author: Jörn Krenzer <jkrenzer>
 * @Date:   20-04-2017
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: Pointer
 * @Last modified by:   jkrenzer
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#ifndef POINTER_HPP
#define POINTER_HPP

#include <iostream>
#include <map>
#include <memory>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

// #include "Json"

namespace Rebus
{
    namespace Pointer
    {

        namespace Detail
        {
            /**
            * @brief Registry class for all database pointers
            *
            */
            template <class Type>
            class Registry
            {
            protected:

                std::map<boost::uuids::uuid, std::weak_ptr<Type> > uuid2Pointers;

                std::map<std::weak_ptr<Type>, boost::uuids::uuid> pointers2Uuids;

            public:

                /**
                * @brief Add a pointer with existing uuid to the registry
                *
                * @param pointer p_pointer:...
                * @param uuid p_uuid:...
                */
                void add(std::weak_ptr<Type> pointer, boost::uuids::uuid uuid);

                /**+++++++        *
                * @param uuid p_uuid:...
                */
                void remove(const boost::uuids::uuid& uuid);

                /**
                * @brief Get UUID corresponding to pointer-instance
                *
                * @param pointer p_pointer:...
                * @return boost::uuids::uuid
                */
                boost::uuids::uuid getUuid(const std::weak_ptr<Type>& pointer) const;

                /**
                * @brief Get Pointer corresponding to UUID
                *
                * @param uuid p_uuid:...
                * @return std::shared_ptr< Type >
                */
                std::shared_ptr<Type> getPointer(const boost::uuids::uuid& uuid) const;

                /**
                * @brief Check if Pointer is registered
                *
                * @param pointer p_pointer:...
                * @return bool
                */
                bool contains(const std::weak_ptr<Type>& pointer) const;

                /**
                * @brief Check if UUID is registered
                *
                * @param uuid p_uuid:...
                * @return bool
                */
                bool contains(const boost::uuids::uuid& uuid) const;
            };
        }

        template <class Type>
        class Pointer
        {
        private:
            boost::uuids::uuid _id;



        protected:
            std::shared_ptr<Type> _pointer;
            bool _tainted;

            void addToRegistry(void);

            void removeFromRegistry(void);

            void tainted(bool taint);

            bool load(void);

            void deleter(Type* ptr);

        public:
            Pointer(std::shared_ptr<Type>& ptr, boost::uuids::uuid id);

            Pointer(Type* ptr, boost::uuids::uuid id);

            Pointer(boost::uuids::uuid id);                     // TODO

            Pointer(Type* ptr);

            Pointer(std::shared_ptr<Type>& ptr);

            boost::uuids::uuid id();

            Type* modify();

            const Type* operator->();

            const Type& operator*();

            bool tainted();

            operator bool() const;                              // TODO

    //         friend ::Rebus::Json::Converter;

        };
    }
}

/*
 * Definitions below as the C++-Standard does not allow definitions of template-class-functions to be in a seperate file.
 */

template <class Type>
Rebus::Pointer::Pointer<Type>::Pointer(Type* ptr) : _id(boost::uuids::random_generator()()),  _pointer(ptr)
{
    _tainted = false;
}

template <class Type>
Rebus::Pointer::Pointer<Type>::Pointer(std::shared_ptr<Type>& ptr) : _id(boost::uuids::random_generator()()),  _pointer(ptr)
{
    _tainted = false;
}

template <class Type>
boost::uuids::uuid Rebus::Pointer::Pointer<Type>::id()
{
    return this->_id;
}

template <class Type>
Type* Rebus::Pointer::Pointer<Type>::modify()
{
    this->tainted(true);
    return this->_pointer.operator->();
}

template <class Type>
const Type* Rebus::Pointer::Pointer<Type>::operator->()
{
    return this->_pointer.operator->();
}

template <class Type>
const Type& Rebus::Pointer::Pointer<Type>::operator*()
{
    return this->_pointer.operator*();
}

template <class Type>
void Rebus::Pointer::Pointer<Type>::tainted(bool taint)
{
    this->_tainted = taint;
}

template <class Type>
bool Rebus::Pointer::Pointer<Type>::tainted()
{
    return this->_tainted;
}
#endif
