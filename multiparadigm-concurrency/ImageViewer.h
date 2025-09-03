#pragma once
#include <so_5/agent.hpp>
#include <opencv2/highgui.hpp>

class ImageViewer : public so_5::agent_t
{
public:
    ImageViewer(so_5::agent_context_t ctx, so_5::mbox_t channel)
        : agent_t(std::move(ctx)), m_channel(std::move(channel))
    {
    }

    void so_define_agent() override
    {
        so_subscribe(m_channel).event([this](const cv::Mat& image) {
            imshow(m_channel->query_name(), image);
            cv::waitKey(25);
        });
    }

private:
    so_5::mbox_t m_channel;
};
