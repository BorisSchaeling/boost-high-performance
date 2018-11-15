#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>

struct object
{
	int id;
	object(int id) : id{ id } {}
};

int main()
{
	std::list<object> c;
	auto r = boost::irange(0, 10'000);

	for (auto i : r)
	{
		c.emplace_back(i);
	}

	int sum = 0;

	{
		boost::timer::auto_cpu_timer t;
		for (auto i : r)
		{
			auto it = std::find_if(std::begin(c), std::end(c),
				[i](const auto &obj) { return obj.id == i; });
			sum += it->id;
		}
	}

	std::cout << sum;
}
