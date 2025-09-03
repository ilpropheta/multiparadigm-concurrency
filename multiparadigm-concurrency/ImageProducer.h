#pragma once
#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>
#include <so_5/all.hpp>

class ImageProducer : public so_5::agent_t
{
    struct grab_image final : so_5::signal_t {};
public:
    ImageProducer(so_5::agent_context_t ctx, so_5::mbox_t output)
        : agent_t(std::move(ctx)), m_output(std::move(output)), m_capture(0, cv::CAP_DSHOW)
	{
    }

    void so_define_agent() override
	{
        so_subscribe_self().event([this](mhood_t<grab_image>) {
            cv::Mat mat;
            m_capture >> mat;
            send<cv::Mat>(m_output, std::move(mat));
            send<grab_image>(*this);
        });
    }

    void so_evt_start() override
	{
        if (!m_capture.isOpened())
        {
            throw std::runtime_error("Can't connect to the webcam");
        }
        send<grab_image>(*this);
    }
private:
	so_5::mbox_t m_output;
    cv::VideoCapture m_capture;
};
