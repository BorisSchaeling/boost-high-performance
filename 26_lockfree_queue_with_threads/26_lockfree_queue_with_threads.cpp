#include <boost/lockfree/queue.hpp>
#include <thread>
#include <iostream>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>

boost::lockfree::queue<int, boost::lockfree::capacity<10'000>> q;
int sum = 0;

void produce()
{
	for (auto i : boost::irange(0, 10'000))
		q.push(i);
}

void consume()
{
	int i;
	while (q.pop(i))
		sum += i;
}

int main()
{
	{
		boost::timer::auto_cpu_timer t;
		std::thread t1{ produce };
		std::thread t2{ consume };
		t1.join();
		t2.join();
		consume();
	}

	std::cout << sum;
}
