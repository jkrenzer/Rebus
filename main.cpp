#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <boost/program_options.hpp>
#include <libxml++-3.0/libxml++/libxml++.h>

/* Function used to check that 'opt1' and 'opt2' are not specified
   at the same time. */
void conflicting_options(const boost::program_options::variables_map& vm, 
                         const char* opt1, const char* opt2)
{
    if (vm.count(opt1) && !vm[opt1].defaulted() 
        && vm.count(opt2) && !vm[opt2].defaulted())
        throw std::logic_error(std::string("Conflicting options '") 
                          + opt1 + "' and '" + opt2 + "'.");
}

int main(int argc, char **argv) {
    std::locale::global(std::locale(""));
    boost::program_options::options_description desc("Allowed options");
  desc.add_options()
      ("help", "produce help message")
      ("file,f" , "save to file instead to STDOUT")
      ("version,V" , "print version information");
//       ("client,c" , "run as client")
//       ("measurements,t", boost::program_options::value<long int>(&target_loops)->default_value(1000), "set how many measurements to take");
  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  boost::program_options::notify(vm);
//   try 
//   {
//     conflicting_options(vm, "server", "client");
//   }
//   catch(std::exception& e)
//   {
//     std::cerr << e.what() << "\n";
//     return 1;
//   }
  
  if (vm.count("help")) 
  {
    std::cout << desc << std::endl;
    return 1;
  }
  else if (vm.count("version"))
  {
    std::cout << "Version-Information:" << std::endl;
  }
  else
  {
    std::cout << desc << std::endl;
    return 1;
  }
    return 0;
}
