#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <boost/intrusive/splay_set.hpp>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>

struct object : boost::intrusive::bs_set_base_hook<>
{
	int id;
	object(int id) : id{ id } {}
	bool operator<(const object &obj) const { return obj.id < id; }
};

int main()
{
	boost::intrusive::splay_set<object> c;
	auto r = boost::irange(0, 10'000);

	std::vector<object> v;
	v.reserve(10'000);

	for (auto i : r)
	{
		v.emplace_back(i);
		c.insert(v.back());
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
