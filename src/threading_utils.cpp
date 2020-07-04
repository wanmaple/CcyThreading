#include "threading_utils.h"
#include <thread>

NS_CCY_BEGIN

uint32_t threading_utils::recommand_concurrency()
{
	uint32_t cores = std::thread::hardware_concurrency();
	if (cores == 0)
	{
		// information not available
		return 1;
	}
	return cores;
}

NS_CCY_END