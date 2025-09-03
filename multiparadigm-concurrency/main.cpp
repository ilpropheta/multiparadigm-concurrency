#include <so_5/all.hpp>
#include "ImageProducer.h"
#include "ImageTracer.h"

int main()
{
	std::stop_source stop_source;
	const so_5::wrapped_env_t sobj;
	auto& environment = sobj.environment();

	auto mailbox = environment.create_mbox();
	auto binder = so_5::disp::active_obj::make_dispatcher(environment).binder();
	environment.introduce_coop([&](so_5::coop_t& coop) {
		coop.make_agent_with_binder<ImageProducer>(binder, mailbox);
		coop.make_agent<ImageTracer>(mailbox);
	});

	std::cin.get();
	stop_source.request_stop();
}
