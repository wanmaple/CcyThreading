#pragma once

#include "macroes.h"
#include <mutex>

NS_CCY_BEGIN

class hierarchical_mutex
{
public:
	explicit hierarchical_mutex(uint64 val);

	void lock();
	void unlock();
	bool try_lock();

private:
	static thread_local uint64 THIS_THREAD_HIERARCHY_VALUE;

	void check_for_hierarchy_violation();
	void update_hierarchy_value();

	std::mutex _m;
	const uint64 _hierarchy_val;
	uint64 _prev_hierarchy_val;
};

NS_CCY_END