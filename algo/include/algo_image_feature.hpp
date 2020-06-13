///
/// \brief Header  for image feature extraction algorithms.
/// \author alex011235
/// \date 2020-05-23
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2020-05-19 Hough lines transform
/// 2020-05-26 Hough circles transform
///

#ifndef ALGO_ALGO_INCLUDE_ALGO_IMAGE_FEATURE_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_IMAGE_FEATURE_HPP_

#include "algo_image_basic.hpp"

namespace algo::image::feature {

// //////////////////////////////////////////
//  Hough transform
// //////////////////////////////////////////

/// \brief Computes the Hough line transform.
/// \param im The input image.
/// \return An image/matrix with the line intersection vote.
Img HoughTransform(const Img& im);

// //////////////////////////////////////////
//  Corner
// //////////////////////////////////////////

enum class CornerDetType {
  kHarris,
  kShiTomasi,
};

struct GaussWindowSettings {
  Size size;  // Window size
  float sigma;// Standard deviation of Gaussian kernel
};

/// \brief Finds the corners in the input image.
/// \details This algorithm is based on the Harris
/// \param im The input image.
/// \param threshold The threshold used by the Harris algorithm to sort out weak corners.
/// \param det_type Corner detection measure type, Harris or Shi-Tomasi.
/// \return Corners.
/// \link <a href="https://en.wikipedia.org/wiki/Corner_detection">Corner detection, Wikipedia.</a>
Points Corners(const Img& im, const int& threshold, const CornerDetType& det_type = CornerDetType::kHarris,
               const int& n_best = 0, const int& min_dist = 0,
               const GaussWindowSettings& g_win_set = {Size{7, 7}, 1.0});

}// namespace algo::image::feature

#endif//ALGO_ALGO_INCLUDE_ALGO_IMAGE_FEATURE_HPP_