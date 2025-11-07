#include "MutantStack.hpp"
#include <list>

int			main(int argc, const char* argv[]);
static void	parse_and_push_args_into_(
				MutantStack<int>* mutantStack, std::list<int>* mirrorList,
				int argc, const char* argv[]);
static void	set_signals(void);
static int	launch_(MutantStack<int>* mutantStack, std::list<int>* mirrorList);
static void test_(const MutantStack<int>& mutantStack,
	const std::list<int>& mirrorList);
static void	print_(MutantStack<int>& mutantStack);

int	main(int argc, const char* argv[])

{
	MutantStack<int>	mutantStack;
	std::list<int>		mirrorList;

	parse_and_push_args_into_(&mutantStack, &mirrorList, argc, argv);
	set_signals();
	return (launch_(&mutantStack, &mirrorList));
}

#include <cstdlib>
#include <iostream>
#define INT_MAX 2147483647
#define INT_MIN -2147483648

static void	parse_and_push_args_into_(
				MutantStack<int>* mutantStack, std::list<int>* mirrorList,
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
		{
			mutantStack->push(static_cast<int>(element));
			mirrorList->push_back(static_cast<int>(element));
		}
	}
}

#include <csignal>
#include <sstream>
volatile sig_atomic_t	g_signal_received = 0;

static int	launch_(MutantStack<int>* mutantStack, std::list<int>* mirrorList)

{
	std::string	input;

	while (true)
	{
		if (g_signal_received)
		{
			std::cout << "\nSignal received. Exiting..." << std::endl;
			return (0);
		}
		print_(*mutantStack);
		std::cout << "PICK: 'PUSH n', 'POP n', TEST or EXIT" << std::endl;
		if (!getline(std::cin, input) || std::cin.eof())
			return (1);
		if (input.empty())
			continue ;

		std::istringstream	iss(input);
		std::string			command;

		iss >> command;
		if (command == "EXIT")
			return (0);
		else if (command == "PUSH")
		{
			int	value;
			if (iss >> value)
			{
				mutantStack->push(value);
				mirrorList->push_back(value);
				std::cout << "Pushed " << value << std::endl;
			}
			else
				std::cout << "Invalid PUSH format. Use 'PUSH n'" << std::endl;
		}
		else if (command == "POP")
		{
			int	count = 1;
			iss >> count;
			if (count <= 0)
			{
				std::cout << "Invalid pop count." << std::endl;
				continue ;
			}
			for (int i = 0; i < count; ++i)
			{
				if (mutantStack->empty()) 
				{
					std::cout << "Stack is empty, cannot pop." << std::endl;
					break ;
				}
                std::cout << "Popped " << mutantStack->top() << std::endl;
                mutantStack->pop();
                mirrorList->pop_back();
			}
		}
		else if (command == "TEST")
			test_(*mutantStack, *mirrorList);
		else
			continue ;
	}
}

static void test_(const MutantStack<int>& mutantStack,
	const std::list<int>& mirrorList)
{
	std::cout << "\nIterating MutantStack (bottom to top):" << std::endl;
	for (MutantStack<int>::const_iterator it = mutantStack.begin(); 
		it != mutantStack.end(); ++it)
		std::cout << *it << std::endl;

    std::cout << "\nIterating std::list (oldest to newest):" << std::endl;
    for (std::list<int>::const_iterator it = mirrorList.begin();
		it != mirrorList.end(); ++it)
		std::cout << *it << std::endl;

    bool								match = true;
    MutantStack<int>::const_iterator	mutantStackIt = mutantStack.begin();
    std::list<int>::const_iterator		mirrorListIt = mirrorList.begin();

	while (mutantStackIt != mutantStack.end()
		&& mirrorListIt != mirrorList.end())
	{
		if (*mutantStackIt != *mirrorListIt)
		{
			match = false;
			break ;
		}
		++mutantStackIt;
		++mirrorListIt;
	}
	if (mutantStackIt != mutantStack.end() || mirrorListIt != mirrorList.end())
		match = false;
	if (match)
		std::cout << "\nIterations match!" << std::endl;
	else
		std::cout << "\nbruh" << std::endl;
}

static void	print_(MutantStack<int>& mutantStack)

{
	if (mutantStack.empty())
		std::cout << "Empty stack." << std::endl;
	std::cout << "Current stack (top to bottom): ";
	for (MutantStack<int>::const_reverse_iterator it = mutantStack.rbegin(); 
		it != mutantStack.rend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

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
