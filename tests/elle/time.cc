#define ELLE_TEST_MODULE time
#include <elle/test.hh>

#include <regex>

#include <elle/time.hh>

BOOST_AUTO_TEST_CASE(to_iso8601)
{
  auto const now = std::chrono::system_clock::now();
  auto const now_str = elle::to_iso8601(now);
  BOOST_TEST_MESSAGE("now_str: " << now_str);
  auto const re =
    std::regex{"(.*?-.*?-.*?)"                       // 1: date.
               "T"
               "([0-9][0-9]:[0-9][0-9]:[0-9][0-9])"  // 2: time in secs.
               "(?:\\.([0-9]{6}))"};                 // 3: microseconds.
  
  auto m = std::smatch{};
  BOOST_CHECK(std::regex_match(now_str, m, re));
}
