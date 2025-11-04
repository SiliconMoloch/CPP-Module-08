#include "Span.hpp"
#include <algorithm>

Span::Span(unsigned int N) : _maxSize(N)

{

}

void	Span::addNumber(int x)

{
	if (_numbers.size() >= _maxSize)
		throw (std::runtime_error("Cannot add number: Span is full"));
	_numbers.push_back(x);
}

#include <limits>

unsigned long	Span::shortestSpan(void) const

{
	if (_numbers.size() < 2)
		throw (std::runtime_error("No span can be found"));
	
	std::vector<int>	sorted = _numbers;
	unsigned long					minSpan = 
		std::numeric_limits<unsigned long>::max();
	unsigned long					diff;

	std::sort(sorted.begin(), sorted.end());
	for (unsigned int i = 1; i < sorted.size(); ++i)
	{
		diff = (unsigned long)(sorted[i]) - (unsigned long)(sorted[i - 1]);
		if (diff < minSpan)
			minSpan = diff;
	}
	return (minSpan);
}

unsigned long	Span::longestSpan(void) const

{
	if (_numbers.size() < 2)
		throw (std::runtime_error("No span can be found"));
	std::vector<int>::const_iterator minIt =
		min_element(_numbers.begin(), _numbers.end());
	std::vector<int>::const_iterator maxIt =
		max_element(_numbers.begin(), _numbers.end());
	return ((unsigned long)(*maxIt) - (unsigned long)(*minIt));
}















































Span::Span(void) : _maxSize(0)

{

}

Span::Span(const Span& other) : _maxSize(other._maxSize),
	_numbers(other._numbers)

{

}

Span&	Span::operator=(const Span& to_assign)

{
	if (this != &to_assign)
	{
		_maxSize = to_assign._maxSize;
		_numbers = to_assign._numbers;
	}
	return (*this);
}

Span::~Span(void)

{

}
