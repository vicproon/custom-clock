#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <custom_clock.hpp>
#include <thread_ctl.hpp>


using namespace std;
using namespace std::chrono;

template <class Ttime_point>
void report_time_elapsed(string prefix, Ttime_point start, Ttime_point finish)
{
  cout << prefix << duration_cast<milliseconds>(finish - start).count() << " ms" << endl;
}

int main()
{
  // clock frondends
  using CustomClock = RatioClock<ratio<4,3>>;
  using AnotherCustomClock = RatioClock<ratio<1,3>>;
  auto start = steady_clock::now();
  auto custom_start = CustomClock::now();
  auto another_start = AnotherCustomClock::now();
  thread_ctl<CustomClock>::spin_until(custom_start + seconds(3));
  auto intermediate = steady_clock::now();
  auto custom_intermediate = CustomClock::now();
  auto another_intermediate = AnotherCustomClock::now();
  thread_ctl<AnotherCustomClock>::spin_until(another_start + seconds(3));
  auto finish = steady_clock::now();
  auto custom_finish = CustomClock::now();
  auto another_finish = AnotherCustomClock::now();

  report_time_elapsed("intermediate steady: ", start, intermediate);
  report_time_elapsed("intermediate custom: ", custom_start, custom_intermediate);
  report_time_elapsed("intermediate another: ", another_start, another_intermediate);


  report_time_elapsed("Steady clock elapsed: ", start, finish);
  report_time_elapsed("Custom clock elapsed: ", custom_start, custom_finish);
  report_time_elapsed("Another clock elapsed: ", another_start, another_finish);
}
