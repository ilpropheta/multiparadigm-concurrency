#pragma once
#include <so_5/all.hpp>
#include <opencv2/core/mat.hpp>
#include <syncstream>

class SlowClientSender : public so_5::agent_t
{
public:
	SlowClientSender(context_t ctx, so_5::mbox_t input, so_5::mchain_t output)
		: agent_t(ctx), m_input(std::move(input)), m_output(std::move(output))
	{
	}

	void so_define_agent() override
	{
		so_subscribe(m_input).event([this](so_5::mhood_t<cv::Mat> img) {
			if (select(so_5::from_all().handle_n(1).no_wait_on_empty(),
				send_case(m_output, img.make_holder(), [this] {
					std::osyncstream(std::cout) << "Image sent to slow client. Lost frame count: " << m_lostCount << "\n";
					m_lostCount = 0;
				})).sent() == 0)
			{
				m_lostCount++;
			}
		});
	}
private:
	so_5::mbox_t m_input;
	so_5::mchain_t m_output;
	int m_lostCount = 0;
};