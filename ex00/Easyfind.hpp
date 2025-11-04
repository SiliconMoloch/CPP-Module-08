#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <iostream>
#include <sstream>

template	<typename T>
typename	T::iterator easyfind(T& container, int value)

{
	typename T::iterator const	it = 
		std::find(container.begin(), container.end(), value);
	if (it != container.end())
	{
		std::cout << *it << " found at index " <<
		std::distance(container.begin(), it) << '.' << std::endl;
		return (it);
	}
	else
	{
		std::stringstream	error_msg;
		error_msg << '\'' << value << "' not found.";
		throw (std::runtime_error(error_msg.str()));
	}
}

#endif
