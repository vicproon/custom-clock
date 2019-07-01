//! @file thread_ctl.hpp
//! @author prun
//! @date 2019.07.01
//! @brief thread execution control based on provided clock

// The header provides a template thread_ctl, which can be used as a replacement
// for some std::this_thread functionality. Specifically, it provides functions 
// spin_for and spin_until, which block thread execution using custom clock,
// provided via template parameter TClock

#pragma once
#ifndef HG__THREAD_CTL_HPP__20190701
#define HG__THREAD_CTL_HPP__20190701

#include <thread>
#include <chrono>

//! @brief utility to control thread execution based on time from custom clock
template<class TClock>
struct thread_ctl
{
  using Duration = typename TClock::duration;
  using TimePoint = typename TClock::time_point;
  
  //! @brief Blocks thread execution (via spin while loop) until duration time
  //!        has passed, based on TClock observations.
  //! @param d [in] required duration
  //! @param spin_sleep [in] If set, the spin loop will actually sleep for this
  //!        amount of time (based on standart library sleep_for implementation)
  //!        instead of yield. Used to exchange `time presicion` for lesser
  //!        cpu load and greated system overall performance.
  static void spin_for(Duration d);
  static void spin_for(Duration d, Duration spin_sleep);

  //! @brief Blocks thread execution (via spin while loop) until a time_point
  //!        is reached, based on TClock observations.
  //! @param tp [in] the TClock::time_point to spin until
  //! @param spin_sleep [in] see spin_for doc.
  static void spin_until(TimePoint tp);
  static void spin_until(TimePoint tp, Duration spin_sleep);


  //! @brief implementation of std::sleep_util ignores observations from clock
  //!        that defines time_point. It only uses it to generate the start
  //!        time point and sleeps for duration(tp-start) using wall clock
  //!        and system sleep/ns_sleep/_Thrd_sleep functions. That is why these
  //!        functions are not useful for this library task.
  static void sleep_for(Duration d);
  static void sleep_until(TimePoint tp);

};

// ============== thread_ctl implementation ================
template<class TClock>  
void thread_ctl<TClock>::sleep_for(Duration d)
{
  auto now = TClock::now();
  std::this_thread::sleep_until(now + d);
}

template<class TClock>
void thread_ctl<TClock>::sleep_until(TimePoint tp)
{
  std::this_thread::sleep_until(tp);
}


template<class TClock>
void thread_ctl<TClock>::spin_for(Duration d)
{
  auto now = TClock::now();
  spin_until(now + d);
}
template<class TClock>
void thread_ctl<TClock>::spin_for(Duration d, Duration spin_sleep)
{
  auto now = TClock::now();
  spin_until(now + d, spin_sleep);
}

template<class TClock>
void thread_ctl<TClock>::spin_until(TimePoint tp)
{
  // if for some reason spinning with yield would be too resource-intensive
  // one should replace current line with the following:
  // spin_until(tp, std::chrono::microseconds(1));
  while (TClock::now() < tp) std::this_thread::yield();
}

template<class TClock>
void thread_ctl<TClock>::spin_until(TimePoint tp, Duration spin_sleep)
{
  if (spin_sleep == Duration::zero())
  {
    spin_until(tp);
    return;
  }
  while (TClock::now() < tp) std::this_thread::sleep_for(spin_sleep);
}

#endif // HG__THREAD_CTL_HPP__20190701