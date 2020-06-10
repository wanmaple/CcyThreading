#pragma once

#include "macroes.h"
#include <thread>

NS_CCY_BEGIN

class scoped_thread
{
public:
	explicit scoped_thread(std::thread th);
	~scoped_thread();

	UNCOPYABLE(scoped_thread);

private:
	std::thread _th;
};

NS_CCY_END