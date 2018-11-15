#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <boost/intrusive/list.hpp>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>

struct object : boost::intrusive::list_base_hook<>
{
	int id;
	object(int id) : id{ id } {}
};

int main()
{
	boost::intrusive::list<object> c;
	auto r = boost::irange(0, 10'000);

	std::vector<object> v;
	v.reserve(10'000);

	for (auto i : r)
	{
		v.emplace_back(i);
		c.push_back(v.back());
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
