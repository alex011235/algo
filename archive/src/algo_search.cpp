///
/// \brief Source file for search algorithms.
/// \author alex011235
/// \date 2020-04-20
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_search.hpp"

#include <algorithm>
#include <cmath>
#include <string>

namespace algo::search {

/////////////////////////////////////////////
/// Binary search
/////////////////////////////////////////////

template<typename T>
int Binary(const std::vector<T> &vec, const T &value)
{
  if (!std::is_sorted(vec.begin(), vec.end())) {
    return -1;
  }

  size_t l{0};
  size_t r{vec.size()};

  while (l < r) {

    int m = std::floor((l + r) / 2);
    if (vec[m] < value) {
      l = m + 1;
    } else {
      r = m;
    }
  }

  if (l == vec.size()) {
    return -1;
  }
  return l;
}

template int Binary<int>(const std::vector<int> &vec, const int &value);
template int Binary<std::string>(const std::vector<std::string> &vec, const std::string &value);

/////////////////////////////////////////////
/// Selection search
/////////////////////////////////////////////

template<typename T>
void SelectionMinPriv(std::vector<T> &vec, const T &k)
{
  for (T i = 0; i <= k; ++i) {
    size_t min_index{static_cast<size_t>(i)};
    T minVal{vec[i]};

    for (size_t j = i + 1; j < vec.size(); ++j) {
      if (vec[j] < minVal) {
        min_index = j;
        minVal = vec[j];
      }
    }

    T t{vec[min_index]};
    vec[min_index] = vec[i];
    vec[i] = t;
  }
}

template<typename T>
std::vector<T> SelectionMin(std::vector<T> vec, const T &k)
{
  if (vec.empty()) {
    return vec;
  }

  if (static_cast<size_t>(k) > vec.size()) {
    return vec;
  }

  std::vector<T> temp{};
  SelectionMinPriv(vec, k);
  temp.resize(k);
  std::copy_n(vec.begin(), k, temp.begin());
  return temp;
}

template std::vector<int> SelectionMin<int>(std::vector<int> vec, const int &value);

template<typename T>
void SelectionMaxPriv(std::vector<T> &vec, const T &k)
{
  for (int i = 0; i <= k; ++i) {
    size_t max_index{static_cast<size_t>(i)};
    T minVal{vec[i]};

    for (size_t j = i + 1; j < vec.size(); ++j) {
      if (vec[j] > minVal) {
        max_index = j;
        minVal = vec[j];
      }
    }

    T t{vec[max_index]};
    vec[max_index] = vec[i];
    vec[i] = t;
  }
}

template<typename T>
std::vector<T> SelectionMax(std::vector<T> vec, const T &k)
{

  if (vec.empty()) {
    return vec;
  }

  if (static_cast<size_t>(k) > vec.size()) {
    return vec;
  }

  std::vector<T> temp{};
  SelectionMaxPriv(vec, k);
  temp.resize(k);
  std::copy_n(vec.begin(), k, temp.begin());
  return temp;
}

template std::vector<int> SelectionMax<int>(std::vector<int> vec, const int &value);

}// namespace algo::search
