/**
 *  ᛝ
 */

#include <vector>

#include "board/board.hpp"
#include "error/error.hpp"
#include "figures/rook.hpp"
#include "logger/logger.hpp"
#include "settings/settings.hpp"


int main(int argc, char **argv)
{
	tt_program::event_logger logger;

	logger.start();

	int res = error::to_int(error::errc::ok);

	auto settings = tt_program::make_default_settings();
	
	tt_program::board_t board(settings.rook_count, logger);
	std::vector<tt_program::rook_t> rook_pool;
	std::vector<std::jthread > thread_pool;
	
	for(std::int8_t i = 0; i < settings.rook_count; ++i)
	{

		rook_pool.emplace_back( tt_program::rook_t(board, 
			settings.min_move_timeout, 
			settings.max_move_timeout, 
			settings.wait_move_timeout,
			settings.move_count) ) ;
	}

	for(std::int8_t i = 0; i < settings.rook_count; ++i)
	{
		auto rook_moves = [ &rook_pool, index = i ](){
			rook_pool[index].wait_start_game();
		};

		thread_pool.emplace_back( std::jthread (rook_moves) );
	}

	board.start_game();

	logger.stop();

	return res;
}