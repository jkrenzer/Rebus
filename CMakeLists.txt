cmake_minimum_required(VERSION 2.8.12)
include(CTest)
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
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" AND NOT MINGW)
  message("Enabling GCC Debug-Flags")
  add_compile_options(-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings) #Enable debugging-output, no-optimization (for valgrind and gdb)
  set(CMAKE_VERBOSE_MAKEFILE ON)
  
  elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" AND MINGW)
  message("Enabling GCC Debug-Flags with DWARF output")
  add_compile_options(-gdwarf-4 -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings)
  set(CMAKE_VERBOSE_MAKEFILE ON)
 
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Coverage" AND NOT MINGW)
  message("Enabling GCC Coverage-Analysis")
  add_compile_options(-g -O0 -Wall -W --coverage -fprofile-arcs -ftest-coverage) #Enable debugging-output, no-optimization (for valgrind and gdb)
  set(CMAKE_C_FLAGS="-g -O0 -Wall -W --coverage -fprofile-arcs -ftest-coverage")
  set(CMAKE_VERBOSE_MAKEFILE ON)
  find_package(LCov REQUIRED)  
  elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Coverage" AND MINGW)
  message("Enabling GCC Debug-Flags with DWARF output")
  add_compile_options(-gdwarf-4 -g -O0 -Wall -W --coverage -fprofile-arcs -ftest-coverage)
  set(CMAKE_VERBOSE_MAKEFILE ON)
 
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Coverage")
  add_custom_target(coverage_report

		# Cleanup lcov
		${LCOV_EXECUTABLE} --directory . --zerocounters

		# Run tests
		COMMAND make test

		# Capturing lcov counters and generating report
		COMMAND ${LCOV_EXECUTABLE} --directory . --capture --output-file coverage.info
		COMMAND ${LCOV_EXECUTABLE} --remove coverage.info '${CMAKE_CURRENT_SOURCE_DIR}/tests/*' '/usr/*' '${CMAKE_CURRENT_SOURCE_DIR}/include/*' --output-file coverage.info
		COMMAND ${GENHTML_EXECUTABLE} -o $ coverage coverage.info

		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMENT "Resetting code coverage counters to zero.\nProcessing code coverage counters and generating report."
	)

  add_custom_target(codecov
                
                make clean && make
                COMMAND curl -s https://codecov.io/bash > codecov.sh
                COMMAND bash codecov.sh -t cbf6ed32-e160-4fae-b568-406ea3944c23
                COMMENT "Trying to send coverageinformation to codecov"
                
  )
	# Show info where to find the report
 add_custom_command(TARGET coverage_report POST_BUILD
		COMMAND ;
		COMMENT "Open ./coverage/index.html in your browser to view the coverage report."
 )
endif()
 
find_package(Doxygen)

### Taget for generating Doxygen documentation (if Doxygen is found)

if(DOXYGEN_FOUND)
 configure_file(doc/Doxyfile ./Doxyfile)
 add_custom_target(doc
     ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
     #COMMAND ${CMAKE_MAKE_PROGRAM} -C ${CMAKE_CURRENT_SOURCE_DIR}/doc/latex/proc/
     #COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/doc/latex/proc/refman.pdf ${CMAKE_CURRENT_SOURCE_DIR}/doc/latex/manual.pdf
     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
     COMMENT "Generating API documentation with Doxygen" VERBATIM
 )
endif(DOXYGEN_FOUND)


 include_directories(${INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)
# link_directories(${LINK_DIRS} ${Boost_LIBRARIES} ${LibXML++_LIBRARIES} ${glibmm_LIBRARIES} build/)

add_executable(test_json_diff tests/json_diff.cpp)
add_executable(test_cpp_json_roundtrip tests/cpp_json_roundtrip.cpp)
add_executable(test_inheritance tests/inheritance.cpp)

#Unit-Testing

configure_file(CTestCustom.cmake CTestCustom.cmake)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Coverage")
  target_link_libraries(test_json_diff gcov)
  target_link_libraries(test_cpp_json_roundtrip gcov)
  target_link_libraries(test_inheritance gcov)
endif()

add_test(json_diff test_json_diff)
add_test(cpp_json_roundtrip test_cpp_json_roundtrip)
add_test(inheritance test_inheritance)
