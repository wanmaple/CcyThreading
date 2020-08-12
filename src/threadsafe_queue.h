#pragma once

#include "macroes.h"
#include <memory>
#include <mutex>
#include <condition_variable>
#include <queue>

NS_CCY_BEGIN

template<typename T>
class threadsafe_queue
{
public:
	threadsafe_queue() {}
	threadsafe_queue(const threadsafe_queue &other);
	threadsafe_queue &operator=(const threadsafe_queue &other);

	void push(T val);
	void wait_and_pop(T &val);
	std::shared_ptr<T> wait_and_pop();
	bool try_pop(T &val);
	std::shared_ptr<T> try_pop();
	bool empty() const;

private:
	mutable std::mutex _m;
	std::queue<T> _data;
	std::condition_variable _cond;
};

template<typename T>
inline threadsafe_queue<T>::threadsafe_queue(const threadsafe_queue & other)
{
	std::lock_guard<std::mutex> lock(other._m);
	_data = other._data;
}

template<typename T>
inline threadsafe_queue<T> & threadsafe_queue<T>::operator=(const threadsafe_queue<T> & other)
{
	std::lock(_m, other._m);
	std::lock_guard<std::mutex> lockS(_m, std::adopt_lock);
	std::lock_guard<std::mutex> lockO(other._m, std::adopt_lock);
	_data = other._data;
	return *this;
}

template<typename T>
inline void threadsafe_queue<T>::push(T val)
{
	std::lock_guard<std::mutex> lock(_m);
	_data.push(val);
	_cond.notify_one();
}

template<typename T>
inline void threadsafe_queue<T>::wait_and_pop(T & val)
{
	std::unique_lock<std::mutex> lock(_m);
	_cond.wait(lock, [this] { return !_data.empty(); });
	val = _data.front();
	_data.pop();
}

template<typename T>
inline std::shared_ptr<T> threadsafe_queue<T>::wait_and_pop()
{
	std::unique_lock<std::mutex> lock(_m);
	_cond.wait(lock, [this] { return !_data.empty(); });
	std::shared_ptr<T> ret(std::make_shared<T>(_data.front()));
	_data.pop();
	return ret;
}

template<typename T>
inline bool threadsafe_queue<T>::try_pop(T & val)
{
	std::lock_guard<std::mutex> lock(_m);
	if (_data.empty())
	{
		return false;
	}
	val = _data.front();
	_data.pop();
}

template<typename T>
inline std::shared_ptr<T> threadsafe_queue<T>::try_pop()
{
	std::lock_guard<std::mutex> lock(_m);
	if (_data.empty())
	{
		return std::shared_ptr<T>();
	}
	std::shared_ptr<T> ret(std::make_shared<T>(_data.front()));
	_data.pop();
	return ret;
}

template<typename T>
inline bool threadsafe_queue<T>::empty() const
{
	std::lock_guard<std::mutex> lock(_m);
	return _data.empty();
}

NS_CCY_END
