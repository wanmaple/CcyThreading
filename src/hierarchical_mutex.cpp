#include "hierarchical_mutex.h"

NS_CCY_BEGIN

thread_local uint64 hierarchical_mutex::THIS_THREAD_HIERARCHY_VALUE = 0xffffffffUL;

hierarchical_mutex::hierarchical_mutex(uint64 val)
	: _hierarchy_val(val)
	, _prev_hierarchy_val(0)
{
}

void hierarchical_mutex::lock()
{
	check_for_hierarchy_violation_and_throw();
	_m.lock();
	update_hierarchy_value();
}

void hierarchical_mutex::unlock()
{
	THIS_THREAD_HIERARCHY_VALUE = _prev_hierarchy_val;
	_m.unlock();
}

bool hierarchical_mutex::try_lock()
{
	if (!check_for_hierarchy_violation())
	{
		return false;
	}
	if (!_m.try_lock())
	{
		return false;
	}
	update_hierarchy_value();
	return true;
}

void hierarchical_mutex::check_for_hierarchy_violation_and_throw()
{
	THROW_IF(THIS_THREAD_HIERARCHY_VALUE <= _hierarchy_val, std::logic_error("mutex hierarchy violated."));
}

bool hierarchical_mutex::check_for_hierarchy_violation()
{
	return THIS_THREAD_HIERARCHY_VALUE > _hierarchy_val;
}

void hierarchical_mutex::update_hierarchy_value()
{
	_prev_hierarchy_val = THIS_THREAD_HIERARCHY_VALUE;
	THIS_THREAD_HIERARCHY_VALUE = _hierarchy_val;
}

NS_CCY_END