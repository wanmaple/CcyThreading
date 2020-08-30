#pragma once

#define NS_CCY_BEGIN namespace ccy {
#define NS_CCY_END }

#define UNCOPYABLE(__CLS__) __CLS__(const __CLS__ &) = delete;	\
__CLS__ &operator=(const __CLS__ &) = delete;

#include <cstdint>
#define int8 int8_t
#define int16 int16_t
#define int32 int32_t
#define int64 int64_t
#define uint8 uint8_t
#define uint16 uint16_t
#define uint32 uint32_t
#define uint64 uint64_t

#include <chrono>
#define SLEEP(__MS__) if (__MS__ > 0) std::this_thread::sleep_for(std::chrono::milliseconds(__MS__));

#include <functional>
#define BIND_0(__SELECTOR__, __TARGET__, ...) std::bind(&__SELECTOR__, __TARGET__, ##__VA_ARGS__)
#define BIND_1(__SELECTOR__, __TARGET__, ...) std::bind(&__SELECTOR__, __TARGET__, std::placeholders::_1, ##__VA_ARGS__)
#define BIND_2(__SELECTOR__, __TARGET__, ...) std::bind(&__SELECTOR__, __TARGET__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define BIND_3(__SELECTOR__, __TARGET__, ...) std::bind(&__SELECTOR__, __TARGET__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

#define THROW_IF(__COND__, __EX__) if (__COND__)	\
throw __EX__;
