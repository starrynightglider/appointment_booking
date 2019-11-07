#pragma once
#include <iostream>
#include <utility>
#include <vector>

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& strm, std::pair<T1, T2> const& p) {
  strm << "[ " << p.first << " , " << p.second << " ]";
  return strm;
}

template <typename T>
std::ostream& operator<<(std::ostream& strm, std::vector<T> const& vec) {
  for (auto const& v : vec) {
    strm << v << std::endl;
  }
  return strm;
}
