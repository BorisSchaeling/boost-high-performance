#include <iterator>
#include <algorithm>
#include <iostream>
#include <boost/poly_collection/base_collection.hpp>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>

struct object
{
	int id;
	char dummy[16];
	object(int id) : id{ id } {}
	virtual ~object() = default;
};

struct derived : object
{
	char dummy2[16];
	derived(int id) : object{ id } {}
};

int main()
{
	boost::base_collection<object> c;
	auto r = boost::irange(0, 100'000);

	for (auto i : r)
	{
		if (i % 2)
			c.insert(object{ i });
		else
			c.insert(derived{ i });
	}

	int sum = 0;

	{
		boost::timer::auto_cpu_timer t;
		for (const auto &obj : c)
		{
			sum += obj.id;
		}
	}

	std::cout << sum;
}
