#include "scoped_thread.h"
#include <stdexcept>

NS_CCY_BEGIN

scoped_thread::scoped_thread(std::thread th)
	: _th(std::move(th))
{
	if (!_th.joinable())
	{
		throw std::logic_error("Invalid thread.");
	}
}

scoped_thread::~scoped_thread()
{
	_th.join();
}

NS_CCY_END
