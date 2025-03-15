#ifndef TT_ROOKS_SYNCHRONIZER_HPP
#define TT_ROOKS_SYNCHRONIZER_HPP

#include <atomic>
#include <barrier>
#include <condition_variable>
#include <mutex>

namespace tt_utils
{

class rooks_synchronizer
{
public:
    rooks_synchronizer(
        const std::int8_t max_rooks_count
    )
        : m_start_barrier(max_rooks_count + 1)
    {}

public:

    void wait_for_start()
    {
        m_start_barrier.arrive_and_wait();
    }

private:
    std::barrier<> m_start_barrier;
};

} // namespace tt_utils

#endif // TT_ROOKS_SYNCHRONIZER_HPP

