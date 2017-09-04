#include <elle/time.hh>

#include <elle/printf.hh>

namespace elle
{
  /*--------.
  | boost.  |
  `--------*/

  boost::posix_time::ptime
  iso8601_to_posix_time(std::string const& str)
  {
    boost::posix_time::ptime res;
    // Use the ISO extended input facet to interpret the string.
    std::stringstream ss(str);
    auto input_facet =
      std::make_unique<boost::posix_time::time_input_facet>();
    // ISO 8601
    input_facet->format("%Y-%m-%dT%H:%M:%S%F");
    ss.imbue(std::locale(ss.getloc(), input_facet.release()));
    if (!(ss >> res))
      err("invalid ISO8601 date: %s", str);
    // Check there isn't any leftover.
    std::string leftover;
    std::getline(ss, leftover);
    if (leftover.empty())
      return res;
    // Boost can't parse timezones, handle it manually.
    if (leftover == "Z")
      ; // Accept UTC suffix.
    else if ((leftover[0] == '+' || leftover[0] == '-') && leftover.size() == 5)
    {
      // Handle timezone.
      std::stringstream tz(leftover);
      int direction = tz.get() == '+' ? -1 : 1;
      int amount;
      tz >> amount;
      if (tz.get() != -1)
        err("garbage at end of date: %s", leftover);
      res += boost::posix_time::hours(direction * amount / 100);
    }
    else
      err("garbage at end of date: %s", leftover);
    if (!ss.eof())
    {
      std::string leftover;
      std::getline(ss, leftover);
      err("garbage at end of date: %s", leftover);
    }
    return res;
  }

  std::string
  to_iso8601(boost::posix_time::ptime const& time)
  {
    std::stringstream ss;
    auto output_facet = std::make_unique<boost::posix_time::time_facet>();
    // ISO 8601
    output_facet->format("%Y-%m-%dT%H:%M:%S%F%q");
    ss.imbue(std::locale(ss.getloc(), output_facet.release()));
    ss << time;
    return ss.str();
  }


  /*--------------.
  | std::chrono.  |
  `--------------*/

  std::string
  to_iso8601(std::chrono::system_clock::time_point const& t)
  {
    // Note that date::format works only with system_clock, not with
    // steady_clock.  The latter needs tz support to be printed, which
    // requires the use of H. Hinnant's tz lib, which we avoided so
    // far.  See log/TextLogger for an alternative if needed.
    return date::format("%FT%T", date::floor<std::chrono::microseconds>(t));
  }

  std::string
  to_iso8601_local(std::chrono::system_clock::time_point const& tp)
  {
    using namespace date;
    using namespace std::chrono;
    // This gives universal time
    //
    // format("%FT%T", floor<seconds>(system_clock::now()));
    //
    // We need to use the tz library, or work by hand.
    auto const t = system_clock::to_time_t(tp);
    auto const tm = std::localtime(&t);
    auto&& os = std::ostringstream{};
    // GCC 4.9 does not support put_time.
    // os << std::put_time(tm, "%F %T");
    {
      // strlen("2017-07-31T05:24:53") = 20;
      auto buf = std::array<char, 24>{};
      // Mingw does not support "%F %T".
      std::strftime(buf.data(), buf.size(), "%Y-%m-%dT%H:%M:%S", tm);
      os << buf.data();
    }
    return os.str();
  }
}
