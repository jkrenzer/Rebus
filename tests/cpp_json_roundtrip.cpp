/**
 * @Author: Jörn Krenzer <jkrenzer>
 * @Date:   20-04-2017
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: cpp_json_roundtrip.cpp
 * @Last modified by:   jkrenzer
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#include <iostream>
#include <sstream>

#include "Test.hpp"
#include "Rebus/Action.hpp"
#include "Rebus/Visitor.hpp"
#include "Rebus/Pointer.hpp"
#include "Rebus/Json.hpp"

#define DEBUG_OUTPUT 0

class Test
{
public:
  int a;
  std::string b;
  double c;
  enum enumerate {d1, d2};
  enumerate d;

    Test()
    {
        a = 15;
        b = std::string("Original");
        c = 3.1415 ;
        d = d1;

    }
    template <class Action>
    void description(Action& act)
    {
        Rebus::Visitor::member(act,  a, "a");
        Rebus::Visitor::member(act,  b, "b");
        Rebus::Visitor::member(act,  c, "c");
        Rebus::Visitor::member(act,  d, "d");
    }

    const bool operator==(const Test& other) const
    {
        return this->a == other.a && this->b == other.b && this->c == other.c && this->d == other.d;
    }
};

int main()
{
    try
    {
    std::cout << "Rebus Unit-Test: C++-JSON-Roundtrip" <<  std::endl;
    Rebus::Pointer::Pointer<Test> ptr(new Test);
    //Declaring test values
    int testA = 42;
    std::string testB("Changed");
    double testC = 51.08;
    Test::enumerate testD = Test::d2;
    //Setting testvalues
    ptr.modify()->a = testA;
    ptr.modify()->b = testB;
    ptr.modify()->c = testC;
    ptr.modify()->d = testD;
    //Roundtrip to JSON-land an back
    JsonLib::json value;
    Rebus::JsonIO::Action::Encode action(value);
    ptr.modify()->description(action);
#if DEBUG_OUTPUT
    std::cout << action.rootRef.dump(4) << std::endl;
#endif
    Rebus::Pointer::Pointer<Test> ptr2(new Test);
    Rebus::JsonIO::Action::Decode action2(action.rootRef);
    ptr2.modify()->description(action2);
    //There and back again, now test if everything is in place
    if (*ptr == *ptr2)
    {
        std::cout << "Roundtrip went well. Test succeeded." <<  std::endl;
        return SUCCESS;
    }
    else
    {
        std::cout << "Roundtrip went wrong. Test failed." <<  std::endl;
        return FAILURE;
    }
    }
    catch (std::exception& e)
    {
        std::cout << "Exception thrown, test failed. What:"<< std::endl << e.what() << std::endl;
        return FAILURE;
    }
    catch (...)
    {
        std::cout << "Unknown exception. Test failed." << std::endl;
        return FAILURE;
    }
}
