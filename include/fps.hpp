#pragma once

namespace opengles_workspace
{

    class fps
    {
    public:
        // Constructor
        fps();

        // Destructor
        ~fps() = default;

        long long GetCurrentTimeMillis();
        long long GetStartTime() const;
        void SetStartTime(long long new_time);

    private:
        long long start_time_;
    };
}