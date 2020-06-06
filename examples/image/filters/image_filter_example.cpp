///
/// \brief Example source code image filters.
/// \author alex011235
/// \date 2020-05-19
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <image_helpers.hpp>
#include <include/algo_image.hpp>
#include <map>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace algo::image;
using namespace algo::image::filter;
using namespace std;

namespace {
string testfile_path() { return "../testfiles/"; };
}// namespace

void RunFiltersExample()
{
  cv::Mat img = cv::imread(testfile_path() + "lena.png", 0);
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", img);

  std::map<string, KernelType> filters = {
      {"Sobel x", KernelType::SOBEL_X},
      {"Sobel y", KernelType::SOBEL_Y},
      {"Edge detect", KernelType::EDGE_DETECT},
      {"Smoothing", KernelType::SMOOTHING},
      {"Modest sharp", KernelType::SHARPEN_MODEST},
      {"Aggressive sharp", KernelType::SHARPEN_AGGRESSIVE},
      {"Gaussian blur", KernelType::GAUSSIAN_BLUR},
      {"Hard blur", KernelType::BLUR_HARD},
      {"Soft blur", KernelType::BLUR_SOFT},
      {"High pass", KernelType::HIGH_PASS},
      {"Emboss", KernelType::EMBOSS},
      {"Weighted average", KernelType::WEIGHTED_AVERAGE},
      {"Vertical dilation", KernelType::DILATION_VERTICAL},
      {"Horizontal dilation", KernelType::DILATION_HORIZONTAL},
      {"XY Dilation", KernelType::DILATION}};

  for (auto const& filter : filters) {
    Img im{MatToVec(img)};
    im = Convolve(im, filter.second);
    cv::Mat img2 = ImGrayToMat(im);
    cv::imshow(filter.first, img2);
  }

  cv::waitKey(0);
}

void RunFiltersColorExample()
{
  cv::Mat img = cv::imread(testfile_path() + "lena_color.png");
  img.convertTo(img, CV_8UC3);
  cv::imshow("Original", img);

  std::map<string, KernelType> filters = {
      {"Sobel x", KernelType::SOBEL_X},
      {"Sobel y", KernelType::SOBEL_Y},
      {"Edge detect", KernelType::EDGE_DETECT},
      {"Smoothing", KernelType::SMOOTHING},
      {"Modest sharp", KernelType::SHARPEN_MODEST},
      {"Aggressive sharp", KernelType::SHARPEN_AGGRESSIVE},
      {"Gaussian blur", KernelType::GAUSSIAN_BLUR},
      {"Hard blur", KernelType::BLUR_HARD},
      {"Soft blur", KernelType::BLUR_SOFT},
      {"High pass", KernelType::HIGH_PASS},
      {"Emboss", KernelType::EMBOSS},
      {"Weighted average", KernelType::WEIGHTED_AVERAGE},
      {"Vertical dilation", KernelType::DILATION_VERTICAL},
      {"Horizontal dilation", KernelType::DILATION_HORIZONTAL},
      {"XY Dilation", KernelType::DILATION}};

  for (auto const& filter : filters) {
    Img3 im{Mat3ToVec(img)};
    im = Convolve3(im, filter.second);
    cv::Mat img2 = Im3ToMat(im);
    cv::imshow(filter.first, img2);
  }

  cv::waitKey(0);
}

void RunMedianExample()
{
  cv::Mat img = cv::imread(testfile_path() + "lena_very_noisy.bmp", 0);
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", img);

  Img im{MatToVec(img)};
  Img res{MedianFilter(im, 3, 3)};
  cv::Mat mat{ImGrayToMat(res)};
  cv::imshow("Result of median filter", mat);

  cv::waitKey(0);
}

void RunMedian3Example()
{
  cv::Mat img = cv::imread(testfile_path() + "lena_noisy_color.png");
  img.convertTo(img, CV_8UC3);
  cv::imshow("Original", img);

  Img3 im{Mat3ToVec(img)};
  Img3 res{MedianFilter3(im, 6, 6)};
  cv::Mat mat{Im3ToMat(res)};
  cv::imshow("Result of median filter", mat);

  cv::waitKey(0);
}

void RunBinaryThresholdExample()
{
  cv::Mat img{cv::imread(testfile_path() + "receipt.png", 0)};
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", img);

  Img im{MatToVec(img)};
  Img res1{threshold::Fixed(im, 120, true)};
  cv::Mat mat_res1{ImGrayToMat(res1)};
  cv::imshow("Result, cut white true", mat_res1);

  Img res2{threshold::Fixed(im, 120, false)};
  cv::Mat mat_res2{ImGrayToMat(res2)};
  cv::imshow("Result, cut white false", mat_res2);

  cv::waitKey(0);
}

void RunAdaptiveThresholdExample()
{
  cv::Mat img{cv::imread(testfile_path() + "receipt.png", 0)};
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", img);

  Img im{MatToVec(img)};
  Img res1{threshold::Adaptive(im, 12, true)};
  cv::Mat mat_res1{ImGrayToMat(res1)};
  cv::imshow("Result, cut white true", mat_res1);

  Img res2{threshold::Adaptive(im, 12, false)};
  cv::Mat mat_res2{ImGrayToMat(res2)};
  cv::imshow("Result, cut white false", mat_res2);

  cv::waitKey(0);
}

int main(int argc, char** argv)
{
  //  RunFiltersExample();
  //  RunFiltersColorExample();
  //  RunMedianExample();
  //  RunMedian3Example();
  //  RunBinaryThresholdExample();
  RunAdaptiveThresholdExample();
  return 0;
}