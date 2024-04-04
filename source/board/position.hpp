#ifndef TT_POSITION_HPP
#define TT_POSITION_HPP

namespace tt_program
{

struct position_t
{
	std::uint8_t x;
	std::uint8_t y;
};



bool operator==(const position_t & left, const position_t & right);


std::ostream & operator<<(std::ostream & out, const tt_program::position_t & position);

} // namespace tt_program

#endif // TT_POSITION_HPP
