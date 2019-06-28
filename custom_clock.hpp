#pragma once
#ifndef HG__CUSTOM_CLOCK_H__20190628
#define HG__CUSTOM_CLOCK_H__20190628

#include <chrono>


class CustomClock
{
public:
  typedef std::chrono::nanoseconds 		duration;
  typedef duration::rep	  				    rep;
  typedef duration::period	  				period;
  typedef std::chrono::time_point<CustomClock, duration> 	time_point;
  //using time_point = std::chrono::time_point<CustomClock>;
  static time_point now();
  
};

CustomClock::time_point CustomClock::now()
{
  auto clock_now = std::chrono::steady_clock::now();
  return time_point(duration(clock_now.time_since_epoch().count() * 4 / 3));
}

#endif // HG__CUSTOM_CLOCK_H__20190628
