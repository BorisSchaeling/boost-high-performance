#include <set>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>

struct object
{
	int id;
	object(int id) : id{ id } {}
	bool operator<(const object &obj) const { return obj.id < id; }
};

int main()
{
	std::set<object> c;
	auto r = boost::irange(0, 10'000);

	for (auto i : r)
	{
		c.emplace(i);
	}

	int sum = 0;

	{
		boost::timer::auto_cpu_timer t;
		for (auto i : r)
		{
			auto it = c.find(i);
			sum += it->id;
		}
	}

	std::cout << sum;
}
