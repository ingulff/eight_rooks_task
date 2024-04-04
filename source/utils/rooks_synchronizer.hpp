#ifndef TT_ROOKS_SYNCHRONIZER_HPP
#define TT_ROOKS_SYNCHRONIZER_HPP

#include <atomic>
#include <condition_variable>
#include <mutex>

namespace tt_utils
{

class rooks_synchronizer
{
public:
    rooks_synchronizer(std::mutex & mutex, const std::int8_t max_rooks_count)
        : m_rooks_starter()
        , m_mutex(mutex)
        , m_max_rooks(max_rooks_count)
        , m_active_rooks(0)
    {}

public:
    void add_rook_to_active()
    {
        ++m_active_rooks;
    }

    void wait( )
    {
        std::unique_lock lock( m_mutex );
//std::cout << "sync::wait() - " << (int)m_active_rooks << std::endl;
        m_rooks_starter.wait( lock, [this](){ return !( this->need_wait() ); } );
    }

    bool need_wait()
    {
        return m_active_rooks.load( std::memory_order_acquire ) != m_max_rooks;
    }

    void notify_all()
    {
//std::cout << "notify all (" << std::endl;
        while ( need_wait() )
        {
            ;
        }
//std::cout << "notify all )" << std::endl;
        m_rooks_starter.notify_all( );
    }

private:

    std::condition_variable m_rooks_starter;
    std::mutex & m_mutex;
    const std::int8_t m_max_rooks;
    std::atomic_int8_t m_active_rooks = 0;
};

} // namespace tt_utils

#endif // TT_ROOKS_SYNCHRONIZER_HPP

