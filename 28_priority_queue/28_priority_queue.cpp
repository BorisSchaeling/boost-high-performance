#include <queue>
#include <iostream>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>

int main()
{
	auto r = boost::irange(0, 10'000);
	std::priority_queue<int> c;

	for (auto i : r)
	{
		c.emplace(i);
	}

	{
		boost::timer::auto_cpu_timer t;
		std::priority_queue<int> c2;
		while (!c.empty())
		{
			c2.push(c.top() * 2);
			c.pop();
		}
		c.swap(c2);
	}

	std::cout << c.top();
}
