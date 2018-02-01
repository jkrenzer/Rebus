/**
 * @Author: Jörn Krenzer <jkrenzer>
 * @Date:   20-04-2017
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: json_diff.cpp
 * @Last modified by:   jkrenzer
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#include <iostream>
#include <exception>
#include "Rebus/Json.hpp"
#include "Test.hpp"

int main()
{
    try
    {
        std::cout << "Rebus Unit-Test: Diff and Patch of JSON" <<  std::endl;
        Rebus::JsonIO::Json j_original;
        Rebus::JsonIO::Json j_changed;
        try
        {
            j_original = {
                {"baz", {"one", "two", "three"}},
                {"foo", "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam VOLUPTUA."}
            };

            j_changed = {
                {"baz", {"four", "five", "six"}},
                {"foo", "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua."}
            };
        }
        catch (std::exception& e)
        {
            std::cout << "Exception while declaring JSON objects." << std::endl;
            throw e;
        }
        std::cout << "Generating diff..." << std::endl;
        Rebus::JsonIO::Json patch;
        try {
            patch = Rebus::JsonIO::Json::diff(j_original, j_changed);
        }
        catch(std::exception& e)
        {
            std::cout << "Exception while generating diff." << std::endl;
            throw e;
        }
        std::cout << "Diff: " << patch.dump(4)  << std::endl;
        std::cout << "Patching..." << std::endl;
        Rebus::JsonIO::Json j_patched;
        try
        {
            j_patched = j_original.patch(patch);
        }
        catch(std::exception& e)
        {
            std::cout << "Exception while patching." << std::endl;
            throw e;
        }

        if (j_patched == j_changed)
        {
            std::cout << "Patched was sucessfully applied. Test succeeded." <<  std::endl;
            return SUCCESS;
        }
        else
        {
            std::cout << "Patched JSON != Changed JSON. Test failed. JSON-Objects were:" <<  std::endl;
            std::cout << "# j_original" << std::endl;
            std::cout << j_original.dump(4) << std::endl << std::endl;
            std::cout << "# j_changed" << std::endl;
            std::cout << j_changed.dump(4) << std::endl << std::endl;
            std::cout << "# j_patched" << std::endl;
            std::cout << j_patched.dump(4) << std::endl << std::endl;
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
