/*
 * prin_ip.h
 *
 *  Created on: 12 июн. 2019 г.
 *      Author: sveta
 */
#pragma once
#ifndef PRINT_IP_H_
#define PRINT_IP_H_

#include <iostream>
#include <vector>
#include <list>
#include <type_traits>
#include <string>
#include <math.h>

// Проверка различных типов данных.
template<typename T>
struct is_container {
	static const bool value = false;
};

template<typename T, typename Alloc>
struct is_container<std::vector<T, Alloc>> {
	static const bool value = true;
};

template<typename T, typename Alloc>
struct is_container<std::list<T, Alloc>> {
	static const bool value = true;
};
template<typename T>
constexpr bool is_container_v = is_container<T>::value;

template<typename T>
struct is_string {
	static const bool value = false;
};

template<>
struct is_string<std::string> {
	static const bool value = true;
};

template<>
struct is_string<char*> {
	static const bool value = true;
};

template<typename T>
struct is_char {
	static const bool value = false;
};

template<>
struct is_char<char> {
	static const bool value = true;
};


template<typename T>
constexpr bool is_string_v = is_string<T>::value;

template<typename T>
constexpr bool is_char_v = is_char<T>::value;

template<typename T>
constexpr bool is_integral_v = std::is_integral<T>::value;

// типы для задания специализаций.
enum class TypeId { Integral, Container, String, Other };

// из T  получить один из эелементов TypeId.
// будет передаваться в IpPrinter<TypeId::Integral, T> для вызова конкретной функции.
template<typename T>
struct TypeIdValue {
	static const TypeId value =
		is_container_v<T> ? TypeId::Container :
		(is_integral_v<T> || is_char_v<T>) ?
		TypeId::Integral :
		is_string_v<T> ?
		TypeId::String :
		TypeId::Other;
};
template<typename T>
constexpr TypeId TypeIdValue_v = TypeIdValue<T>::value;

// общий вид для принтера.
template<TypeId typeId, typename T>
struct IpPrinter {
	static void PrintIp(T someIp, std::ostream& out=std::cout) {

	}
};

// печать значений для контенеров.
template<typename T>
struct IpPrinter<TypeId::Container, T> {
	static void PrintIp(T someIp, std::ostream& out=std::cout) {
		if (std::begin(someIp) == std::end(someIp))
			return;

		if (std::begin(someIp) != std::end(someIp)) {
			std::string s = std::to_string(*std::begin(someIp));
			auto second = std::begin(someIp)++;
			for (auto a = second; a != std::end(someIp); a++) {
				s += "." + std::to_string(*a);
			}
			out << s << std::endl;
		}

	}
};

// печать значений для интергальных типов.
template<typename T>
struct IpPrinter<TypeId::Integral, T> {
	static void PrintIp(T someIp,std::ostream& out) {
		out << int2ip(someIp);
		out << std::endl;
	}
private:
	static std::string int2ip(const T ip) {
	    int size = sizeof(T);
		std::vector<unsigned char> bytes(size);
		auto t = 0;
		for (auto i = bytes.begin(); i != bytes.end() ; i++) {
			*i = (ip >> t) & 0xFF;
			t += 8;
		}
		std::string s= std::to_string(*bytes.rbegin());
		for (auto i = bytes.rbegin()+1; i != bytes.rend(); i++) {
			s += "." + std::to_string(*i);
		}
		return s;
	}

};

// печать значений для строк.
template<typename T>
struct IpPrinter<TypeId::String, T> {
	static void PrintIp(T someIp, std::ostream &out=std::cout) {
		out << someIp;
		out << std::endl;
	}
};


namespace CommonIpPrinter {
	template<typename T>
	static void PrintIp(const T &someIp, std::ostream& out=std::cout) {
		// std::cout<<static_cast<int>(TypeIdValue_v<T>)<< " ";
		IpPrinter<TypeIdValue_v<T>, T>::PrintIp(someIp, out);
	}
// отдельные функции печати строковых значений.
	static void PrintIp(const std::string &someIp, std::ostream& out=std::cout) {
		out << someIp;
		out << std::endl;
	}

	static void PrintIp(const char* someIp, std::ostream& out=std::cout) {
		out << someIp;
		out << std::endl;
	}
};




#endif /* PRINT_IP_H_ */
