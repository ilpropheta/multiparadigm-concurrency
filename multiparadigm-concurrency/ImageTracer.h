#pragma once

#include <print>
#include <so_5/all.hpp>
#include <opencv2/core/mat.hpp>

class ImageTracer : public so_5::agent_t
{
public:
    using agent_t::agent_t;

    void so_define_agent() override
    {
        so_subscribe_self().event([](const cv::Mat& image) {
            std::print("received Image {}x{}\n", image.cols, image.rows);
        });
    }
};