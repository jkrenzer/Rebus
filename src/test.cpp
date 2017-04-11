#include <iostream>
#include <sstream>

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
        b = std::string("Blah!");
    }
    template <class Action>
    void description(Action& act)
    {
        Rebus::member(act,  a, "a");
        Rebus::member(act,  b, "b");
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
        Rebus::member(act,  c, "c");
        Rebus::inherit<Test>(act,  this);
    }
};


int main()
{
    std::cout << "Rebus 0.0.0" <<  std::endl;
    Rebus::Pointer<NewTest> ptr(new NewTest);
    ptr.modify()->b = std::string("Changed!!");
    JsonLib::json value;
    Rebus::JsonIO::Actions::Encode action(value);
    ptr.modify()->description(action);
    std::stringstream ss;
    ss << action.rootRef <<  std::endl;
    std::cout <<  ss.str();
    Rebus::Pointer<NewTest> ptr2(new NewTest);
    Rebus::JsonIO::Actions::Decode action2(action.rootRef);
    ptr2.modify()->description(action2);
    std::cout << "Result: " <<  ptr2->b <<  std::endl;
    
  Rebus::JsonIO::Json j_original = R"({
  "baz": ["one", "two", "three"],
"foo": "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet."
  })"_json;
 
  Rebus::JsonIO::Json j_changed = R"({
"baz": ["one", "two", "three"],
"foo": "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clitoris kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet."
})"_json;

  auto patch = Rebus::JsonIO::Json::diff(j_changed, j_original);
  std::cout << "Diff: " << patch.dump(4)  << std::endl; 
    
  Rebus::JsonIO::Json j_patched = j_original.patch(patch);
  
  std::cout << "Patched: " <<  j_patched.dump(4) <<  std::endl;
}
