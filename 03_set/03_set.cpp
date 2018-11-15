#include <set>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>

int main()
{
	auto r = boost::irange(0, 10'000);
	std::set<int> c(std::begin(r), std::end(r));

	int sum = 0;

	{
		boost::timer::auto_cpu_timer t;
		for (auto i : r)
		{
			auto it = std::find(std::begin(c), std::end(c), i);
			sum += *it;
		}
	}

	std::cout << sum;
}
