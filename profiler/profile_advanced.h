#pragma once

#include <chrono>
#include <string>

struct TotalDuration {
  std::string message;
  std::chrono::steady_clock::duration value;

  explicit TotalDuration(const std::string& msg);
  ~TotalDuration();
};

class AddDuration {
public:
  explicit AddDuration(std::chrono::steady_clock::duration& dest);
  explicit AddDuration(TotalDuration& dest);

  ~AddDuration();

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
