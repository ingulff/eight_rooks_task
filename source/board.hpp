#ifndef TT_BOARD_HPP
#define TT_BOARD_HPP

#include <array>
#include <mutex>

#include "utils/rooks_synchronizer.hpp"

namespace tt_program
{

struct position_t
{
	std::int8_t x;
	std::int8_t y;
};

class board_t
{

public:
	board_t(std::int8_t rooks_count);

	board_t(board_t & other) = delete;
	board_t & operator=(board_t & other) = delete;

	~board_t() = default;

	bool try_make_horizontal_move(const position_t & cur_position, const position_t & new_position);

	bool try_make_vertical_move(const position_t & cur_position, const position_t & new_position);

public:
	void wait_all_rooks();

	void add_rook();

	void start_game();

	bool set_start_position(const position_t & position);

private:
	bool has_figure(const position_t & position);

private:
	void set_position(const position_t & position);

	void clear_position(const position_t & position);

private:
	bool is_valid_position(const position_t & position);

	bool can_make_vertical_move(const position_t & cur_position, const position_t & new_position);

	bool can_make_horizontal_move(const position_t & cur_position, const position_t & new_position);

private:
	std::array<std::int8_t, 8> m_board;
	std::mutex m_mutex;
	tt_utils::rooks_synchronizer m_rooks_synchronizer;
};

} // namespace tt_program

#endif // TT_BOARD_HPP
