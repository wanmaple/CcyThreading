#include <iostream>
#include <thread>
#include <vector>
#include "src/thread_guard.h"
#include "src/scoped_thread.h"
#include "src/threadsafe_queue.h"

using namespace std;
using namespace ccy;

class A
{
public:
	int i;
};

void doSth(int i)
{
	cout << i << endl;
}

int main()
{
	threadsafe_queue<int> queue;

	return 0;
}