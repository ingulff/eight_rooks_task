/**
 *  ᛝ
 */

#include <thread>

#include "board/position.hpp"
#include "figures/rook.hpp"

namespace tt_program
{

template<typename T>
T rand_between( std::uniform_int_distribution<T> & distr )
{
    static std::random_device rd; 
    static std::mt19937 eng( rd( ) );

    return distr( eng );
}

std::string generate_rook_name()
{
	static int number = 1;

	return std::to_string(number++);
}


rook_t::rook_t(tt_program::board_t & board,
			std::int32_t min_move_timeout,
			std::int32_t max_move_timeout,
			std::int32_t wait_move_timeout,
			std::int32_t move_count)
		: m_board(board)
		, m_wait_distr(min_move_timeout, max_move_timeout)
		, m_wait_move_timeout(wait_move_timeout)
		, m_move_count(move_count)
		, m_cur_pos()
		, m_name(generate_rook_name())
{}


void rook_t::wait_start_game()
{
	m_board.wait_all_rooks();
	start_moves();
}

void rook_t::start_moves() 
{
	do 
	{
		generate_start_pos();
	}
	while( m_board.set_start_position( m_cur_pos ) == false );
	

	while(m_move_count > 0)
	{
//std::cout << "start_moves() - " << m_move_count << std::endl;
		make_next_move();
		--m_move_count;
	}

//std::cout << "start_moves() - end" << std::endl;
}


void rook_t::wait_timeout( std::chrono::milliseconds time )
{
	std::this_thread::sleep_for( time );
}

std::int32_t rook_t::wait_next_move()
{
	auto next_timeout = rand_between( m_wait_distr );
	wait_timeout( std::chrono::milliseconds( next_timeout ) );

	return next_timeout;
}

rook_t::move_t rook_t::generate_next_move()
{
	static std::uniform_int_distribution<> move_distr(1, 8);

	move_t next_move;

	next_move.dir = (rand_between<int>(move_distr) & 1) ? rook_t::move_direction::vertical : rook_t::move_direction::horizontal;
	next_move.next_pos = rand_between(move_distr)-1;

	return next_move;
}

void rook_t::generate_start_pos()
{
	auto next_vert_pos = generate_next_move();
	auto next_hor_pos = generate_next_move();

	m_cur_pos.x = next_hor_pos.next_pos;
	m_cur_pos.y = next_vert_pos.next_pos;
//std::cout << "generate_start_pos() - (" << (int)m_cur_pos.x << ", " << (int)m_cur_pos.y << ")" << std::endl;
}


void rook_t::make_next_move()
{
	std::int32_t remainder_timeout = -1;
	bool is_successs_move = false;
	tt_program::position_t next_pos = m_cur_pos;
	move_t next_move;

	while( (is_successs_move == false) )
	{
		auto timeout = wait_next_move();
		remainder_timeout -= timeout;
//std::cout << "reminder_timeout: " << remainder_timeout << std::endl;
		if(remainder_timeout < 1)
		{
			remainder_timeout = m_wait_move_timeout;
			next_pos = m_cur_pos; // обнуляем клетку в которую хотели пойти

			while(next_pos == m_cur_pos)
			{
				next_move = generate_next_move();
				if(next_move.dir == rook_t::move_direction::vertical)
				{
					next_pos.x = next_move.next_pos;
					next_pos.y = m_cur_pos.y;
				}
				else
				{
					next_pos.x = m_cur_pos.x;
					next_pos.y = next_move.next_pos;
				}
			}

		}
//std::cout << "next_move: (" << (int)m_cur_pos.x << ", " << (int)m_cur_pos.y << ") -> (" << (int)(int)next_pos.x << ", " << (int)next_pos.y << ")" << std::endl;

		if(next_move.dir == rook_t::move_direction::vertical)
		{
			is_successs_move = m_board.try_make_vertical_move(m_name, m_cur_pos, next_pos);
		}
		else
		{
			is_successs_move = m_board.try_make_horizontal_move(m_name, m_cur_pos, next_pos);
		}

		if(is_successs_move)
		{
			remainder_timeout = -1;
			m_cur_pos = next_pos;
		}
	}
}

} // tt_program
