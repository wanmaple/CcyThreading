#pragma once

#include "macroes.h"
#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#include <functional>

NS_CCY_BEGIN

class empty_stack_error : public std::exception
{
public:
	const char *what() const throw();
};

template<typename T>
class ccy_stack
{
public:
	ccy_stack() {}
	ccy_stack(const ccy_stack &other);

	ccy_stack &operator=(const ccy_stack &) = delete;

	void push(T val);
	std::shared_ptr<T> pop();
	void pop(T &val);
	bool pop_if(const std::function<bool(T)> &condition);
	bool empty() const;

private:
	std::stack<T> _data;
	mutable std::mutex _m;
};

template<typename T>
ccy_stack<T>::ccy_stack(const ccy_stack<T> &other)
{
	std::lock_guard<std::mutex> lock(_m);
	_data = other._data;
}

template<typename T>
void ccy_stack<T>::push(T val)
{
	std::lock_guard<std::mutex> lock(_m);
	_data.push(val);
}

template<typename T>
std::shared_ptr<T> ccy_stack<T>::pop()
{
	std::lock_guard<std::mutex> lock(_m);
	if (_data.empty())
	{
		throw empty_stack_error();
	}
	const std::shared_ptr<T> ret(std::make_shared<T>(_data.top()));
	_data.pop();
	return ret;
}

template<typename T>
bool ccy_stack<T>::pop_if(const std::function<bool(T)> &condition)
{
	std::lock_guard<std::mutex> lock(_m);
	if (condition == nullptr)
	{
		return false;
	}
	if (_data.empty())
	{
		throw empty_stack_error();
	}
	const std::shared_ptr<T> top(std::make_shared<T>(_data.top()));
	if (condition(top.get()))
	{
		_data.pop();
		return true;
	}
	return false;
}

template<typename T>
void ccy_stack<T>::pop(T &val)
{
	std::lock_guard<std::mutex> lock(_m);
	if (_data.empty())
	{
		throw empty_stack_error();
	}
	val = _data.top();
	_data.pop();
}

template<typename T>
bool ccy_stack<T>::empty() const
{
	std::lock_guard<std::mutex> lock(_m);
	if (_data.empty())
	{
		throw empty_stack_error();
	}
	return _data.empty();
}

NS_CCY_END