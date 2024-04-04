/**
 *  ᛝ
 */

#include <iostream>
#include <utility>

#include <cstdint>

#include "logger/logger.hpp"

namespace tt_program
{

inline namespace details
{

void print_board(std::ostream & out, tt_program::const_data_ptr board_data)
{
	std::string_view board_aplha = "  |A |B |C |D |E |F |G |H |   \n";
	std::string_view board_border = "-----------------------------\n";
	out << board_aplha <<  board_border; 
	for(std::uint8_t i = 0; i < 8; ++i)
	{
		out << (i+1) << " |";
		for(std::uint8_t j = 0; j < 8; ++j)
		{
			bool is_empty = !!((*(board_data+i)) & (1 << j));
			if(is_empty == false)
			{
				out << "  |";
			}
			else
			{
				out << "R |";
			}
		}
		out << " " << (i+1) << "\n";
	}
	out << board_border << board_aplha;
}

std::ostream & operator<<(std::ostream & out, const tt_program::event_logger::event_t & event)
{
	out << event.figure_name << " try move: " << event.start << " -> " << event.end << std::endl;
	print_board(out, event.board_data);
	return out;
}


} // namespace details


event_logger::event_logger()
	: m_event_queue()
	, m_mutex()
	, m_event_guard()
	, m_thread()
	, m_timer("program")
	, m_is_active(false)
{}

event_logger::~event_logger()
{
	if(m_thread.joinable())
	{
		m_thread.join();
	}
}


void event_logger::log(event_t event)
{
	{
		std::lock_guard lock(m_mutex);

		m_event_queue.emplace(std::move(event));
	}

	m_event_guard.notify_one();
}


void event_logger::log_events()
{
	while( m_is_active )
	{
		std::unique_lock lock(m_mutex);
		m_event_guard.wait(lock, [this](){ return this->has_events(); } );
		
		lock.unlock();
		while(m_event_queue.empty() == false)
		{
			auto event = m_event_queue.front();
			m_event_queue.pop();
			std::cout << event << std::endl;
		}

	}
}

bool event_logger::has_events()
{
	return (m_is_active == true) && (m_event_queue.empty() == false);
}


void event_logger::start()
{
	m_is_active.store(true);
	m_thread = std::thread([this](){ this->log_events(); });
}

void event_logger::stop()
{
//std::cout << "stoP()" << std::endl;
	m_is_active.store(false);

	if(m_thread.joinable())
	{
		m_thread.join();
	}

	m_event_guard.notify_one();
}

} // namespace tt_program
