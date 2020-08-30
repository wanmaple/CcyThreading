#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include "src/thread_guard.h"
#include "src/scoped_thread.h"
#include "src/threadsafe_queue.h"
#include "src/threading_utils.h"
#include "src/hierarchical_mutex.h"

using namespace std;
using namespace ccy;

class A
{
public:
	int test(float a)
	{
		return (int)(a * 100.0f);
	}
};

hierarchical_mutex g_m1000(1000u);
hierarchical_mutex g_m100(100u);

void test1()
{
	std::lock_guard<hierarchical_mutex> lock(g_m1000);
	for (size_t i = 0; i < 1000; i++)
	{
		cout << i << endl;
	}
}

void test2()
{
	std::lock_guard<hierarchical_mutex> lock(g_m100);
	SLEEP(1000);
	for (size_t i = 0; i < 1000; i++)
	{
		cout << (i + 20000) << endl;
	}
}

int main()
{
	test1();
	test2();

	return 0;
}