/**
 *  ᛝ
 */

#include <cstdint>

#include "settings.hpp"

namespace tt_program
{

#ifdef ROOK_COUNT
	static constexpr std::int8_t rook_count = ROOK_COUNT;
#else
	static constexpr std::int8_t rook_count = 6;
#endif // ROOK_COUNT
#undef ROOK_COUNT

#ifdef MIN_MOVE_TIMEOUT
	static constexpr std::int32_t min_move_timeout = MIN_MOVE_TIMEOUT;
#else
	static constexpr std::int32_t min_move_timeout = 200;
#endif // MIN_MOVE_TIMEOUT
#undef MIN_MOVE_TIMEOUT

#ifdef MAX_MOVE_TIMEOUT
	static constexpr std::int32_t max_move_timeout = MAX_MOVE_TIMEOUT;
#else
	static constexpr std::int32_t max_move_timeout = 300;
#endif // MAX_MOVE_TIMEOUT
#undef MAX_MOVE_TIMEOUT

#ifdef WAIT_MOVE_TIMEOUT
	static constexpr std::int32_t wait_move_timeout = WAIT_MOVE_TIMEOUT;
#else
	constexprstd::int32_t wait_move_timeout = 5000;
#endif
#undef WAIT_MOVE_TIMEOUT

#ifdef MOVE_COUNT
	static constexpr std::int32_t move_count = MOVE_COUNT;
#else
	static constexpr std::int32_t move_count = 50;
#endif
#undef MOVE_COUNT


settings_t make_default_settings()
{

	//settings_t settings{rook_count, min_move_timeout, max_move_timeout, wait_move_timeout, move_count};
	//return settings;
	return {rook_count, min_move_timeout, max_move_timeout, wait_move_timeout, move_count};
}

} // namespace tt_program
