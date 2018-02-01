/**
 * @Author: Jörn Krenzer <jkrenzer>
 * @Date:   20-04-2017
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: inheritance.cpp
 * @Last modified by:   jkrenzer
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#include <iostream>
#include <sstream>
#include <exception>

#include "Test.hpp"
#include "Rebus/Action.hpp"
#include "Rebus/Visitor.hpp"
#include "Rebus/Pointer.hpp"
#include "Rebus/Json.hpp"

class Test
{
protected:
    int a;


public:
  std::string b;
    Test()
    {
        a = 15;
        b = std::string("Original");
    }
    template <class Action>
    void description(Action& act)
    {
        Rebus::Visitor::member(act,  a, "a");
        Rebus::Visitor::member(act,  b, "b");
    }
};

class NewTest :  public Test
{
public:
    float c;
    NewTest()
    {
        c = 1.234567;
    }
    template <class Action>
    void description(Action& act)
    {
      Rebus::Visitor::member(act,  c, "c");
      Rebus::Visitor::inherit<Test>(act,  this);
    }
};


int main()
{   try
    {
        std::cout << "Rebus Unit-Test: Inheritance in Roundtrip" <<  std::endl;
        Rebus::Pointer::Pointer<NewTest> ptr(new NewTest);
        ptr.modify()->b = std::string("Changed");
        JsonLib::json value;
        Rebus::JsonIO::Action::Encode action(value);
        ptr.modify()->description(action);
        Rebus::Pointer::Pointer<NewTest> ptr2(new NewTest);
        Rebus::JsonIO::Action::Decode action2(action.rootRef);
        ptr2.modify()->description(action2);
        if (ptr2->b == ptr->b)
        {
            std::cout << "Roundtrip with inheritance sucessfull. Test succeeded." <<  std::endl;
            return SUCCESS;
        }
        else
        {
            std::cout << "Roundtrip: prt->b != prt2->b. Test failed." <<  std::endl;
            return FAILURE;
        }
    }
    catch(std::exception& e)
    {
        std::cout << "Exception thrown. Test failed. What:" <<  std::endl;
        std::cout << e.what() <<  std::endl;
        return FAILURE;
    }
}
