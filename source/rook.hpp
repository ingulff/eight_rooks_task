#ifndef TT_ROOK_HPP
#define TT_ROOK_HPP

#include <chrono>
#include <random>

#include <cstdint>

#include "board.hpp"

namespace tt_program
{

class rook_t
{
public:
	rook_t(tt_program::board_t & board,
			std::int32_t min_move_timeout,
			std::int32_t max_move_timeout,
			std::int32_t wait_move_timeout,
			std::int32_t move_count);

public:
	void wait_start_game();
	void start_moves();

private:
	enum class move_direction : std::int8_t
	{
		horizontal = 0,
		vertical = 1,
	};


	struct move_t
	{
		move_direction dir;
		std::int8_t next_pos;
	};

private:
	void wait_timeout( std::chrono::milliseconds time );

	std::int32_t wait_next_move();

	move_t generate_next_move();

	void generate_start_pos();

	void make_next_move();

private:
	tt_program::board_t & m_board;
	std::uniform_int_distribution<> m_wait_distr;
	const std::int32_t m_wait_move_timeout;
	std::int32_t m_move_count;
	tt_program::position_t m_cur_pos;
};

} // namespace tt_program

#endif // TT_ROOK_HPP
