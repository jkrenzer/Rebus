cmake_minimum_required(VERSION 2.8.12)
set(PROJECT_NAME Rebus)
set(PROJECT_BRIEF_DESCRIPTION "C++ JSON ORM")
set(DOCUMENTATION_DIR ${CMAKE_CURRENT_SOURCE_DIR}/doc)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set(CMAKE_TOOLCHAIN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchains)
#set(PROJECT_LOGO)

include(CTest)
include(${CMAKE_MODULE_PATH}/FindPythonModule.cmake)

### Configuration switches

# set(LINK_STATIC FALSE) # set TRUE to link libraries static, so we get a stand-alone application
set(BUILD_SHARED_LIBS TRUE)

###

add_compile_options(-std=c++11) #Enable C++11 support
###

find_package(Doxygen)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Coverage")
  find_package(PythonInterp 3 REQUIRED)
endif()
###

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
  add_custom_target(test_coverage

                # Cleanup lcov
		${LCOV_EXECUTABLE} --directory . --zerocounters
		#Clean and build anew
		COMMAND make clean && make test

		# Capturing lcov counters and generating report
		COMMAND ${LCOV_EXECUTABLE} --directory . --capture --output-file test-coverage.info
		COMMAND ${LCOV_EXECUTABLE} --remove test-coverage.info '${CMAKE_CURRENT_SOURCE_DIR}/tests/*' '/usr/*' '${CMAKE_CURRENT_SOURCE_DIR}/deps/*' --output-file test-coverage.info
  )
  if(DOXYGEN_FOUND)
    find_python_module(coverxygen)
    add_custom_target(doxygen_coverage
                    ${PYTHON_EXECUTABLE} -m coverxygen --xml-dir ${CMAKE_CURRENT_SOURCE_DIR}/doc/xml --src-dir ${CMAKE_CURRENT_SOURCE_DIR} --output doxygen-coverage.info
                    DEPENDS doc
    )
    add_custom_target(codecov_doc
                COMMAND bash codecov.sh -t cbf6ed32-e160-4fae-b568-406ea3944c23 -X gcov -f doxygen-coverage.info -F documentation
                COMMENT "Trying to send doc-coverage-information to codecov"
                DEPENDS fetch_codecove doxygen_coverage
    )
    add_custom_target(doc_coverage_report
		${GENHTML_EXECUTABLE} -o $ doc_coverage doxygen-coverage.info
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		DEPENDS doxygen_coverage
		COMMENT "Generating documentation-coverage report."
	)
    # Show info where to find the report
    add_custom_command(TARGET doc_coverage_report POST_BUILD
                    COMMAND ;
                    COMMENT "Open ./doc_coverage/index.html in your browser to view the coverage report."
    )
  endif()
  add_custom_target(test_coverage_report
		${GENHTML_EXECUTABLE} -o $ test_coverage test-coverage.info
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMENT "Generating test-coverage report."
	)
  # Show info where to find the report
  add_custom_command(TARGET test_coverage_report POST_BUILD
		COMMAND ;
		COMMENT "Open ./test_coverage/index.html in your browser to view the coverage report."
  )
  add_custom_target(fetch_codecove
                curl -s https://codecov.io/bash > codecov.sh
  )
  add_custom_target(codecov_test
                bash codecov.sh -t cbf6ed32-e160-4fae-b568-406ea3944c23 -X gcov -f test-coverage.info -F tests
                COMMENT "Trying to send code-coverage-information to codecov"
                DEPENDS fetch_codecove test_coverage
  )


endif()



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


 include_directories(${INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/deps)
# link_directories(${LINK_DIRS} ${Boost_LIBRARIES} ${LibXML++_LIBRARIES} ${glibmm_LIBRARIES} build/)

# Libraries
add_library(rebus_type
  src/Rebus/Type/BasicTypes/Char.cpp
  src/Rebus/Type/BasicTypes/Double.cpp
  src/Rebus/Type/BasicTypes/Float.cpp
  src/Rebus/Type/BasicTypes/Int.cpp
  src/Rebus/Type/BasicTypes/String.cpp
)

add_executable(test_json_diff tests/json_diff.cpp)
add_executable(test_cpp_json_roundtrip tests/cpp_json_roundtrip.cpp)
add_executable(test_inheritance tests/inheritance.cpp)
add_executable(test_basic_types tests/basic_types.cpp)
target_link_libraries(test_basic_types rebus_type)

add_custom_target(build_tests
    DEPENDS test_json_diff test_cpp_json_roundtrip test_inheritance test_basic_types
)
#Unit-Testing

configure_file(CTestCustom.cmake CTestCustom.cmake)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Coverage")
  target_link_libraries(test_json_diff gcov)
  target_link_libraries(test_cpp_json_roundtrip gcov)
  target_link_libraries(test_inheritance gcov)
  target_link_libraries(test_basic_types gcov)
  target_link_libraries(rebus_type gcov)
endif()

add_test(build_test_code "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target build_tests)
add_test(json_diff test_json_diff)
add_test(cpp_json_roundtrip test_cpp_json_roundtrip)
add_test(inheritance test_inheritance)
add_test(basic_types test_basic_types)
