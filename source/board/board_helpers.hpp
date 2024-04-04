#ifndef TT_BOARD_HELPERS_HPP
#define TT_BOARD_HELPERS_HPP

#include <array>

#include <cstdint>

namespace tt_program
{


using data_t = std::uint8_t;
using const_data_ptr = const data_t *;
using board_data_t = const std::array<data_t, 8>;

} // namespace tt_program

#endif // TT_BOARD_HELPERS_HPP
