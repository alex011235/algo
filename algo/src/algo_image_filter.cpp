///
/// \brief Source code for image filtering algorithms.
/// \author alex011235
/// \date 2020-05-18
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "algo_image_filter.hpp"

#include <cmath>

namespace algo::image::filter {

/////////////////////////////////////////////
/// Kernels
/////////////////////////////////////////////

namespace {

using Kernel = std::array<float, 9>;

constexpr Kernel kernel_sobel_x{-1.0 / 2.0, 0, 1.0 / 2.0, -2.0 / 2.0, 0, 2.0 / 2.0, -1.0 / 2.0, 0, 1.0 / 2.0};
constexpr Kernel kernel_sobel_y{-1.0 / 2.0, -2.0 / 2.0, -1.0 / 2.0, 0, 0, 0, 1.0 / 2.0, 2.0 / 2.0, 1.0 / 2.0};
constexpr Kernel kernel_edge{1.0, 0.0, -1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0};
constexpr Kernel kernel_smooth{1.0 / 13.0, 2.0 / 13.0, 1.0 / 13.0, 2.0 / 13.0, 4.0 / 13.0, 2.0 / 13.0, 1.0 / 13.0, 2.0 / 13.0, 1.0 / 13.0};
constexpr Kernel kernel_sharp_agg{0, -1.0, 0, -1.0, 5.0, -1.0, 0, -1.0, 0};
constexpr Kernel kernel_sharp_mod{-1.0 / 9.0, -1.0 / 9.0, -1.0 / 9.0, -1.0 / 9.0, 17.0 / 9.0, -1.0 / 9.0, -1.0 / 9.0, -1.0 / 9.0, -1.0 / 9.0};
constexpr Kernel kernel_gauss_blur{1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0, 2.0 / 16.0, 4.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0};
constexpr Kernel kernel_blur_hard{1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0};
constexpr Kernel kernel_blur_soft{0.0, 1.0 / 8.0, 0.0, 1.0 / 8.0, 1.0 / 2.0, 1.0 / 8.0, 0.0, 1.0 / 8.0, 0.0};
constexpr Kernel kernel_emboss{-2.0, -1.0, 0.0, -1.0, 1.0, 1.0, 0.0, 1.0, 2.0};
constexpr Kernel kernel_weighted{1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0, 2.0 / 16.0, 4.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0};
constexpr Kernel kernel_dilation_v{0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0};
constexpr Kernel kernel_dilation_h{0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0};
constexpr Kernel kernel_dilation{0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0};
constexpr Kernel kernel_high_pass{-1.0, -1.0, -1.0, -1.0, 8.0, -1.0, -1.0, -1.0, -1.0};
constexpr Kernel kernel_nothing{0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0};

Kernel GetKernel(const KernelType& filter_type)
{
  switch (filter_type) {
    case KernelType::SOBEL_X:
      return kernel_sobel_x;
    case KernelType::SOBEL_Y:
      return kernel_sobel_y;
    case KernelType::EDGE_DETECT:
      return kernel_edge;
    case KernelType::SMOOTHING:
      return kernel_smooth;
    case KernelType::SHARPEN_MODEST:
      return kernel_sharp_mod;
    case KernelType::SHARPEN_AGGRESSIVE:
      return kernel_sharp_agg;
    case KernelType::GAUSSIAN_BLUR:
      return kernel_gauss_blur;
    case KernelType::BLUR_HARD:
      return kernel_blur_hard;
    case KernelType::BLUR_SOFT:
      return kernel_blur_soft;
    case KernelType::EMBOSS:
      return kernel_emboss;
    case KernelType::WEIGHTED_AVERAGE:
      return kernel_weighted;
    case KernelType::DILATION_VERTICAL:
      return kernel_dilation_v;
    case KernelType::DILATION_HORIZONTAL:
      return kernel_dilation_h;
    case KernelType::DILATION:
      return kernel_dilation;
    case KernelType::HIGH_PASS:
      return kernel_high_pass;
  }
  return kernel_nothing;
}

}// namespace

/////////////////////////////////////////////
/// Convolutions
/////////////////////////////////////////////

Data8 ConvolvePriv(const Data8& im, size_t rows, size_t cols, KernelType filter_type)
{
  Data8 res(im.size(), 0);
  const Kernel filter{GetKernel(filter_type)};
  uint8_t dim{3U};
  uint8_t sz{static_cast<uint8_t>(dim >> 1U)};

  // Filtering window
  for (size_t i = sz; i < rows - sz; i++) {
    for (size_t j = sz; j < cols - sz; j++) {
      float sum = 0;
      for (uint8_t k = 0; k < dim; k++) {
        for (uint8_t m = 0; m < dim; m++) {
          // Multiply components
          auto im_num = static_cast<float>((im[(i + k - sz) * cols + (j + m - sz)]));
          float filt_num = filter[k * dim + m];
          sum += im_num * filt_num;
        }
      }
      // Check overflow
      if (sum < 0) sum = 0;
      if (sum > 255) sum = 255;

      res[i * cols + j] = static_cast<uint8_t>(sum);
    }
  }
  return res;
}

Img Convolve(const Img& im, KernelType filter_type)
{
  Img res{im};
  res.data = ConvolvePriv(res.data, im.size.rows, im.size.cols, filter_type);
  return res;
}

Img3 Convolve3(const Img3& im, KernelType filter_type)
{
  Img3 res{im};
  res.data[Red] = ConvolvePriv(res.data[Red], im.size.rows, im.size.cols, filter_type);
  res.data[Green] = ConvolvePriv(res.data[Green], im.size.rows, im.size.cols, filter_type);
  res.data[Blue] = ConvolvePriv(res.data[Blue], im.size.rows, im.size.cols, filter_type);
  return res;
}

/////////////////////////////////////////////
/// Gaussian blur
/////////////////////////////////////////////

namespace {
/// \brief Computes the 2D gauss value at x, y with standard deviation sigma.
constexpr auto Gauss2D = [](auto x, auto y, auto sigma) {
  float a = 1.0 / (2.0 * M_PI * sigma * sigma);
  float b = -(x * x + y * y) / (2.0 * sigma * sigma);
  return a * std::pow(M_E, b);
};

ImgF GaussianKernel(const Size& size, const float& sigma)
{
  ImgF kernel{Dataf(size.cols * size.rows, 0), size};
  const int kDimX{size.cols / 2};
  const int kDimY{size.rows / 2};

  for (int x = size.cols - 1; x >= 0; --x) {
    for (int y = size.rows - 1; y >= 0; --y) {
      kernel.Set(x, y, Gauss2D(kDimX - x, kDimY - y, sigma));
    }
  }
  return kernel;
}
}//namespace

Img GaussianBlur(const Img& im, const Size& size, const float& sigma)
{
  // Size x,y must be odd! Test
  if (size.rows % 2 == 0 || size.cols % 2 == 0) {
    return im;
  }

  const ImgF kernel{GaussianKernel(size, sigma)};
  Img res{im};

  const size_t kCols = size.cols;
  const size_t kRows = size.rows;
  const size_t kSizeX = kCols >> 1U;
  const size_t kSizeY = kRows >> 1U;

  // Filtering window
  for (size_t x = 0; x < im.size.cols; x++) {
    for (size_t y = 0; y < im.size.rows; y++) {

      double sum = 0;
      for (size_t m = 0; m < size.cols; m++) {
        for (size_t k = 0; k < size.rows; k++) {
          // Avoid read and write outside bounds of image
          const size_t kPosX = std::min(std::max(0UL, x + m - kSizeX), static_cast<size_t>(im.size.cols - 1));
          const size_t kPosY = std::min(std::max(0UL, y + k - kSizeY), static_cast<size_t>(im.size.rows - 1));
          const auto kImVal = static_cast<double>(im.At(kPosX, kPosY));
          const float kVal{kernel.At(m, k)};
          // Image value * kernel value
          sum += kImVal * kVal;
        }
      }

      uint8_t res_val = static_cast<uint8_t>(std::min(std::max(0.0, sum), 255.0));
      res.Set(x, y, res_val);
    }
  }
  return res;
}

/////////////////////////////////////////////
/// Median filters
/////////////////////////////////////////////

Data8 MedianFilterPriv(const Data8& im, const int& rows, const int& cols, const int& w_width, const int& w_height)
{
  Data8 res(rows * cols, 0);
  int edge_x{w_width / 2};
  int edge_y{w_height / 2};

  for (size_t x = 0; x < cols - edge_x; x++) {
    for (size_t y = 0; y < rows - edge_y; y++) {

      std::vector<int> window(w_height * w_height, 0);
      int i{0};

      for (size_t wx = 0; wx < w_width; wx++) {
        for (size_t wy = 0; wy < w_height; wy++) {
          window[i] = im[(y + wy - edge_y) * cols + (x + wx - edge_x)];
          i++;
        }
      }
      std::sort(window.begin(), window.end());
      res[y * cols + x] = window[w_width * w_height / 2];
    }
  }
  return res;
}

Img MedianFilter(const Img& im, const int& w_width, const int& w_height)
{
  Img res;
  res.data = MedianFilterPriv(im.data, im.size.rows, im.size.cols, w_width, w_height);
  res.size = im.size;
  return res;
}

Img3 MedianFilter3(const Img3& im, const int& w_width, const int& w_height)
{
  Img3 res;
  res.data[Red] = MedianFilterPriv(im.data[Red], im.size.rows, im.size.cols, w_width, w_height);
  res.data[Green] = MedianFilterPriv(im.data[Green], im.size.rows, im.size.cols, w_width, w_height);
  res.data[Blue] = MedianFilterPriv(im.data[Blue], im.size.rows, im.size.cols, w_width, w_height);
  res.size = im.size;
  return res;
}

}// namespace algo::image::filter