#pragma once
#include <so_5/message.hpp>

namespace commands
{
	struct start_acquisition final : so_5::signal_t {};
	struct stop_acquisition final : so_5::signal_t {};
}
