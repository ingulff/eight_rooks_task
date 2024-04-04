/**
 *  ᛝ
 */

#include <mutex>

#include <cstdint>

#include "board.hpp"

namespace tt_program
{

board_t::board_t(std::int8_t rooks_count)
	: m_board( {0} )
	, m_mutex()
 	, m_rooks_synchronizer(m_mutex, rooks_count)
{}


bool board_t::try_make_horizontal_move(const position_t & cur_position, const position_t & new_position)
{
	std::lock_guard lock(m_mutex);

	bool res = false;

	if( is_valid_position(cur_position) 
		&& is_valid_position(new_position) 
		&& can_make_horizontal_move(cur_position, new_position) )
	{
		set_position(new_position);
		clear_position(cur_position);
		res = true;
	}

	return res;
}

bool board_t::try_make_vertical_move(const position_t & cur_position, const position_t & new_position)
{
	std::lock_guard lock(m_mutex);

	bool res = false;

	if( is_valid_position(cur_position) 
		&& is_valid_position(new_position) 
		&& can_make_vertical_move(cur_position, new_position) )
	{
		set_position(new_position);
		clear_position(cur_position);
		res = true;
	}

	return res;
}


void board_t::wait_all_rooks()
{
	add_rook();
	m_rooks_synchronizer.wait();
}

void board_t::add_rook()
{
	m_rooks_synchronizer.add_rook_to_active();
}

void board_t::start_game()
{
	m_rooks_synchronizer.notify_all();
}

bool board_t::set_start_position(const position_t & position)
{
	std::lock_guard lock(m_mutex);

	bool res = false;

	if( is_valid_position(position) && (has_figure(position) == false) )
	{
		res = true;
		set_position(position);
	}

	return res;
}


bool board_t::has_figure(const position_t & position)
{
	// x - строка на доске, y - номер ячейки в строке
	return !!(m_board[position.x] & (1 << position.y));
}


void board_t::set_position(const position_t & position)
{
	m_board[position.x] |= (1 << position.y);
}

void board_t::clear_position(const position_t & position)
{
	m_board[position.x] &= ~(1 << position.y);
}


bool board_t::is_valid_position(const position_t & position)
{
	return (position.x > -1) && (position.x < 64) && (position.y > -1) && (position.y < 64);
}

bool board_t::can_make_vertical_move(const position_t & cur_position, const position_t & new_position)
{
	bool res = true;
	for(auto i = std::min(cur_position.x, new_position.x),
			end = std::max(cur_position.x, new_position.x);
			i < end; ++i)
	{
		if(m_board[i] & ( 1 << new_position.y))
		{
			res = false;
			break;
		}
	}

	return res;
}

bool board_t::can_make_horizontal_move(const position_t & cur_position, const position_t & new_position)
{
	bool res = true;
	for(auto i = std::min(cur_position.y, new_position.y),
			end = std::max(cur_position.y, new_position.y);
			i < end; ++i)
	{
		if(m_board[new_position.x] & ( 1 << i))
		{
			res = false;
			break;
		}
	}

	return res;

}

} // namespace tt_program

