/*
 * test_print_ip.cpp
 *
 *  Created on: 12 июн. 2019 г.
 *      Author: sveta
 */

#define BOOST_TEST_MODULE print_ip_test_module
#include <boost/test/included/unit_test.hpp>
#include "print_ip.h"
#include <string>

BOOST_AUTO_TEST_SUITE(print_ip_test_suite)

BOOST_AUTO_TEST_CASE(print_ip_check_values_test_case)
{
	std::stringstream ss;
	CommonIpPrinter::PrintIp<char>(-1, ss);
	BOOST_REQUIRE_EQUAL(std::stoi(ss.str()),255);
    CommonIpPrinter::PrintIp<long long>(8875824491850138409, ss);
    std::string s= ss.str();
	BOOST_REQUIRE_EQUAL(s.substr(4,27), "123.45.67.89.101.112.131.41");
}



BOOST_AUTO_TEST_SUITE_END()







