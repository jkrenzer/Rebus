#include <iostream>
#include <sstream>
#include <exception>

#include "Test"
#include "Rebus/Action"
#include "Rebus/Visitor"
#include "Rebus/Pointer"
#include "Rebus/Json"

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
