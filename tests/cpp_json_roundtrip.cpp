#include <iostream>
#include <sstream>

#include "Tests"
#include "Actions"
#include "Visitors"
#include "Pointer"
#include "Json"

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
        Rebus::member(act,  a, "a");
        Rebus::member(act,  b, "b");
    }
    
    const bool operator==(const Test& other) const
    {
        return this->a == other.a && this->b == other.b;
    }
};

int main()
{
    try
    {
    std::cout << "Rebus Unit-Test: C++-JSON-Roundtrip" <<  std::endl;
    Rebus::Pointer<Test> ptr(new Test);
    ptr.modify()->b = std::string("Changed");
    JsonLib::json value;
    Rebus::JsonIO::Actions::Encode action(value);
    ptr.modify()->description(action);
    Rebus::Pointer<Test> ptr2(new Test);
    Rebus::JsonIO::Actions::Decode action2(action.rootRef);
    ptr2.modify()->description(action2);
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
