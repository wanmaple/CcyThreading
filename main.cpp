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

int test1(int num)
{
    for (int i = 0; i < num; ++i) {
        cout << "TEST1 " << i << endl;
    }
    return num;
}

void test2(float num)
{
    float sum = 0.0f;
    for (int i = 0; i < 10000; ++i) {
        sum += i;
    }
    cout << "TEST2 " << (sum / num) << endl;
}

int main()
{
    auto f1 = threading_utils::make_async(test1, 1000);
    auto f2 = threading_utils::make_async(test2, 22225.0f);
    cout << f1.get() << endl;
    f2.wait();

	return 0;
}
