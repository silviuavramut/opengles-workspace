
#include <fps.hpp>

#include <chrono>

namespace opengles_workspace
{

    fps::fps()
    {
        start_time_ = GetCurrentTimeMillis();
    }

    long long fps::GetCurrentTimeMillis()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
            .count();
    }

    long long fps::GetStartTime() const
    {
        return start_time_;
    }

    void fps::SetStartTime(long long new_time){
        start_time_ = new_time;
    }
}
