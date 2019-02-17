/**
 * @file Args.h
 * @date Dec 11, 2018
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

#ifndef Args_h_INCLUDED
#define Args_h_INCLUDED

#include "string_convert.hpp"
#include <vector>

class Args
{
public:
	class NoMoreArgException;
	class NoSuchArgException;

	using ArgVector = std::vector< std::pair<std::string, std::string> >;
	class Item
	{
	public:
		Item(const ArgVector& tokens) : tokens(tokens), itToken(tokens.begin())
		{
		}

		Item(const ArgVector& tokens, ArgVector::const_iterator itToken) : tokens(tokens), itToken(itToken)
		{
		}

		template <typename T>
		T convert() const
		{
			return string_convert<T>(itToken->second);
		}
		template <typename T>
		operator T() const
		{
			return convert<T>();
		}

		template <typename T>
		Item& operator >> (T& variable)
		{
			if (itToken != tokens.end())
			{
				variable = string_convert<T>(itToken->second);
				++itToken;
			}
			else throw NoMoreArgException();
			return *this;
		}

		const std::string& name() const
		{
			return itToken->first;
		}

		const std::string& valueStr() const
		{
			return itToken->second;
		}

	private:
		const ArgVector& tokens;
		ArgVector::const_iterator itToken;
	};

public:
	Args(int argc, const char* const argv[], const std::string& prefix = "--", const std::string& assignStr = "=");
	std::string cmdStr() const;

	Item item(const std::string& name) const;
	template <typename T>
	T item(const std::string& name, const T& defaultValue) const
	{
		try
		{
			return string_convert<T>(item(name).valueStr());
		}
		catch (const NoSuchArgException& e)
		{
			return defaultValue;
		}
	}

	std::string item(const std::string& name, const char* defaultValue) const;

	Item operator() (const std::string& name) const
	{
		return item(name);
	}

	template <typename T>
	T operator() (const std::string& name, const T& defaultValue) const
	{
		return item(name, defaultValue);
	}

	std::string operator() (const std::string& name, const char* defaultValue) const
	{
		return item(name, defaultValue);
	}

	template <typename T>
	Item operator >> (T& variable)
	{
		Item item(tokens);
		return item >> variable;
	}

public:
	const std::string progName;
	const std::string prefix;
	const std::string assignStr;

private:
	void store(std::pair<std::string, std::string>& tokenPair);

private:
	std::vector< std::pair<std::string, std::string> > tokens;
};


template <>
std::string Args::Item::convert<std::string>() const
{
	return string_convert<const std::string&>(itToken->second);
}

class Args::NoMoreArgException : public std::exception
{
public:
	NoMoreArgException()  : message("No more arguments left") {}
	const char* what() const throw() { return message.c_str(); }

public:
	const std::string message;
};

class Args::NoSuchArgException : public std::exception
{
public:
	NoSuchArgException(const std::string& name)  : message("No argument named '" + name + "'") {}
	const char* what() const throw() { return message.c_str(); }

public:
	const std::string message;
};



#endif /* Args_h_INCLUDED */

