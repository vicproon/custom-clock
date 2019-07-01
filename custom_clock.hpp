#pragma once
#ifndef HG__CUSTOM_CLOCK_H__20190628
#define HG__CUSTOM_CLOCK_H__20190628

#include <chrono>

template<class T>
struct is_ratio : std::false_type{};

template<std::intmax_t Num, std::intmax_t Denom>
struct is_ratio<std::ratio<Num, Denom>> : std::true_type {};

// custom clock that are intent to run std::ratio-times faster than steady clock
template<class TRatio>
class RatioClock
{
  static_assert(is_ratio<TRatio>::value, "TRatio parameter for Ratio Clock should be specialization of std::ratio");
public:
  typedef std::chrono::nanoseconds 		duration;
  typedef duration::rep	  				    rep;
  typedef duration::period	  				period;
  typedef std::chrono::time_point<RatioClock<TRatio>, duration> 	time_point;
  //using time_point = std::chrono::time_point<CustomClock>;
  static time_point now();
  
};

template<class TRatio>
typename RatioClock<TRatio>::time_point RatioClock<TRatio>::now()
{
  auto clock_now = std::chrono::steady_clock::now();
  return time_point(duration(clock_now.time_since_epoch().count() * TRatio::num / TRatio::den));
}



#endif // HG__CUSTOM_CLOCK_H__20190628
