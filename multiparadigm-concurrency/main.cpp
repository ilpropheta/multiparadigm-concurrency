#include <so_5/all.hpp>
#include <opencv2/core/hal/interface.h>
#include "ImageTracer.h"

int main()
{
	const so_5::wrapped_env_t sobj;
	auto& environment = sobj.environment();

	auto tracer = environment.make_agent<ImageTracer>();
	const auto mailbox = tracer->so_direct_mbox();
	environment.register_agent_as_coop(std::move(tracer));

	send<cv::Mat>(mailbox, cv::Mat::ones(100, 100, CV_8U));
	send<cv::Mat>(mailbox, cv::Mat::ones(100, 200, CV_8U));
	send<cv::Mat>(mailbox, cv::Mat::ones(100, 300, CV_8U));
}
