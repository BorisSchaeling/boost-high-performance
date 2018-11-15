#include <iterator>
#include <algorithm>
#include <iostream>
#include <boost/poly_collection/any_collection.hpp>
#include <boost/type_erasure/member.hpp>
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

BOOST_TYPE_ERASURE_MEMBER((has_get), get, 0)
using get_interface = has_get<int(), const boost::type_erasure::_self>;

int main()
{
	boost::any_collection<get_interface> c;
	auto r = boost::irange(0, 10'000);

	for (auto i : r)
	{
		if (i % 2)
			c.insert(object{ i });
		else
			c.insert(object2{ i });
	}

	int sum = 0;

	{
		boost::timer::auto_cpu_timer t;
		for (auto i : r)
		{
			auto it = std::find_if(std::begin(c), std::end(c),
				[i](const auto &obj) { return obj.get() == i; });
			sum += it->get();
		}
	}

	std::cout << sum;
}
