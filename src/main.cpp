#include <chrono>
#include <thread>
#include <iostream>

#include <custom_clock.hpp>

template<class TClock>
struct my_thread
{
  using Duration = typename TClock::duration;
  using TimePoint = typename TClock::time_point;
  static void sleep_for(Duration d)
  {
    auto now = TClock::now();
    std::this_thread::sleep_until(now + d);
  }

  static void spin_for(Duration d)
  {
    auto now = TClock::now();
    spin_until(now + d);
  }

  static void sleep_until(TimePoint tp)
  {
    std::this_thread::sleep_until(tp);
  }

  static void spin_until(TimePoint tp, Duration d={})
  {
    while (TClock::now() < tp)
    {
      if (d == Duration::zero()) std::this_thread::sleep_for(d);
      else std::this_thread::yield();
    }  
  }
};

// template<class TClock, class Duration>
// void my_thread::sleep_for(Duration d)
// {
// auto now = TClock::now();
// std::this_thread::sleep_until(now + d);
// }


using namespace std;
using namespace std::chrono;

int main()
{
  auto start = steady_clock::now();
  auto custom_start = CustomClock::now();
  my_thread<CustomClock>::spin_until(custom_start + seconds(3));
  auto intermediate = steady_clock::now();
  auto custom_intermediate = CustomClock::now();
  my_thread<CustomClock>::spin_until(custom_start + seconds(3));
  auto finish = steady_clock::now();
  auto custom_finish = CustomClock::now();

  cout << "Steady clock elapsed: " << duration_cast<milliseconds>(finish - start).count() << endl;
  cout << "Custom clock elapsed: " << duration_cast<milliseconds>(custom_finish - custom_start).count() << endl;


  cout << "intermediate steady: " << duration_cast<milliseconds>(intermediate - start).count() <<
          "ms" << endl;
  cout << "intermediate custom: " << duration_cast<milliseconds>(custom_intermediate - custom_start).count() <<
          "ms" << endl;

}
