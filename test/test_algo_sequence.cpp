///
/// \brief Unit tests for sequence algorithms.
/// \author alex011235
/// \date 2020-04-20
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <algorithm>
#include <cmath>
#include <numeric>

#include "algo.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace algo::sequence;

/////////////////////////////////////////////
/// Longest increasing sub sequence tests
/////////////////////////////////////////////

TEST(test_algo_sequence, longest_incr_subseq_empty)
{
  vector<int> vec{};
  EXPECT_TRUE(LongestIncreasingSub(vec).empty());
}

TEST(test_algo_sequence, longest_incr_subseq_single_input)
{
  vector<int> in{1};
  vector<int> ans{1};
  vector<int> out{LongestIncreasingSub(in)};
  EXPECT_TRUE(equal(out.begin(), out.end(), ans.begin()));
}

TEST(test_algo_sequence, longest_incr_subseq_standard)
{
  vector<int> in{1, 2, 3, 4, 5, 6, 5, 1, 2, 3, 4, 5, 6, 7, 8, 1};
  vector<int> ans{1, 2, 3, 4, 5, 6, 7, 8};
  vector<int> out{LongestIncreasingSub(in)};
  EXPECT_TRUE(equal(out.begin(), out.end(), ans.begin()));
}

TEST(test_algo_sequence, longest_incr_subseq_with_negative)
{
  vector<int> in{1, 2, 3, -3, -2, -1, 0, 1, 2, 0};
  vector<int> ans{-3, -2, -1, 0, 1, 2};
  vector<int> out{LongestIncreasingSub(in)};
  EXPECT_TRUE(equal(out.begin(), out.end(), ans.begin()));
}

TEST(test_algo_sequence, longest_incr_subseq_float)
{
  vector<float> in{9.0, 10.0, M_SQRT2, M_E, M_PI, 2.0};
  vector<float> ans{M_SQRT2, M_E, M_PI};
  vector<float> out{LongestIncreasingSub(in)};
  EXPECT_TRUE(equal(out.begin(), out.end(), ans.begin()));
}

/////////////////////////////////////////////
/// Test max subarray
/////////////////////////////////////////////

TEST(test_algo_sequence, max_sub_array_test_empty)
{
  vector<int> vec{};
  EXPECT_EQ(MaxSubarray(vec), 0);
}

TEST(test_algo_sequence, max_sub_array_test_one_element)
{
  vector<int> vec{1};
  EXPECT_EQ(MaxSubarray(vec), 1);
}

TEST(test_algo_sequence, max_sub_array_test_only_increasing)
{
  vector<int> vec{1, 2, 3, 4, 5, 6};
  int sum{accumulate(vec.begin(), vec.end(), 0)};
  EXPECT_EQ(MaxSubarray(vec), sum);
}

TEST(test_algo_sequence, max_sub_array_test_decreasing)
{
  vector<int> vec{7, 6, 5, 4, 3, 2, 1};
  int sum{accumulate(vec.begin(), vec.end(), 0)};
  EXPECT_EQ(MaxSubarray(vec), sum);
}

TEST(test_algo_sequence, max_sub_array_test_standard)
{
  vector<int> vec{-5, 5, 5, 5, -5, -5, -5, 5, 5, 5, 5, -5};
  EXPECT_EQ(MaxSubarray(vec), 20);
}
