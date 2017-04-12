cmake_minimum_required(VERSION 2.8.12)
project(rebus)

set(PROJECT_NAME Rebus)
set(PROJECT_BRIEF_DESCRIPTION "C++ JSON ORM")
set(DOCUMENTATION_DIR ${CMAKE_CURRENT_SOURCE_DIR}/doc)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set(CMAKE_TOOLCHAIN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchains)
#set(PROJECT_LOGO)

### Configuration switches

# set(LINK_STATIC FALSE) # set TRUE to link libraries static, so we get a stand-alone application
set(BUILD_SHARED_LIBS TRUE)

###

add_compile_options(-std=c++11) #Enable C++11 support
# 
# if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" AND NOT MINGW)
#  message("Enabling GCC Debug-Flags")
#  add_compile_options(-g -O0) #Enable debugging-output, no-optimization (for valgrind and gdb)
#  set(CMAKE_VERBOSE_MAKEFILE ON)
#  elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" AND MINGW)
#  message("Enabling GCC Debug-Flags with DWARF output")
#  add_compile_options(-gdwarf-4 -O0)
#  set(CMAKE_VERBOSE_MAKEFILE ON)
# endif()
# 
# set(BOOST_ALL_DYN_LINK TRUE)
# set(Boost_DETAILED_FAILURE_MSG "ON")
# 
# find_package(Boost COMPONENTS program_options log REQUIRED)
# find_package(LibXML++ REQUIRED)
# find_package(Glibmm REQUIRED)
find_package(Doxygen)
# find_package(Jsoncpp REQUIRED)

 include_directories(${INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)
# link_directories(${LINK_DIRS} ${Boost_LIBRARIES} ${LibXML++_LIBRARIES} ${glibmm_LIBRARIES} build/)

add_executable(test_visit src/test.cpp)
target_link_libraries(test_visit jsoncpp)

#add_executable(rebus main.cpp)
#target_link_libraries(rebus ${Boost_LIBRARIES})

install(TARGETS test_visit RUNTIME DESTINATION bin)

#Unit-Testing

enable_testing()

add_test(json_roundtrip test_visit)
