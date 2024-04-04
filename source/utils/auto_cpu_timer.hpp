#ifndef TT_AUTO_CPU_TIMER_HPP
#define TT_AUTO_CPU_TIMER_HPP

#include <iostream>
#include <chrono>

namespace tt_utils
{

class auto_cpu_timer
{
public:
    explicit auto_cpu_timer(std::string name)
    : m_name(name)
    , m_start(std::chrono::steady_clock::now())
    {}

    ~auto_cpu_timer()
    {
        m_finish = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(m_finish - m_start).count();
        std::cout << m_name << " - elapsed time = " << elapsed << " ms" << std::endl;
    }

    auto_cpu_timer(const auto_cpu_timer&) = delete;

private:
	std::string m_name;
    std::chrono::steady_clock::time_point m_start;
    std::chrono::steady_clock::time_point m_finish;
};

} // namespace tt_utils

#endif // TT_AUTO_CPU_TIMER_HPP
