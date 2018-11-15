#include <iterator>
#include <algorithm>
#include <iostream>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>
#include <boost/poly_collection/base_collection.hpp>

struct object
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
	boost::base_collection<object> c;
	auto r = boost::irange(0, 100'000);

	for (auto i : r)
	{
		if (i % 2)
			c.insert(derived{ i });
		else
			c.insert(derived2{ i });
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
