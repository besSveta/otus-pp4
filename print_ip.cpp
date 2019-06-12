/*
 * print_ip.cpp
 *
 *  Created on: 25 мая 2019 г.
 *      Author: sveta
 */
#include "print_ip.h"

int main(int, char *[]) {
	std::vector<int> b{ 1, 2, 3, 4 };
	std::list<int> s{ 1, 2, 3, 4 };
	CommonIpPrinter::PrintIp<std::list<int>>(s);
	CommonIpPrinter::PrintIp<std::vector<int>>(b);
	CommonIpPrinter::PrintIp("ss");
	CommonIpPrinter::PrintIp<long long>(8875824491850138409);
	CommonIpPrinter::PrintIp<int>(2130706433);
	CommonIpPrinter::PrintIp<char>(-1);
	CommonIpPrinter::PrintIp<short>(0);
	CommonIpPrinter::PrintIp<double>(0.3);
	return 0;
}
