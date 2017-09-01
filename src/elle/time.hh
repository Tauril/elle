#pragma once

#include <chrono>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <elle/date/date.h>
#include <elle/windows.hh>

namespace elle
{
  // https://stackoverflow.com/a/4918873/1353549
  template <typename Clock, typename Duration>
  inline static
  boost::posix_time::ptime
  to_boost(const std::chrono::time_point<Clock, Duration>& from)
  {
    using duration_t = std::chrono::nanoseconds;
    using rep_t = duration_t::rep;
    rep_t d = std::chrono::duration_cast<duration_t>(from.time_since_epoch()).count();
    rep_t sec = d / 1000000000;
    rep_t nsec = d % 1000000000;
    return boost::posix_time::from_time_t(0)
      + boost::posix_time::seconds(static_cast<long>(sec))
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
      + boost::posix_time::nanoseconds(nsec);
#else
      + boost::posix_time::microseconds((nsec+500)/1000);
#endif
  }

  template <typename Clock, typename Duration>
  inline static
  std::chrono::time_point<Clock, Duration>
  from_boost(const boost::posix_time::ptime& from)
  {
    boost::posix_time::time_duration const time_since_epoch
      = from - boost::posix_time::from_time_t(0);
    std::chrono::time_point<Clock, Duration> t
      = std::chrono::system_clock::from_time_t(time_since_epoch.total_seconds());
    auto nsec
      = time_since_epoch.fractional_seconds()
      * (1000000000 / time_since_epoch.ticks_per_second());
    return t + std::chrono::duration_cast<Duration>(std::chrono::nanoseconds(nsec));
  };

  /// Parse a date in ISO 8601 format such as "2017-08-31T13:02:41".
  boost::posix_time::ptime
  iso8601_to_posix_time(std::string const& str);

  /// Convert to ISO 8601, i.e., "2017-08-31T13:02:41", not
  /// "20170831T130241" as boost::to_iso_string does.
  std::string
  to_iso8601(boost::posix_time::ptime const& t);

  /// Convert to ISO 8601, i.e., "2017-08-31T13:02:41.123456".
  template <typename Clock, typename Duration = typename Clock::duration>
  std::string
  to_iso8601(std::chrono::time_point<Clock, Duration> const& t)
  {
    // Note that date::format works only with system_clock, not with
    // steady_clock.  The latter needs tz support to be printed, which
    // requires the use of H. Hinnant's tz lib, which we avoided so
    // far.  See log/TextLogger for an alternative if needed.
    return date::format("%FT%T", t);
  }
}
