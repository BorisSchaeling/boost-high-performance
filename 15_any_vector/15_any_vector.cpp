#include <vector>
#include <any>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>

struct object
{
	int id;
	char dummy[64];
	object(int id) : id{ id } {}
	int get() const { return id; }
};

struct object2
{
	int id;
	char dummy[128];
	object2(int id) : id{ id } {}
	int get() const { return id; }
};

int main()
{
	std::vector<std::any> c;
	auto r = boost::irange(0, 10'000);

	for (auto i : r)
	{
		if (i % 2)
			c.emplace_back(object{ i });
		else
			c.emplace_back(object2{ i });
	}

	int sum = 0;

	try
	{
		boost::timer::auto_cpu_timer t;
		for (auto i : r)
		{
			auto it = std::find_if(std::begin(c), std::end(c),
				[i, j = 0](const auto &obj) mutable { return  i == ((j++ % 2) ?
					std::any_cast<object>(&obj)->get() : std::any_cast<object2>(&obj)->get()); });
			sum += (i % 2) ? std::any_cast<object>(&*it)->get() : std::any_cast<object2>(&*it)->get();
		}
	}
	catch (std::exception &ex) { std::cout << ex.what() << std::endl; }

	std::cout << sum;
}
