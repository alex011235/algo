///
/// \brief Source file for transform algorithms.
/// \author alex011235
/// \date 2020-04-19
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_transform.hpp"

#include <algorithm>

namespace algo::transform {

namespace {
constexpr auto IsPowOf2 = [](auto x) {
  return (x != 0) && ((x & (x - 1)) == 0);
};
}//namespace

FftTransf FFT(const FftTransf &A)
{
  auto N = A.size();
  if (N <= 1) {
    return A;
  }
  if (!IsPowOf2(N)) {
    return FftTransf{};
  }

  auto even_part = A[std::slice(0, N / 2, 2)];
  auto odd_part = A[std::slice(1, N / 2, 2)];
  auto res_ev = FFT(even_part);
  auto res_odd = FFT(odd_part);
  auto B = A;

  for (size_t i = 0; i < N / 2; ++i) {
    auto comp = std::polar(1.0, -2 * M_PI * i / N) * res_odd[i];
    B[i] = res_ev[i] + comp;
    B[i + N / 2] = res_ev[i] - comp;
  }
  return B;
}

FftTransf IFFT(const FftTransf &B)
{
  size_t N{B.size()};
  if (N == 0) {
    return B;
  }
  if (!IsPowOf2(N)) {
    return FftTransf{};
  }

  auto T = B;
  std::transform(begin(T), end(T), begin(T),
                 [&](std::complex<double> &c) { return conj(c); });
  auto A = FFT(T);
  std::transform(begin(A), end(A), begin(A),
                 [&](std::complex<double> &c) { return conj(c); });

  std::for_each(begin(A), end(A), [&](std::complex<double> &comp) {
    std::complex<double> c(real(comp) / N, imag(comp) / N);
    comp = c;
  });
  return A;
}

}// namespace algo::transform