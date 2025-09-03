#include <so_5/all.hpp>
#include <opencv2/core/hal/interface.h>
#include "ImageTracer.h"

int main()
{
	const so_5::wrapped_env_t sobj;
	auto& environment = sobj.environment();

	auto mailbox = environment.introduce_coop([&](so_5::coop_t& coop) {
		return coop.make_agent<ImageTracer>()->so_direct_mbox();
	});

	send<cv::Mat>(mailbox, cv::Mat::ones(100, 100, CV_8U));
	send<cv::Mat>(mailbox, cv::Mat::ones(100, 200, CV_8U));
	send<cv::Mat>(mailbox, cv::Mat::ones(100, 300, CV_8U));
}
