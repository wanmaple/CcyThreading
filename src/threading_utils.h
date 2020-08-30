#pragma once

#include "macroes.h"
#include <future>

NS_CCY_BEGIN

class threading_utils
{
public:
	static uint32_t recommand_concurrency();

	template<typename F, typename... Args>
	static std::future<typename std::result_of<F(Args...)>::type> make_async(F &&func, Args &&... args);
};

template<typename F, typename ...Args>
inline std::future<typename std::result_of<F(Args...)>::type> threading_utils::make_async(F && func, Args && ...args)
{
	typedef typename std::result_of<F(Args...)>::type R;
	std::future<R> ret = std::async(func, args);
	return ret;
}

NS_CCY_END
