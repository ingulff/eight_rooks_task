/**
 *  ᛝ
 */

#include "board/board.hpp"

namespace tt_program
{

board_t::board_t(std::int8_t rooks_count, tt_program::event_logger & logger)
	: m_board( {0} )
	, m_row_mutexes()
	, m_col_mutexes()
 	, m_rooks_synchronizer(rooks_count)
 	, m_logger(logger)
{}


bool board_t::try_make_horizontal_move(
	const std::string & fig_name, 
	const position_t & cur_position, 
	const position_t & new_position
) {
	std::scoped_lock row_lock(m_row_mutexes[cur_position.y], m_col_mutexes[new_position.x]);

	bool res = false;

	if( is_valid_position(cur_position) 
		&& is_valid_position(new_position) 
		&& can_make_horizontal_move(cur_position, new_position) )
	{
		set_position(new_position);
		clear_position(cur_position);
		res = true;
	}

	m_logger.log( { fig_name, cur_position, new_position, data(), res } );
	return res;
}

bool board_t::try_make_vertical_move(
	const std::string & fig_name, 
	const position_t & cur_position,
	const position_t & new_position
) {
	std::scoped_lock col_lock(m_col_mutexes[cur_position.x], m_row_mutexes[new_position.y]);

	bool res = false;

	if( is_valid_position(cur_position) 
		&& is_valid_position(new_position) 
		&& can_make_vertical_move(cur_position, new_position) )
	{
		set_position(new_position);
		clear_position(cur_position);
		res = true;
	}

	m_logger.log( { fig_name, cur_position, new_position, data(), res } );

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
	std::scoped_lock lock(m_row_mutexes[position.y], m_col_mutexes[position.x]);

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
	return (position.x < 8) && (position.y < 8);
}

bool board_t::can_make_vertical_move(const position_t & cur_position, const position_t & new_position)
{
	bool res = true;
	if(cur_position.x < new_position.x)
	{
		for(auto i = cur_position.x + 1, end = new_position.x + 1; i < end; ++i)
		{
			if( !!( m_board[i] & (1 << cur_position.y)) )
			{
				res = false;
				break;
			}
		}
	}
	else
	{
		for(auto i = new_position.x; i < cur_position.x; ++i)
		{
			if( !!( m_board[i] & (1 << cur_position.y)) )
			{
				res = false;
				break;
			}
		}
	}

	return res;
}

bool board_t::can_make_horizontal_move(const position_t & cur_position, const position_t & new_position)
{
	bool res = true;
	if(cur_position.y < new_position.y)
	{
		for(auto i = cur_position.y + 1, end = new_position.y + 1; i < end; ++i)
		{
			if( !!( m_board[cur_position.x] & (1 << i)) )
			{
				res = false;
				break;
			}
		}
	}
	else
	{
		for(auto i = new_position.y; i < cur_position.y; ++i)
		{
			if( !!( m_board[cur_position.x] & (1 << i)) )
			{
				res = false;
				break;
			}
		}
	}

	return res;
}


board_data_t board_t::data() const
{
	return m_board;
}



bool operator==(const position_t & left, const position_t & right)
{
	return (left.x == right.x) && (left.y == right.y);
}


std::ostream & operator<<(std::ostream & out, const tt_program::position_t & position)
{
	char alpha = 'A' + position.y;
	out << "(" << (position.x + 1) << ", " << alpha << ")";
	return out;
}

} // namespace tt_program

