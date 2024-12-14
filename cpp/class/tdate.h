#ifndef __TDATE_H__
#define __TDATE_H__

#include <cstdio>
#include <iostream>
#include <string>

class Tdate {
private:
  int year = 1970;
  int month = 1;
  int day = 1;

public:
  void set(int y, int m, int d);
  bool is_leap_year();
  operator std::basic_string<char>();
  void print();
};

#endif