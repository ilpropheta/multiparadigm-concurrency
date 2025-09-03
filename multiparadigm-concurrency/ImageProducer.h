#pragma once
#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>
#include <so_5/all.hpp>

class ImageProducer : public so_5::agent_t {
public:
	ImageProducer(so_5::agent_context_t ctx, so_5::mbox_t output, std::stop_token st)
		: agent_t(std::move(ctx)), m_output(std::move(output)), m_stop(std::move(st))
	{}

	void so_evt_start() override
	{
		cv::VideoCapture cap(0, cv::CAP_DSHOW);
		if (!cap.isOpened())
		{
			throw std::runtime_error("Can't connect to the webcam");
		}
		cv::Mat image;
		while (!m_stop.stop_requested())
		{
			cap >> image; // !!! not checking any errors here...
			so_5::send<cv::Mat>(m_output, std::move(image));
		}
	}
private:
	so_5::mbox_t m_output;
	std::stop_token m_stop;
};
