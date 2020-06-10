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

thread_guard::thread_guard(thread_guard && other) noexcept
	: _th(other._th)
{
}

thread_guard & thread_guard::operator=(thread_guard && other) noexcept
{
	_th = std::move(other._th);
	return *this;
}

NS_CCY_END