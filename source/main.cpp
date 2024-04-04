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
	std::vector<std::thread> thread_pool;
	std::vector<tt_program::rook_t> rook_pool;
	
	for(std::int8_t i = 0; i < settings.rook_count; ++i)
	{

		rook_pool.emplace_back( tt_program::rook_t(board, 
			settings.min_move_timeout, 
			settings.max_move_timeout, 
			settings.wait_move_timeout,
			settings.move_count) ) ;
	}

	for(std::int8_t i = 1; i < settings.rook_count; ++i)
	{
		auto rook_moves = [ &rook_pool, index = i ](){
			rook_pool[index].wait_start_game();
		};

		thread_pool.emplace_back( std::thread(rook_moves) );
	}
//std::cout << "pre joint" << std::endl;
	board.add_rook();
//std::cout << "add_rook 0 " << std::endl;
	board.start_game();

	rook_pool[0].start_moves();

	for(auto & thread : thread_pool)
	{
		thread.join();
	}
//std::cout << "after join" << std::endl;

	logger.stop();

	return res;
}