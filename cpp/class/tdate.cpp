#include "tdate.h"

void Tdate::set(int y, int m, int d) {
  this->day = d;
  this->month = m;
  this->year = y;
}

bool Tdate::is_leap_year() {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

Tdate::operator std::basic_string<char>() {
  char result[] = "1970/01/01";
  std::sprintf(result, "%d/%2d/%2d", year, month, day);
  return std::string(result);
}

void Tdate::print() { std::cout << (std::string) * (this) << std::endl; }