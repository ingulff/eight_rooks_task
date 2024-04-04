/**
 *  ᛝ
 */

#include <vector>

#include "board.hpp"
#include "error/error.hpp"
#include "settings.hpp"
#include "rook.hpp"
#include "utils/auto_cpu_timer.hpp"


int main(int argc, char **argv)
{
	tt_utils::auto_cpu_timer timer("main()"); 

	int res = error::to_int(error::errc::ok);

	auto settings = tt_program::make_default_settings();
	
	tt_program::board_t board(settings.rook_count);
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

	for(auto & thread : thread_pool)
	{
		thread.join();
	}

	board.add_rook();
	board.start_game();

	rook_pool[0].start_moves();


	std::cout << "hello world" << std::endl;

	return res;
}