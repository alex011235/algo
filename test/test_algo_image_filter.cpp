///
/// \brief Unit tests for image algorithms.
/// \author alex011235
/// \date 2020-05-18
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <algorithm>
#include <array>
#include <vector>

#include "gtest/gtest.h"
#include "include/algo.hpp"

using namespace std;
using namespace algo::image;
using namespace algo::image::filter;

/////////////////////////////////////////////
/// Kernels and convolutions
/////////////////////////////////////////////

TEST(test_algo_image, test_kernels)
{
  Data8 data{10, 20, 30, 40,
             50, 60, 70, 80,
             90, 100, 110, 120,
             130, 140, 150, 160};
  Img im{data, Size{4, 4}};

  Data8_3 data3{data, data, data};
  Img3 im3{data3, Size{4, 4}};

  vector<filter::KernelType> kernels{
      KernelType::SOBEL_X, KernelType::SOBEL_Y, KernelType::EDGE_DETECT,
      KernelType::SMOOTHING, KernelType::SHARPEN_MODEST, KernelType::SHARPEN_AGGRESSIVE,
      KernelType::GAUSSIAN_BLUR, KernelType::BLUR_HARD, KernelType::BLUR_SOFT, KernelType::EMBOSS,
      KernelType::WEIGHTED_AVERAGE, KernelType::DILATION_VERTICAL, KernelType::DILATION_HORIZONTAL,
      KernelType::DILATION, KernelType::HIGH_PASS};

  for (const auto& kernel : kernels) {
    Img res{filter::Convolve(im, kernel)};
    EXPECT_FALSE(equal(im.data.begin(), im.data.end(), res.data.begin()));

    Img3 res3{filter::Convolve3(im3, kernel)};
    EXPECT_FALSE(equal(im.data.begin(), im.data.end(), res3.data.at(Red).begin()));
    EXPECT_FALSE(equal(im.data.begin(), im.data.end(), res3.data.at(Green).begin()));
    EXPECT_FALSE(equal(im.data.begin(), im.data.end(), res3.data.at(Blue).begin()));
  }
}

/////////////////////////////////////////////
/// Thresholding
/////////////////////////////////////////////

TEST(test_algo_image, test_binary_thresholding)
{
  Data8 data{0, 10, 20, 30,
             40, 50, 60, 70,
             80, 90, 100, 110,
             120, 130, 140, 150};

  Img im{data, Size{4, 4}};
  Img imt1{filter::threshold::Fixed(im, 90, true)};

  int ct1{static_cast<int>(std::count_if(imt1.data.begin(), imt1.data.end(), [](const uint8_t& x) { return x == 255; }))};
  EXPECT_EQ(ct1, 6);

  imt1 = {filter::threshold::Fixed(im, 90, false)};
  ct1 = static_cast<int>(std::count_if(imt1.data.begin(), imt1.data.end(), [](const uint8_t& x) { return x == 255; }));
  EXPECT_EQ(ct1, 10);
}
