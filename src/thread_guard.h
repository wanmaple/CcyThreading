#pragma once

#include "macroes.h"
#include <thread>

NS_CCY_BEGIN

class thread_guard
{
public:
	explicit thread_guard(std::thread &th);
	~thread_guard();

	thread_guard(const thread_guard &) = delete;
	thread_guard &operator=(const thread_guard &) = delete;

private:
	std::thread &_th;
};

NS_CCY_END