#ifndef TT_LOGGER_HPP
#define TT_LOGGER_HPP

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>
#include <queue>

#include "board/board_helpers.hpp"
#include "board/position.hpp"
#include "utils/auto_cpu_timer.hpp"

namespace tt_program
{

class event_logger
{
public:
	event_logger();

	~event_logger();

public:
	struct event_t
	{
		std::string figure_name;
		tt_program::position_t start;
		tt_program::position_t end;
		tt_program::const_data_ptr board_data;
		bool is_move_success;
	};

	void log(event_t event);

private:
	void log_events();

private:
	bool has_events();

public:
	void start();

	void stop();

private:
	std::queue<event_t> m_event_queue;
	std::mutex m_mutex;
	std::condition_variable m_event_guard;
	std::thread m_thread;

	tt_utils::auto_cpu_timer m_timer;

	std::atomic_bool m_is_active;
};

} // namespace tt_program

#endif // TT_LOGGER_HPP