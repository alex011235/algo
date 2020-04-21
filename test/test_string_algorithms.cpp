///
/// \brief Unit tests for sort algorithms.
/// \author alex011235
/// \date 2019-10-13
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
#include "gtest/gtest.h"

#include "string_algorithms.hpp"

using namespace std;
using namespace algo;

/////////////////////////////////////////////
/// Bitap search
/////////////////////////////////////////////

TEST(test_bitap, test_search)
{
  string text{"this is a bitap test"};
  string pattern{"bitap"};
  string res{strings::BitapSearch(text, pattern)};
  EXPECT_EQ(res, "bitap test");
}

TEST(test_bitap, search_not_found)
{
  string text{"this is a bitap test"};
  string pattern{"dijkstra"};
  string res{strings::BitapSearch(text, pattern)};
  EXPECT_EQ(res.size(), 0);
}

TEST(test_bitap, empty_pattern)
{
  string text{"this is a bitap test"};
  string res{strings::BitapSearch(text, "")};
  EXPECT_EQ(res, text);
}

/////////////////////////////////////////////
/// Boyer-More
/////////////////////////////////////////////

TEST(test_boyer_more, nbr_of_occurences_0)
{
  string text{"Banana banana"};
  string pattern{"Manana"};
  vector<int> matches{strings::SearchBoyerMoore(text, pattern)};
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_boyer_more, nbr_of_occurences_1)
{
  string text{"Banana banana"};
  string pattern{"Banana ba"};
  vector<int> matches{strings::SearchBoyerMoore(text, pattern)};
  EXPECT_EQ(matches.size(), 1);
}

TEST(test_boyer_more, nbr_of_occurences_many)
{
  string text{"Lorem cucumber ipsum dolor sit amet, cucumber vel modus "
              "alienum eu. Omnium oporteat definitiones cu mei. Has et solum cucumber vitae, viderer "
              "delicata consectetuer est at. At nisl cucumber facete qui, eu oblique "
              "Lorem cucumber ipsum dolor sit amet, cucumber vel modus "
              "alienum eu. Omnium oporteat definitiones cu mei. Has et solum cucumber vitae, viderer "
              "delicata consectetuer est at. At nisl cucumber facete qui, eu oblique "};

  string pattern{"cucumber"};

  vector<int> matches = strings::SearchBoyerMoore(text, pattern);
  EXPECT_EQ(matches.size(), 8);
}

TEST(test_boyer_more, empty_input_pattern)
{
  string text{"Banana banana"};
  vector<int> matches{strings::SearchBoyerMoore(text, "")};
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_boyer_more, empty_input_text)
{
  string text{""};
  string pattern{"Banana"};
  vector<int> matches{strings::SearchBoyerMoore(text, pattern)};
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_boyer_more, empty_input)
{
  string empty;
  vector<int> matches{strings::SearchBoyerMoore(empty, empty)};
  EXPECT_EQ(matches.size(), 0);
}

/////////////////////////////////////////////
/// Longest common substring
/////////////////////////////////////////////

TEST(test_longest_common_substring, standard)
{
  string A{"otirpporeijgpowkruskaldijkstrawithicecreamergjeågjeopnpoqerhgldijkstrassadar"};
  string B{"iuthewriuthkruskaldijksfuiqgfuqygfnvkjkruskaldijkstrawithicecreamdfbiehf5d"};
  string C{strings::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "kruskaldijkstrawithicecream");
}

TEST(test_longest_common_substring, empty_first)
{
  string A;
  string B{"iuthewriuthkruskaldijksfuiqgfuqygfnvkjkruskaldijkstrawithicecreamdfbiehf5d"};
  string C{strings::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(test_longest_common_substring, empty_second)
{
  string A{"otirpporeijgpowkruskaldijkstrawithicecreamergjeågjeopnpoqerhgldijkstrassadar"};
  string B;
  string C{strings::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(test_longest_common_substring, empty_input)
{
  string A, B;
  string C{strings::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(test_longest_common_substring, one_word)
{
  string A{"calculator"};
  string B{"culat"};
  string C{strings::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "culat");
}

TEST(test_longest_common_substring, one_char)
{
  string x{strings::LongestCommonSubstring("x", "x")};
  EXPECT_EQ(x, "x");

  x = strings::LongestCommonSubstring("x", "y");
  EXPECT_EQ(x, "");
}

/////////////////////////////////////////////
/// Rabin-Karp
/////////////////////////////////////////////

TEST(test_rabin_karp, single_input)
{
  string sentence{"one two one three one two hello one"};
  vector<int> pos{strings::SearchRabinKarpSingle(sentence, "one")};
  EXPECT_EQ(pos.size(), 4);
}

TEST(test_rabin_karp, multi_input)
{
  string sentence{"one two one three one two hello one"};
  set<string> words{"one", "two"};
  vector<int> pos = strings::SearchRabinKarpMulti(sentence, words, 3);
  EXPECT_EQ(pos.size(), 6);
}

TEST(test_rabin_karp, not_found_single)
{
  string sentence{"one two one three one two hello one"};
  vector<int> pos{strings::SearchRabinKarpSingle(sentence, "four")};
  EXPECT_EQ(pos.size(), 0);
}

TEST(test_rabin_karp, not_found_multi)
{
  string sentence{"one two one three one two hello one"};
  set<string> words{"four", "five"};
  vector<int> pos{strings::SearchRabinKarpMulti(sentence, words, 3)};
  EXPECT_EQ(pos.size(), 0);
}

/////////////////////////////////////////////
/// Heap's algorithm
/////////////////////////////////////////////

TEST(test_heaps, test_generate)
{
  string sample{"METAL"};
  vector<string> perms{strings::GenerateAllPermutations(sample)};
  EXPECT_EQ(perms.size(), 120);
  EXPECT_TRUE(find(perms.begin(), perms.end(), "LATEM") != perms.end());
  EXPECT_TRUE(find(perms.begin(), perms.end(), "MEALT") != perms.end());
}

/////////////////////////////////////////////
/// Levenshtein distance
/////////////////////////////////////////////

TEST(test_leven_dist, test_standard)
{
  EXPECT_EQ(strings::LevDistance("abracadabra", "cadabraabra"), 6);
  EXPECT_EQ(strings::LevDistance("book", "back"), 2);
  EXPECT_EQ(strings::LevDistance("book", "book"), 0);
  EXPECT_EQ(strings::LevDistance("book", "read"), 4);
  EXPECT_EQ(strings::LevDistance("book", ""), 4);
}