// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "profile_advanced.h"

#include <iostream>
#include <sstream>

using namespace std;
using namespace chrono;

TotalDuration::TotalDuration(const string& msg)
  : message(msg + ": ")
  , value(0)
{
}

TotalDuration::~TotalDuration() {
  ostringstream os;
  os << message
     << duration_cast<milliseconds>(value).count()
     << " ms" << endl;
  cerr << os.str();
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
