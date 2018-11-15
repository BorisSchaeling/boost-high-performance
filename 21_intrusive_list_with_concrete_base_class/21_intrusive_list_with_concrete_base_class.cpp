#include <iterator>
#include <algorithm>
#include <iostream>
#include <boost/intrusive/list.hpp>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>

struct object : boost::intrusive::list_base_hook<>
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
	boost::intrusive::list<object> c;
	auto r = boost::irange(0, 10'000);

	std::vector<object> v;
	v.reserve(5'000);

	std::vector<derived> v2;
	v2.reserve(5'000);

	for (auto i : r)
	{
		if (i < 5000)
		{
			v.emplace_back(i);
			c.push_back(v.back());
		}
		else
		{
			v2.emplace_back(i);
			c.push_back(v2.back());
		}
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
