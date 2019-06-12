cmake_minimum_required(VERSION 3.2)

project(cmake VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
find_package(Threads REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(printIp print_ip.cpp)
add_library(printIplib print_ip_lib.cpp)
add_executable(test_printIp test_print_ip.cpp)

set_target_properties(printIp printIplib test_printIp PROPERTIES
	CXXSTANDARD 17
	CSS_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

set_target_properties(test_printIp PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(printIp 
	printIplib
    Threads::Threads
)

target_link_libraries(test_printIp	
	${Boost_LIBRARIES}
	printIplib
)
	
install(TARGETS printIp RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")


set(CPACK_PACKAGE_CONTACT bessveta@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(printIpTest test_printIp)
