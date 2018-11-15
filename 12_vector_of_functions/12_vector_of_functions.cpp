#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <iostream>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>

struct object
{
	int id;
	char dummy[64];
	object(int id) : id{ id } {}
	int operator()() const { return id; }
};

struct object2
{
	int id;
	char dummy[128];
	object2(int id) : id{ id } {}
	int operator()() const { return id; }
};

int main()
{
	std::vector<std::function<int()>> c;
	auto r = boost::irange(0, 10'000);

	for (auto i : r)
	{
		if (i % 2)
			c.push_back(object{ i });
		else
			c.push_back(object2{ i });
	}

	int sum = 0;

	{
		boost::timer::auto_cpu_timer t;
		for (auto i : r)
		{
			auto it = std::find_if(std::begin(c), std::end(c),
				[i](const auto &function) { return function() == i; });
			sum += (*it)();
		}
	}

	std::cout << sum;
}
