#include <iterator>
#include <iostream>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>
#include <boost/heap/fibonacci_heap.hpp>

int main()
{
	auto r = boost::irange(0, 10'000);
	boost::heap::fibonacci_heap<int> c;

	for (auto i : r)
	{
		c.emplace(i);
	}

	{
		boost::timer::auto_cpu_timer t;
		for (auto it = std::begin(c); it != std::end(c); ++it)
		{
			auto handle = c.s_handle_from_iterator(it);
			const int new_value = *it * 2;
			c.increase(handle, new_value);
		}
	}

	std::cout << c.top();
}
