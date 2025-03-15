#ifndef TT_BOARD_HPP
#define TT_BOARD_HPP

#include <array>
#include <mutex>

#include <cstdint>

#include "board/board_helpers.hpp"
#include "board/position.hpp"
#include "logger/logger.hpp"
#include "utils/rooks_synchronizer.hpp"

namespace tt_program
{

class board_t
{
public:
	board_t(std::int8_t rooks_count, tt_program::event_logger & logger);

	board_t(board_t & other) = delete;
	board_t & operator=(board_t & other) = delete;

	~board_t() = default;

	bool try_make_horizontal_move(const std::string & fig_name, const position_t & cur_position, const position_t & new_position);

	bool try_make_vertical_move(const std::string & fig_name, const position_t & cur_position, const position_t & new_position);

public:

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

public:
	board_data_t data() const;

public:
	struct move_conditions
	{
		std::condition_variable& col_conditional;
		std::condition_variable& raw_conditional;
	};

	move_conditions get_move_conditions(const position_t & position);

private:
	std::array<data_t, 8> m_board;
	std::array<std::mutex, 8> m_row_mutexes;
	std::array<std::mutex, 8> m_col_mutexes;
	std::array<std::condition_variable, 8> m_row_move_conditions;
	std::array<std::condition_variable, 8> m_col_move_conditions;
	tt_utils::rooks_synchronizer m_rooks_synchronizer;

	tt_program::event_logger & m_logger;
};

} // namespace tt_program

#endif // TT_BOARD_HPP
