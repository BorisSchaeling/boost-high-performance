#include <queue>
#include <thread>
#include <mutex>
#include <iostream>
#include <boost/range/irange.hpp>
#include <boost/timer/timer.hpp>

class queue
{
public:
	void push(int i)
	{
		std::lock_guard<std::mutex> l{ m };
		q.push(i);
	}

	bool pop(int &i)
	{
		std::lock_guard<std::mutex> l{ m };
		if (!q.empty())
		{
			i = q.front();
			q.pop();
			return true;
		}
		return false;
	}

private:
	std::mutex m;
	std::queue<int> q;
};

queue q;
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
