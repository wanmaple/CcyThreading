#include "thread_guard.h"

NS_CCY_BEGIN

thread_guard::thread_guard(std::thread & th)
	: _th(th)
{
}

thread_guard::~thread_guard()
{
	if (_th.joinable())
	{
		_th.join();
	}
}

NS_CCY_END