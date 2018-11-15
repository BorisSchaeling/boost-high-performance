#include <iterator>
#include <algorithm>
#include <iostream>
#include <boost/intrusive/list.hpp>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>

struct object : boost::intrusive::list_base_hook<>
{
	virtual ~object() = default;
	virtual int get() const = 0;
};

struct derived : object
{
	int id;
	char dummy[16];
	derived(int id) : id{ id } {}
	int get() const override { return id; }
};

struct derived2 : object
{
	int id;
	char dummy[32];
	derived2(int id) : id{ id } {}
	int get() const override { return id; }
};

int main()
{
	boost::intrusive::list<object> c;
	auto r = boost::irange(0, 10'000);

	std::vector<derived> v;
	v.reserve(5'000);

	std::vector<derived2> v2;
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
			sum += obj.get();
		}
	}

	std::cout << sum;
}
