#ifndef TT_SETTINGS_HPP
#define TT_SETTINGS_HPP

#include <cstdint>

namespace tt_program
{

struct settings_t
{
	std::int8_t rook_count;
	std::int32_t min_move_timeout;
	std::int32_t max_move_timeout;
	std::int32_t wait_move_timeout;
	std::int32_t move_count;
};

settings_t make_default_settings();

} // namespace tt_program

#endif // TT_SETTINGS_HPP
