//
// Created by Alexander Karlsson on 2019-10-13.
//

#include "string_algorithms.h"

#include <vector>

using namespace std;

string StringAlgorithm::bitap_search(string text, string pattern) {
  size_t m = pattern.length();

  if (m == 0) return text;

  vector<int> R(m, 0);
  R[0] = 1;

  for (size_t i = 0; i < text.length(); i++) {
    // Uppdate the bit array
    for (size_t k = m; k >= 1; k -= 1) {
      R[k] = R[k - 1] & (text[i] == pattern[k - 1]);
    }

    if (R[m] > 0) return text.substr(i - m + 1);
  }

  return "";
}