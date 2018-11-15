#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>
#define BOOST_POOL_NO_MT
#include <boost/pool/pool_alloc.hpp>

int main()
{
	using allocator = boost::fast_pool_allocator<
		int, 
		boost::default_user_allocator_new_delete, 
		boost::details::pool::default_mutex, 
		1,
		4
	>;

	auto r = boost::irange(0, 10'000);
	std::list<int, allocator> c(std::begin(r), std::end(r));

	int sum = 0;

	{
		boost::timer::auto_cpu_timer t;
		for (auto i : r)
		{
			auto it = std::find(std::begin(c), std::end(c), i);
			sum += *it;
		}
	}

	std::cout << sum;
}
