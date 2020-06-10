#pragma once

#include "macroes.h"
#include <thread>

NS_CCY_BEGIN

// RAII idiom of thread.
class thread_guard
{
public:
	explicit thread_guard(std::thread &th);
	~thread_guard();

	thread_guard(thread_guard &&other) noexcept;
	thread_guard &operator=(thread_guard &&other) noexcept;
	UNCOPYABLE(thread_guard);

private:
	std::thread &_th;
};

NS_CCY_END