///
/// \brief Source file for data mining algorithms.
/// \author alex011235
/// \date 2020-04-30
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
/// Change list:
/// 2015-08-14 KNN
/// 2015-08-16 K-means
/// 2020-07-19 DBSCAN
///

#ifndef ALGORITHM_DATA_MINING_DATA_MINING_ALGORITHMS_HPP_
#define ALGORITHM_DATA_MINING_DATA_MINING_ALGORITHMS_HPP_

#include <string>
#include <vector>

#include "algo_geometry.hpp"

namespace algo::data_mining {

// ///////////////////////////////////////////
// K-means
// ///////////////////////////////////////////

struct Centroid {
  geometry::Point p;
  double mean_x, mean_y;
  size_t size;
};

using Centroids = std::vector<Centroid>;
using Clusters = std::vector<geometry::Points>;

/// \brief Returns the clusters of K-means. Each cluster i in 1...i...k contains a set of points.
/// \param k Number of clusters.
/// \return Clusters. If k is greater than the points.size() it will return an empty object.
/// \link <a href="https://en.wikipedia.org/wiki/K-means_clustering">K-means, Wikipedia.</a>
Clusters KMeans(geometry::Points points, int8_t k);

// ///////////////////////////////////////////
// KNN
// ///////////////////////////////////////////

// Labeled point
struct LabeledPoint {
  double x, y, dist;
  std::string label;
};

using LabeledPoints = std::vector<LabeledPoint>;

/// \brief Returns clustered data based on the k neighbors in the labeled data. If an unlabeled point is nearest to four points
/// A,B,B,B and k is set to 3 then the unlabeled will get B as label.
/// \param unlabeled_data Data to label.
/// \param labeled_data Data with known labels in a 2D-space.
/// \return Labeled data based on the rules of KNN.
/// \link <a href="https://en.wikipedia.org/wiki/K-nearest_neighbors_algorithm">KNN, Wikipedia.</a>
LabeledPoints KNearestNeighbor(const geometry::Points& unlabeled_data, LabeledPoints& labeled_data, uint8_t k);

// ///////////////////////////////////////////
// DBSCAN
// ///////////////////////////////////////////

enum class DistFunc {
  Manhattan,///< L1, "Manhattan" distance.
  Euclidean ///< L2, Euclidean distance.
};

/// \brief Finds the clusters of DBSCAN algorithm. Depending on chosen max-distance eps and minimum amount of points in a cluster,
/// the algorithm will return n clusters. It's not possible to choose the number of clusters, which can be a benefit.
/// \details Density-based spatial clustering of application with noise.
/// \param points The input points to scan for clusters.
/// \param dist_func The distance function, e.g. L1 or L2.
/// \param eps The maximum distance between two neighbor points.
/// \param min_pts The minimum number of neighbors within the distance eps that a point must have.
/// \return A list of points with label. Label == "0" means noise. Label > "1" means cluster number.
/// \link <a href="https://en.wikipedia.org/wiki/DBSCAN">DBSCAN, Wikipedia.</a>
LabeledPoints DBSCAN(const geometry::Points& points, DistFunc dist_func, double eps, int min_pts);

}// namespace algo::data_mining

#endif//ALGORITHM_DATA_MINING_DATA_MINING_ALGORITHMS_HPP_
