#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>

struct object
{
	int id;
	char dummy[32];
};

int main()
{
	std::vector<object*> c;
	auto r = boost::irange(0, 10'000);

	for (auto i : r)
	{
		c.push_back(new object{ i });
	}

	int sum = 0;

	{
		boost::timer::auto_cpu_timer t;
		for (auto i : r)
		{
			auto it = std::find_if(std::begin(c), std::end(c),
				[i](const object *obj) { return obj->id == i; });
			sum += (*it)->id;
		}
	}

	std::cout << sum;
}
