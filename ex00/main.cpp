#include "Easyfind.hpp"
#include <vector>
#include <iostream>

int			main(int argc, const char* argv[]);
static void	parse_and_load_arguments_into_(std::vector<int> *v, 
	int argc, const char* argv[]);
static void	set_signals(void);
static bool	parse_and_convert_input(int* integer_to_find);

int	main(int argc, const char* argv[])

{
	std::vector<int>	v;
	int					integer_to_find;

	parse_and_load_arguments_into_(&v, argc, argv);
	if (!v.size())
		return (1);
	set_signals();
	if (!parse_and_convert_input(&integer_to_find))
		return (1);
	try
	{
			(void)easyfind(v, integer_to_find);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

#define INT_MIN -2147483648
#define INT_MAX 2147483647

static void	parse_and_load_arguments_into_(std::vector<int> *v, 
	int argc, const char* argv[])

{
	for (int i = 1; i < argc; ++i)
	{
		char		*end;
		long const	element = strtol(argv[i], &end, 10);

		if (*end ^ '\0')
			std::cout
			<< '\'' << argv[i] << "' is invalid. Dismissed." << std::endl;
		else if (element < INT_MIN || element > INT_MAX)
			std::cout << element 
			<< " does not fit into an integer. Dismissed." << std::endl;
		else
			v->push_back(element);
	}
}

#include <csignal>
volatile sig_atomic_t	g_signal_received = 0;

void	signal_handler(int signum)

{
	g_signal_received = signum;
}

static void	set_signals(void)

{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}

static bool	parse_and_convert_input(int* integer_to_find)

{
	std::string	input;

	if (!getline(std::cin, input) || std::cin.eof())
		return (false);
	
	char*		end;
	long const	long_to_prevent_overflow = strtol(input.c_str(), &end, 10);
	if (*end ^ '\0' 
		|| long_to_prevent_overflow < INT_MIN 
		|| long_to_prevent_overflow > INT_MAX)
		return (parse_and_convert_input(integer_to_find));
	*integer_to_find = static_cast<int>(long_to_prevent_overflow);
	return (true);
}
