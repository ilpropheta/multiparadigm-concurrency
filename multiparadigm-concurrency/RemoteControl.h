#pragma once
#include <so_5/all.hpp>
#include "commands.h"

class RemoteControl : public so_5::agent_t
{
public:
	RemoteControl(so_5::agent_context_t ctx, so_5::mbox_t input, so_5::mbox_t output)
		: agent_t(std::move(ctx)), m_input(std::move(input)), m_output(std::move(output))
	{
	}

	void so_define_agent() override
	{
		so_subscribe(m_input).event([this](const std::string& cmd) {
			if (cmd == "1")
			{
				std::print("Starting image acquisition...\n");
				so_5::send<commands::start_acquisition>(m_output);
			}
			else if (cmd == "2")
			{
				std::print("Stopping image acquisition...\n");
				so_5::send<commands::stop_acquisition>(m_output);
			}
			else if (cmd.starts_with("3")) {
				so_5::send<commands::start_acquisition>(m_output);
				so_5::send_delayed<commands::stop_acquisition>(m_output, std::chrono::seconds(stoi(cmd.substr(1))));
			}
		});
	}

private:
	so_5::mbox_t m_input;
	so_5::mbox_t m_output;
};
