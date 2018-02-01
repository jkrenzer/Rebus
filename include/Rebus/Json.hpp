/**
 * @Author: Jörn Krenzer <jkrenzer>
 * @Date:   31-01-2018
 * @Email:  joern.krenzer@gmx.de
 * @Project: Rebus (https://github.com/jkrenzer/rebus)
 * @Filename: Json
 * @Last modified by:   jkrenzer
 * @Last modified time: 31-01-2018
 * @License: LGPL Version 3
 * @Copyright: This software and all its parts are subject to the conditions of the above mentioned license. See the LICENSE file for more information.
 */



#ifndef JSON_HPP
#define JSON_HPP
#include <sstream>
#include "nlohmann/json.hpp"
#include "diff-match-patch-cpp-stl/diff_match_patch.h"

#include "Pointer.hpp"

namespace JsonLib = nlohmann;

namespace Rebus
{
    namespace JsonIO
    {

        namespace Action
        {
            class Encode
            {
            public:
                JsonLib::json& rootRef;

                Encode(JsonLib::json& rootRef);

                template <class Type>
                void operator()(Type& ref, const std::string& name);
            };

            class Decode
            {
            public:
              ::JsonLib::json& rootRef;

                Decode(JsonLib::json& rootRef);

                template <class Type>
                void operator()(Type& ref, const std::string& name);
            };
        }


        /**
        * @brief Wrapper class for Json-library (nlohmann::json)
        *
        * This class allows usage of the wrapped nlohmann::json-class and adds some special mechanisms to the diff and patch functions,  so we can use a diff at character-loevel for long texts.
        *         *
        */
        class Json :  public JsonLib::json
        {
        public:

            Json(const Json& other) : JsonLib::json(other)
            {}

            Json(JsonLib::json& other) : JsonLib::json(other)
            {}

            Json() : JsonLib::json()
            {}

            using JsonLib::json::operator=;

            static Json diff(const JsonLib::json& newJson, const JsonLib::json& oldJson, const std::string& path = "")
                {
                    auto diff = JsonLib::json::diff(newJson,  oldJson,  path);
                    for( auto it = diff.begin(); it != diff.end(); it++)
                    {
                        if (*it->find("op") == "replace")
                        {
                            auto value_it = it->find("value");
                            auto path_it = it->find("path");
                            if (value_it->is_string() and value_it->get<std::string>().size() > 31)
                            {
                                const std::string path = *path_it;
                                JsonLib::json::json_pointer ptr(path);
                                const std::string oldString = oldJson.at(ptr);
                                const std::string newString = newJson.at(ptr);
                                diff_match_patch<std::string> dmp;
                                dmp.Diff_Timeout = 0.0;
                                auto diffs = dmp.diff_main(newString, oldString);
                                dmp.diff_cleanupEfficiency(diffs);
                                auto patches = dmp.patch_make(diffs);
                                std::string diffValue = dmp.patch_toText(patches);
                                *value_it = diffValue;
                                (*it)["diff"] = true;
                            }
                        }
                    }
                    return diff;

                }

          Json patch(const Json& patch)
            {
                Json patch_local = patch;
                for( auto it = patch_local.begin(); it != patch_local.end(); it++)
                {
                    auto diff_it = it->find("diff");
                    if (diff_it !=  it->end())
                    {
                        auto value_it = it->find("value");
                        auto path_it = it->find("path");
                        const std::string path = *path_it;
                        diff_match_patch<std::string> dmp;
                        JsonLib::json::json_pointer ptr(path);
                        const std::string oldString = this->at(ptr);
                        const std::string newString;
                        auto patches = dmp.patch_fromText(*value_it);
                        auto result = dmp.patch_apply(patches, oldString);
                        *value_it = std::get<0>(result);
                        //Cleaning up our stuff before we call patch.
                        it->erase("diff");
                    }
                }
                auto patched = JsonLib::json::patch(patch_local);
                std::cout << "Patched:" << std::endl;
                std::cout << patched.dump(4) << std::endl;
                return patched;
            }

        };

        class Converter
        {
        public:

            template <class Type>
            JsonLib::json objToJson(::Rebus::Pointer::Pointer<Type> obj);

            template <class Type>
              ::Rebus::Pointer::Pointer<Type> JsonToObj(JsonLib::json json);
        };
    }
}

Rebus::JsonIO::Action::Encode::Encode(JsonLib::json& rootRef) : rootRef(rootRef)
{}

template <typename Type>
void Rebus::JsonIO::Action::Encode::operator()(Type& ref, const std::string& name)
{
    this->rootRef[name] = ref;
}

Rebus::JsonIO::Action::Decode::Decode(JsonLib::json& rootRef) : rootRef(rootRef)
{}

template <typename Type>
void Rebus::JsonIO::Action::Decode::operator()(Type& ref, const std::string& name)
{
    ref  = this->rootRef[name];
}

template <typename Type>
JsonLib::json Rebus::JsonIO::Converter::objToJson(Rebus::Pointer::Pointer<Type> obj)
{

}

template <typename Type>
Rebus::Pointer::Pointer<Type> Rebus::JsonIO::Converter::JsonToObj(JsonLib::json json)
{
}

#endif
