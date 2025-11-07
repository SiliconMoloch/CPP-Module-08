#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>

template 	<typename T>
class		MutantStack : public std::stack<T>
{
	public:
		typedef typename std::deque<T>::iterator			iterator;
		typedef typename std::deque<T>::const_iterator		const_iterator;
		typedef typename std::deque<T>::reverse_iterator	reverse_iterator;
		typedef typename std::deque<T>::const_reverse_iterator 	
														const_reverse_iterator;

		iterator				begin(void) 
		{
			return (this->c.begin());
		}
		iterator				end(void)
		{
			return (this->c.end());
		}
		const_iterator			begin(void) const
		{
			return (this->c.begin());
		}
		const_iterator			end(void) const
		{
			return (this->c.end());
		}
		reverse_iterator		rbegin(void)
		{
			return (this->c.rbegin());
		}
		reverse_iterator		rend(void)
		{
			return (this->c.rend());
		}
		const_reverse_iterator	rbegin(void) const
		{
			return (this->c.rbegin());
		}
		const_reverse_iterator	rend(void) const
		{
			return (this->c.rend());
		}
};

#endif
