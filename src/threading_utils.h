#pragma once

#include "macroes.h"
#include <future>

NS_CCY_BEGIN

class threading_utils
{
public:
	static uint32_t recommand_concurrency();

	template<typename F>
	static std::future<typename std::result_of<F()>::type> make_async(F func);
};

template<typename F>
inline std::future<typename std::result_of<F()>::type> threading_utils::make_async(F func)
{
	typedef typename std::result_of<F()>::type R;
	std::future<R> ret = std::async(func);
	return ret;
}

NS_CCY_END
