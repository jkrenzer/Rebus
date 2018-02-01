/**
 * @Author: Jörn Krenzer <jkrenzer>
 * @Date:   20-04-2017
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: basic_types.cpp
 * @Last modified by:   jkrenzer
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */

/**
 * @file basic_types.cpp
 * @brief Test for the functionality of the basic types
 * This file is a test for the basic types and checks the conversation and verification functions.
 */

#include <iostream>

#include <Rebus/Type/BasicTypes.hpp>

#include "Test.hpp"

using namespace Rebus;

template <class T>
void testType()
{
  Type::Traits<T> traits = Type::Traits<T>();
  std::cout << "Type-Name: " << traits.name() << " Description: " << traits.description() << " UUID: " << traits.uuid() << std::endl;
}

int main()
{
  try
  {
    testType<char>();
    testType<double>();
    testType<float>();
    testType<int>();
    testType<std::string>();
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
  return SUCCESS;
  //TODO Write test to check a) traits and verification of basic types and b) that calls to unimplemented types throw the right exceptions.
}
