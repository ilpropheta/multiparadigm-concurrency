#pragma once
#include <syncstream>
#include <opencv2/imgproc.hpp>
#include <so_5/mchain.hpp>

inline [[nodiscard]]std::jthread SpawnSlowClient(const so_5::mchain_t& channel)
{
	return std::jthread{ [=] {
		receive(so_5::from(channel).handle_all(), [](const cv::Mat& frame) {
			cv::Mat out;
			cv::GaussianBlur(frame, out, { 251, 251 }, 0.0); // simulating slow processing
			std::osyncstream(std::cout) << "Slow client processed one frame\n";
		});
	} };
}
