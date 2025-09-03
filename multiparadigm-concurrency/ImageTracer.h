#pragma once

#include <print>
#include <so_5/all.hpp>
#include <opencv2/core/mat.hpp>

class ImageTracer : public so_5::agent_t {
public:
    ImageTracer(so_5::agent_context_t ctx, so_5::mbox_t input)
        : agent_t(ctx), m_input(std::move(input))
	{
    }

    void so_define_agent() override
	{
        so_subscribe(m_input).event([](const cv::Mat& image) {
            std::print("Got image: {}x{}\n", image.cols, image.rows);
        });
    }
private:
    so_5::mbox_t m_input;
};
