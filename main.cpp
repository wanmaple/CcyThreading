#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include "src/thread_guard.h"
#include "src/scoped_thread.h"
#include "src/threadsafe_queue.h"
#include "src/threading_utils.h"

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

void test()
{
	cout << "TEST" << endl;
}

int main()
{
	A a;
	auto f1 = threading_utils::make_async(BIND_0(A::test, a, 1.1f));
	auto f2 = threading_utils::make_async(BIND_0(A::test, a, 0.21f));
	auto f3 = threading_utils::make_async(test);
	cout << f1.get() << endl;
	cout << f2.get() << endl;
	f3.wait();

	return 0;
}