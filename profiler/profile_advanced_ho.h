#pragma once

#include <chrono>
#include <string>
#include <iostream>
#include <sstream>

/// Counter for AddDuration
struct TotalDuration {
  std::string message;
  std::chrono::steady_clock::duration value;

  explicit TotalDuration(const std::string& msg)
    : message(msg + ": ")
    , value(0)
    {}
  ~TotalDuration() {
    std::ostringstream os;
    os << message
        << std::chrono::duration_cast<std::chrono::milliseconds>(value).count()
        << " ms" << std::endl;
    std::cerr << os.str();
  }
};

/**
    @brief advanced profiler (compared with LogDuration in profle.h). It uses TotalDuration as counter 
    
    This profiler can measure timing of single operation in cycle
    How to use:
    - create TotalDuration counter("msg") (it will count time for all cycles)
    - use macro **ADD_DURATION**(TotalDuration counter) for scope. Each start will add timing to counter
    - when counter destroys it will output message and time to cerr
*/
class AddDuration {
public:
  explicit AddDuration(std::chrono::steady_clock::duration& dest)
    : add_to(dest)
    , start(std::chrono::steady_clock::now())
    {}
  explicit AddDuration(TotalDuration& dest)
    : AddDuration(dest.value)
    {}

  ~AddDuration() {
    add_to += std::chrono::steady_clock::now() - start;
  }

private:
  std::chrono::steady_clock::duration& add_to;
  std::chrono::steady_clock::time_point start;
};

#define MY_UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define MY_UNIQ_ID(lineno) MY_UNIQ_ID_IMPL(lineno)

#define ADD_DURATION(value) \
  AddDuration MY_UNIQ_ID(__LINE__){value};


/**
    Example ADD_DURATION
*/
/*
int main() {
	TotalDuration read("Total read");
	TotalDuration parse("Total parse");

	for (string line; ReadLine(cin, line, read); ) {
		ADD_DURATION(parse);
		const auto words = SplitIntoWordsView(line);
	}
}
 */
