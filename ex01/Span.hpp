#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>
#define INT_MAX 2147483647
#define INT_MIN -2147483648 

class Span

{
	private:
		unsigned int		_maxSize;
		std::vector<int>	_numbers;
	public:
		Span(void);
		Span(const Span& other);
		Span&	operator=(const Span& to_assign);
		~Span(void);

		Span(unsigned int N);
		void			addNumber(int x);
		unsigned long	shortestSpan(void) const;
		unsigned long	longestSpan(void) const;

		template	<typename Iterator>
		void		addRange(Iterator begin, Iterator end)
		{
			if (_numbers.size() + std::distance(begin, end) > _maxSize)
				throw (std::runtime_error("Cannot add range: exceeds max size"));
			_numbers.insert(_numbers.end(), begin, end);
		}
};

#endif
