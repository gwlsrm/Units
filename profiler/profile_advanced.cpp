#include "profile_advanced.h"

#include <iostream>
#include <sstream>

using namespace std;
using namespace chrono;

TotalDuration::TotalDuration(const std::string& msg)
  : message(msg + ": ")
  , value(0)
{
}

TotalDuration::~TotalDuration() {
  std::ostringstream os;
  os << message
     << duration_cast<milliseconds>(value).count()
     << " ms" << endl;
  std::cerr << os.str();
}

AddDuration::AddDuration(steady_clock::duration& dest)
  : add_to(dest)
  , start(steady_clock::now())
{
}

AddDuration::AddDuration(TotalDuration& dest)
  : AddDuration(dest.value)
{
}

AddDuration::~AddDuration() {
  add_to += steady_clock::now() - start;
}
