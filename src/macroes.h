#pragma once

#define NS_CCY_BEGIN namespace ccy {
#define NS_CCY_END }

#define UNCOPYABLE(__CLS__) __CLS__(const __CLS__ &) = delete;	\
__CLS__ &operator=(const __CLS__ &) = delete;

#include <cstdint>
#define uint8 uint8_t
#define uint16 uint16_t
#define uint32 uint32_t
#define uint64 uint64_t