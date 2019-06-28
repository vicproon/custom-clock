# custom-clock
Custom clock integrated with std::chrono routines.

Can be used for std::this_thread::sleep_for std::this_thread::sleep_until.
The sample usage case is integrating with simulation environment and making process sleep times rely on simulation clock rather than system clock.
