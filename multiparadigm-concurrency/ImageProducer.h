#pragma once
#include <print>
#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>
#include <so_5/all.hpp>
#include "commands.h"

class ImageProducer : public so_5::agent_t
{
    struct grab_image final : so_5::signal_t {};
public:
    ImageProducer(so_5::agent_context_t ctx, so_5::mbox_t output, so_5::mbox_t commands)
        : agent_t(std::move(ctx)), m_output(std::move(output)), m_commands(std::move(commands)), m_capture(0, cv::CAP_DSHOW) {
    }


    void so_define_agent() override
	{
        st_started.event([this](mhood_t<grab_image>) {
            cv::Mat mat;
            m_capture >> mat;
            send<cv::Mat>(m_output, std::move(mat));
            send<grab_image>(*this);
        }).event(m_commands, [this](mhood_t<commands::stop_acquisition>) {
            std::print("Stopping image acquisition...\n");
        	st_stopped.activate();
        });

    	st_stopped.event(m_commands, [this](mhood_t<commands::start_acquisition>) {
            std::print("Starting image acquisition...\n");
    		st_started.activate();
    		send<grab_image>(*this);
    	});

        st_stopped.activate();
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
    state_t st_stopped{ this }, st_started{ this };

	so_5::mbox_t m_output;
    so_5::mbox_t m_commands;
    cv::VideoCapture m_capture;
};
