#include <so_5/all.hpp>
#include "ImageProducer.h"
#include "ImageTracer.h"
#include "ImageViewer.h"
#include "RemoteControl.h"

static void SendKeyboardInputTo(const so_5::mbox_t& destination)
{
	std::string cmd;
	while (std::getline(std::cin, cmd))
	{
		if (cmd.empty())
			break;
		send<std::string>(destination, std::move(cmd));
	}
}

int main()
{
	const so_5::wrapped_env_t sobj;
	auto& environment = sobj.environment();

	const auto imageCh = environment.create_mbox("raw-images");
	const auto commandsCh = environment.create_mbox("commands");
	const auto keyboardCh = environment.create_mbox();

	environment.introduce_coop([&](so_5::coop_t& coop) {
		coop.make_agent<ImageProducer>(imageCh);
		coop.make_agent<ImageViewer>(imageCh);
		coop.make_agent<RemoteControl>(keyboardCh, commandsCh);
	});

	SendKeyboardInputTo(keyboardCh);
}
