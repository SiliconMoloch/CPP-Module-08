#include "Span.hpp"
#include <iostream>
#include <cstdlib>

int					main(int argc, const char* argv[]);
static unsigned int	parse_(const char* arg);

int	main(int argc, const char* argv[])

{
	if (argc ^ 2)
	{
		std::cout << "Usage: ./Span <N>" << std::endl;
		return (1);
	}

	srand((unsigned int)time(0));
	unsigned int const	N = parse_(argv[1]);
	if (!N)
	{
		std::cout << "Please." << std::endl;
		return (1);
	}

	Span				that(N);
	Span				no_this_instead(that);
	Span				nevermind = no_this_instead;	
	std::vector<int>	v;

	try
	{
		for (unsigned int i = 0; i < N; ++i)
			v.push_back(rand() % 512);
		for (unsigned int i = 0; i < v.size(); ++i)
			std::cout << v[i] << std::endl;
		nevermind.addRange(v.begin(), v.end());
		std::cout << "Shortest span: " << nevermind.shortestSpan() << std::endl;
		std::cout << "Longest span: " << nevermind.longestSpan() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

static unsigned int	parse_(const char* arg)

{
	char				*end;
	unsigned long const	ulong_to_prevent_overflow = strtoul(arg, &end, 10);

	if (*end ^ '\0' || 
		ulong_to_prevent_overflow > INT_MAX)
		return (0);
	return (static_cast<unsigned int>(ulong_to_prevent_overflow));
}
