/**
 * @file string_convert.hpp
 * @date Dec 13, 2018
 * @author anvar
 * @note
 * SVN tag: $Id$
 *
 * Contributors: Shebli Anvar (shebli.anvar@cea.fr)
 *
 * This software is part of the RTOS and Multitasking Programming Course.
 *
 * @copyright © Shebli Anvar, Commissariat a l'Energie Atomique et aux Energies Alternatives (CEA)
 *
 * @par FREE SOFTWARE LICENCING
 * This software is governed by the CeCILL license under French law and abiding  * by the rules of distribution of free
 * software. You can use, modify and/or redistribute the software under the terms of the CeCILL license as circulated by
 * CEA, CNRS and INRIA at the following URL: "http://www.cecill.info". As a counterpart to the access to the source code
 * and rights to copy, modify and redistribute granted by the license, users are provided only with a limited warranty
 * and the software's author, the holder of the economic rights, and the successive licensors have only limited
 * liability. In this respect, the user's attention is drawn to the risks associated with loading, using, modifying
 * and/or developing or reproducing the software by the user in light of its specific status of free software, that may
 * mean that it is complicated to manipulate, and that also therefore means that it is reserved for developers and
 * experienced professionals having in-depth computer knowledge. Users are therefore encouraged to load and test the
 * software's suitability as regards their requirements in conditions enabling the security of their systems and/or data
 * to be ensured and, more generally, to use and operate it in the same conditions as regards security. The fact that
 * you are presently reading this means that you have had knowledge of the CeCILL license and that you accept its terms.
 *
 * @par COMMERCIAL SOFTWARE LICENCING
 * You can obtain this software from the author under other licencing terms for commercial purposes. For this you will need to
 * negotiate a specific contract with the author.
 */

#ifndef string_convert_hpp_INCLUDED
#define string_convert_hpp_INCLUDED

#include <boost/lexical_cast.hpp>
#include <boost/type_index.hpp>
#include <boost/algorithm/string.hpp>
#include <cctype>
#include <string>
#include <stdexcept>

template <typename T>
std::runtime_error make_string_convert_exception(const std::string& valueStr)
{
	return std::runtime_error("'" + valueStr + "' cannot be parsed as " + boost::typeindex::type_id<T>().pretty_name());
}

template <typename T>
T string_convert(const std::string& valueStr)
{
	try
	{
		return boost::lexical_cast<T>(valueStr);
	}
	catch (const boost::bad_lexical_cast& e)
	{
		throw make_string_convert_exception<T>(valueStr);
	}
}

template<>
bool string_convert<bool>(const std::string& valueStr)
{
	using T = bool;
	auto str = boost::algorithm::to_lower_copy(valueStr);
	if (str == "true" or str == "yes" or str == "1" or str == "")
		return true;
	else if (str == "false" or str == "no" or str == "0")
		return false;
	throw make_string_convert_exception<T>(valueStr);
}

template<>
int string_convert<int>(const std::string& valueStr)
{
	using T = int;
	size_t consumed{0};
	auto value = std::stoi(valueStr, &consumed, 0);
	if (consumed != valueStr.size())
	{
		value = static_cast<T>(std::stold(valueStr, &consumed));
		if (consumed != valueStr.size())
			throw make_string_convert_exception<T>(valueStr);
	}
	return value;
}

template<>
long string_convert<long>(const std::string& valueStr)
{
	using T = long;
	size_t consumed{0};
	auto value = std::stol(valueStr, &consumed, 0);
	if (consumed != valueStr.size())
	{
		value = static_cast<T>(std::stold(valueStr, &consumed));
		if (consumed != valueStr.size())
			throw make_string_convert_exception<T>(valueStr);
	}
	return value;
}

template<>
long long string_convert<long long>(const std::string& valueStr)
{
	using T = long long;
	size_t consumed{0};
	auto value = std::stoll(valueStr, &consumed, 0);
	if (consumed != valueStr.size())
	{
		value = static_cast<T>(std::stold(valueStr, &consumed));
		if (consumed != valueStr.size())
			throw make_string_convert_exception<T>(valueStr);
	}
	return value;
}

template<>
unsigned string_convert<unsigned>(const std::string& valueStr)
{
	using T = unsigned;
	size_t consumed{0};
	auto value = std::stoul(valueStr, &consumed, 0);
	if (consumed != valueStr.size())
	{
		value = static_cast<T>(std::stold(valueStr, &consumed));
		if (consumed != valueStr.size())
			throw make_string_convert_exception<T>(valueStr);
	}
	return value;
}

template<>
unsigned long string_convert<unsigned long>(const std::string& valueStr)
{
	using T = unsigned long;
	size_t consumed{0};
	auto value = std::stoul(valueStr, &consumed, 0);
	if (consumed != valueStr.size())
	{
		value = static_cast<T>(std::stold(valueStr, &consumed));
		if (consumed != valueStr.size())
			throw make_string_convert_exception<T>(valueStr);
	}
	return value;
}

template<>
unsigned long long string_convert<unsigned long long>(const std::string& valueStr)
{
	using T = unsigned long long;
	size_t consumed{0};
	auto value = std::stoull(valueStr, &consumed, 0);
	if (consumed != valueStr.size())
	{
		value = static_cast<T>(std::stold(valueStr, &consumed));
		if (consumed != valueStr.size())
			throw make_string_convert_exception<T>(valueStr);
	}
	return value;
}

template<>
float string_convert<float>(const std::string& valueStr)
{
	using T = float;
	size_t consumed{0};
	auto value = std::stof(valueStr, &consumed);
	if (consumed != valueStr.size())
	{
		value = static_cast<T>(std::stold(valueStr, &consumed));
		if (consumed != valueStr.size())
			throw make_string_convert_exception<T>(valueStr);
	}
	return value;
}

template<>
double string_convert<double>(const std::string& valueStr)
{
	using T = double;
	size_t consumed{0};
	auto value = std::stod(valueStr, &consumed);
	if (consumed != valueStr.size())
	{
		value = static_cast<T>(std::stold(valueStr, &consumed));
		if (consumed != valueStr.size())
			throw make_string_convert_exception<T>(valueStr);
	}
	return value;
}

template<>
long double string_convert<long double>(const std::string& valueStr)
{
	using T = long double;
	size_t consumed{0};
	auto value = std::stold(valueStr, &consumed);
	if (consumed != valueStr.size())
		throw make_string_convert_exception<T>(valueStr);

	return value;
}

template<>
const std::string& string_convert<const std::string&>(const std::string& valueStr)
{
	return valueStr;
}

template<>
const char* string_convert<const char*>(const std::string& valueStr)
{
	return valueStr.c_str();
}


#endif /* string_convert_hpp_INCLUDED */

