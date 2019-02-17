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

#include "Args.h"
#include <utility>
#include <iostream>

Args::Args(int argc, const char* const argv[], const std::string& prefix, const std::string& assignStr)
: progName(argv[0]), prefix(prefix), assignStr(assignStr)
{
	std::pair<std::string, std::string> tokenPair;
	for (auto i=1; i < argc; ++i)
	{
		std::string tok = argv[i];

		// Initialize value index to 0 and name index to std::string::npos
		size_t iValue = 0;
		size_t iName = std::string::npos;
		size_t iAssign = std::string::npos;

		// If there is a prefix then token should contain name (empty if there is no valid character after prefix)
		if (not prefix.empty() and tok.find(prefix) == 0)
		{
			iName = prefix.size();                   // Name begins right after prefix
			iAssign = tok.find(assignStr, iName);    // Look for separator in token
			if (iAssign != std::string::npos)        // If assign string present
				iValue = iAssign + assignStr.size(); // then value begins right after assign string
			else                                     // If no assign string is present
				iValue = std::string::npos;          // then token is only name (doesn't contain value)
		}
		else                                         // If no prefix is present
		{
			iAssign = tok.find(assignStr, 0);        // Look for separator in token
			if (iAssign != std::string::npos)        // If assign string present
			{
				iName = 0;                           // Then token begins as name and
				iValue = iAssign + assignStr.size(); // value is right after assign string
			}
			else                                     // If neither prefix nor assign string
			{                                        // then token is value
				iName = std::string::npos;
				iValue = 0;
			}
		}

		// If we have name then copy to current pair
		if (iName != std::string::npos)
		{
			if (not tokenPair.first.empty())         // Store possible previous (name,value) pair and begin new pair
				store(tokenPair);

			tokenPair.first = tok.substr(iName, iAssign - iName);
		}

		// If we have value then copy it and store current pair
		if (iValue != std::string::npos)
		{
			tokenPair.second = tok.substr(iValue);
			store(tokenPair);
		}
	}
	// If last token was a name (without value) store it with empty value
	if (not tokenPair.first.empty())
		store(tokenPair);
}

std::string Args::cmdStr() const
{
	std::string cmdStr_(progName);
	for (const auto& p : tokens)
	{
		cmdStr_ += " --" + p.first + "='" + p.second + "'";
	}
	return cmdStr_;
}

Args::Item Args::item(const std::string& name) const
{
	for (auto itToken = tokens.begin(); itToken != tokens.end(); ++itToken)
		if (itToken->first == name)
			return Item(tokens, itToken);

	throw NoSuchArgException(name);
}

std::string Args::item(const std::string& name, const char* defaultValue) const
{
	try
	{
		return item(name).valueStr();
	}
	catch (const NoSuchArgException& e)
	{
		return std::string(defaultValue);
	}
}

void Args::store(std::pair<std::string, std::string>& tokenPair)
{
	if (not tokenPair.first.empty() or not tokenPair.second.empty())
	{
		//std::cout << "Storing: '" << tokenPair.first << "'='" << tokenPair.second << "'" << std::endl;
		tokens.push_back(tokenPair);
		tokenPair.first.clear();
		tokenPair.second.clear();
	}
	else
	{
		std::cout << "Refuse to store empty pair!" << std::endl;
	}
}

