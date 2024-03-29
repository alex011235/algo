///
/// \brief Source file for string algorithms.
/// \author alex011235
/// \date 2020-04-19
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
#include "algo_string.hpp"

#include <algorithm>
#include <cmath>
#include <vector>

namespace algo::string {

int LastOccurrence(std::string str, char c)
{
  int index = str.length();
  while (index != 0) {
    if (str[index] == c) {
      return index;
    }
    index--;
  }
  return 0;
}

std::vector<int> SearchBoyerMoore(std::string &text, const std::string &pattern)
{
  int m = pattern.length(), n = text.length(), i = m - 1, j = i;
  int chunk = 0, w_length = m;
  std::vector<int> matches;

  do {
    if (pattern[j] == text[i]) {
      if (j == 0) {
        matches.push_back(i + chunk);
        text = text.substr(i + w_length);
        chunk = chunk + i + w_length;
        n = text.length(), i = m - 1, j = i;
      } else {
        i--;
        j--;
      }
    } else {
      i = i + m - std::min(j, 1 + LastOccurrence(text, text[i]));
      j = m - 1;
    }
  } while (i < n - 1);
  return matches;
}

std::string LongestCommonSubstring(std::string A, std::string B)
{

  if (A.empty() || B.empty()) {
    return "";
  }

  // Append blank spaces to search in whole strings, note for-loops start on 1.
  A = " " + A + " ";
  B = " " + B + " ";

  std::vector<std::vector<int>> L(A.length(), std::vector<int>(B.length(), 0));
  int max_substr = 0, x_longest = 0;

  for (size_t i = 1; i < A.length(); ++i) {
    for (size_t j = 1; j < B.length(); ++j) {

      if (A[i - 1] == B[j - 1]) {
        L[i][j] = L[i - 1][j - 1] + 1;

        if (L[i][j] > max_substr) {
          max_substr = L[i][j];
          x_longest = i;
        }
      } else {
        L[i][j] = 0;
      }
    }
  }
  std::string res = A.substr(x_longest - max_substr, max_substr);

  if (res[0] == ' ') {
    return std::string(res.begin() + 1, res.end());
  }
  return res;
}

namespace {
/// \brief Returns the hash for str.
/// \param str The string to hash.
/// \return hash.
constexpr auto Fingerprint = [](auto str) {
  std::hash<std::string> shash;
  return shash(str);
};
}//namespace

std::vector<int> SearchRabinKarpSingle(const std::string &text, const std::string &pattern)
{
  std::vector<int> pos;
  size_t n = text.length();
  size_t m = pattern.length();
  unsigned long hash_p = Fingerprint(pattern);
  unsigned long hash_t = Fingerprint(text.substr(0, m));

  for (size_t i = 0; i < (n - m + 1); i++) {
    if (hash_t == hash_p) {
      if (text.substr(i, m) == pattern) pos.push_back(i);
    }
    std::string temp = text.substr(i + 1, m);
    hash_t = Fingerprint(temp);
  }
  return pos;
}

std::vector<int> SearchRabinKarpMulti(const std::string &text, std::set<std::string> patterns, int m)
{
  std::set<unsigned long> hash_pm;
  std::vector<int> pos;
  size_t n = text.length();

  for (const auto &pattern : patterns) {
    hash_pm.insert(Fingerprint(pattern));
  }

  unsigned long hash_t = Fingerprint(text.substr(0, m));

  for (size_t j = 0; j < (n - m + 1); j++) {
    bool h_find = hash_pm.find(hash_t) != hash_pm.end();
    bool p_find = patterns.find(text.substr(j, m)) != patterns.end();
    if (h_find && p_find) pos.push_back(j);

    std::string temp = text.substr(j + 1, m);
    hash_t = Fingerprint(temp);
  }
  return pos;
}

/// \brief Hidden function for generating all the permutations of the input str.
/// \param n Size of str;
/// \param str The input string.
/// \param vec The permutations.
void Heaps(size_t n, std::string &str, std::vector<std::string> &vec)
{
  if (n == 1) {
    vec.emplace_back(str);
  } else
    for (size_t i = 0; i < n; i++) {
      Heaps(n - 1, str, vec);
      if (n % 2 == 0) {
        std::swap(str[i], str[n - 1]);
      } else {
        std::swap(str[0], str[n - 1]);
      }
    }
}

std::vector<std::string> GenerateAllPermutations(std::string &str)
{
  size_t n{str.size()};
  std::vector<std::string> vec;
  Heaps(n, str, vec);
  return vec;
}

bool IsRotated(const std::string &str1, const std::string &str2)
{
  if (str1.empty() && str2.empty()) {
    return true;
  }
  size_t len{str1.size()};
  std::string str11(2 * len - 1, ' ');
  std::copy(str1.begin(), str1.end(), str11.begin());
  std::copy(str1.begin(), str1.end(), str11.begin() + len);
  return str11.find(str2) != std::string::npos;
}

std::string Compress(const std::string &str)
{
  const size_t n{str.size()};
  std::string res;

  int old_char{str[0]};
  int count{0};

  for (size_t i = 0; i <= n; i++) {
    auto uc = static_cast<unsigned char>(str[i]);
    int c = uc;
    // Count the number of times the current char occurs.
    if (c == old_char) {
      count++;
    } else {
      if (old_char != ' ') {
        res.push_back(old_char);

        if (count > 1) {
          res += std::to_string(count);
        }
        count = 1;
      }
      old_char = c;
    }
  }

  // If the input char is smaller, the compression failed.
  if (str.size() <= res.size()) {
    return str;
  }

  return res;
}

bool HasUniqueChars(const std::string &str)
{
  std::vector<int> visited(255, 0);

  for (const auto &x : str) {
    int xi{x - '0'};
    visited[xi]++;
    if (visited[xi] > 1) {
      return false;
    }
  }
  return true;
}

/////////////////////////////////////////////
/// String metric
/////////////////////////////////////////////

namespace metric {

int Levenshtein(const std::string &word_a, const std::string &word_b)
{
  size_t a_size{word_a.length()};
  size_t b_size{word_b.length()};

  std::vector<std::vector<int>> d(a_size + 1, std::vector<int>(b_size + 1, 0));
  d[0][0] = 0;

  for (size_t i = 1; i < a_size + 1; i++) d[i][0] = i;
  for (size_t j = 1; j < b_size + 1; j++) d[0][j] = j;

  for (size_t j = 1; j < b_size + 1; j++) {
    for (size_t i = 1; i < a_size + 1; i++) {
      int cost{1};
      if (word_a[i - 1] == word_b[j - 1]) {
        cost = 0;
      }

      d[i][j] = std::min(d[i - 1][j] + 1, std::min(d[i][j - 1] + 1, d[i - 1][j - 1] + cost));
    }
  }
  return d[a_size][b_size];
}

int Hamming(const std::string &word_a, const std::string &word_b)
{
  if (word_a.size() != word_b.size()) {
    return -1;
  }
  size_t counter{0};
  size_t size{word_a.size()};

  for (size_t i = 0; i < size; i++) {
    if (word_a.at(i) != word_b.at(i)) {
      counter++;
    }
  }
  return counter;
}

double Dice(const std::string &word_a, const std::string &word_b)
{
  std::vector<std::string> bigrams_a, bigrams_b;

  for (size_t i = 0; i < word_a.size() - 1; i++) {
    std::string str{word_a[i], word_a[i + 1]};
    bigrams_a.emplace_back(str);
  }
  for (size_t i = 0; i < word_b.size() - 1; i++) {
    std::string str{word_b[i], word_b[i + 1]};
    bigrams_b.emplace_back(str);
  }
  // Find the intersect of bigrams
  int intersect{0};
  for (const auto &bigram : bigrams_a) {
    if (find(bigrams_b.begin(), bigrams_b.end(), bigram) != bigrams_b.end()) {
      intersect++;
    }
  }
  // Compute score
  return 2.0 * intersect / static_cast<double>(bigrams_a.size() + bigrams_b.size());
}

namespace {

constexpr auto Jaro = [](const std::string &word_a, const std::string &word_b) {
  double max_dist = std::floor(std::max(word_a.size(), word_b.size()) / 2.0) - 1.0;
  std::string wa{word_a}, wb{word_b};

  if (word_b.size() < word_a.size()) {
    wa = word_b;
    wb = word_a;
  }
  std::vector<std::pair<int, int>> match;
  for (int i = 0; i < static_cast<int>(wa.size()); i++) {
    for (int j = 0; j < static_cast<int>(wb.size()); j++) {
      if (wa[i] == wb[j] && std::abs(i - j) <= max_dist) {
        match.emplace_back(std::make_pair(i, j));
        break;
      }
    }
  }
  auto m = static_cast<double>(match.size());
  double t{0.0};
  for (const auto &mt : match) {
    if (mt.first > mt.second) {
      t += 1.0;
    }
  }
  if (m == 0) {
    return 0.0;
  }
  return 1.0 / 3.0 * (m / wa.size() + m / wb.size() + (m - t) / m);
};

}// namespace

double JaroWinkler(const std::string &word_a, const std::string &word_b)
{
  if (word_a == word_b) {
    return 1.0;// Max score.
  }
  int l{0};            // Length of the common prefix up to four chars.
  const double kP{0.1};// Scaling factor.

  int sz = static_cast<int>(std::min(word_a.size(), word_b.size()));// Max size
  for (int i = 0; i < std::min(4, sz); i++) {
    if (word_a[i] == word_b[i]) {
      l++;
    } else {
      break;
    }
  }
  double jaro{Jaro(word_a, word_b)};
  return jaro + l * kP * (1.0 - jaro);
}

}// namespace metric
}// namespace algo::string
