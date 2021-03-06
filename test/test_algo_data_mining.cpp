///
/// \brief Unit tests for data mining algorithms.
/// \author alex011235
/// \date 2020-04-27
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <algorithm>

#include "algo.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace algo::data_mining;
using namespace algo::geometry;

/////////////////////////////////////////////
/// K-means
/////////////////////////////////////////////

TEST(test_algo_data_mining, kmeans_empty_input)
{
  Points points{};
  Clusters clusters{KMeans(points, 3)};
  EXPECT_TRUE(clusters.empty());
}

TEST(test_algo_data_mining, kmeans_zero_k)
{
  Points points{{0.212603, 0.553522},
                {0.194965, 0.527275},
                {0.219101, 0.52271},
                {0.220029, 0.527275},
                {0.206105, 0.529557},
                {0.206105, 0.51358},
                {0.207961, 0.512439},
                {0.220029, 0.524992},
                {0.211675, 0.536404}};

  Clusters clusters{KMeans(points, 0)};
  EXPECT_TRUE(clusters.empty());
}

TEST(test_algo_data_mining, kmeans_one_center)
{
  Points points{{0.212603, 0.553522},
                {0.194965, 0.527275},
                {0.219101, 0.52271},
                {0.220029, 0.527275},
                {0.206105, 0.529557},
                {0.206105, 0.51358},
                {0.207961, 0.512439},
                {0.220029, 0.524992},
                {0.211675, 0.536404}};

  Clusters clusters{KMeans(points, 1)};
  EXPECT_EQ(clusters.size(), 1);
}

TEST(test_algo_data_mining, kmeans_too_many_clusters)
{
  Points points{{0.212603, 0.553522},
                {0.194965, 0.527275},
                {0.219101, 0.52271},
                {0.220029, 0.527275},
                {0.206105, 0.529557},
                {0.206105, 0.51358},
                {0.207961, 0.512439},
                {0.220029, 0.524992},
                {0.211675, 0.536404}};

  Clusters clusters{KMeans(points, points.size() + 1)};
  EXPECT_TRUE(clusters.empty());
}

TEST(test_algo_data_mining, kmeans_standard)
{
  Points points{{0.184982, 0.571833},
                {0.186523, 0.623506},
                {0.184865, 0.525364},
                {0.200396, 0.555169},
                {0.116674, 0.563119},
                {0.211976, 0.632246},
                {0.184568, 0.597068},
                {0.224437, 0.55624},
                {0.239292, 0.57665},
                {0.164756, 0.562486},
                {0.179244, 0.572289},
                {0.210807, 0.566596},
                {0.20369, 0.541137},
                {0.165889, 0.626851},
                {0.194098, 0.58839},
                {0.214113, 0.624798},
                {0.159452, 0.628741},
                {0.147493, 0.538751},
                {0.141923, 0.547846},
                {0.1216, 0.577467},
                {0.167362, 0.582833},
                {0.283139, 0.230916},
                {0.27045, 0.322248},
                {0.193272, 0.237957},
                {0.20184, 0.273536},
                {0.223819, 0.296191},
                {0.257816, 0.262981},
                {0.235152, 0.189414},
                {0.201989, 0.289344},
                {0.231877, 0.245095},
                {0.252119, 0.2847},
                {0.267838, 0.24958},
                {0.188088, 0.312208},
                {0.309562, 0.197298},
                {0.237038, 0.251317},
                {0.320457, 0.23209},
                {0.308763, 0.278195},
                {0.231026, 0.280286},
                {0.299847, 0.250155},
                {0.297428, 0.279454},
                {0.249367, 0.228016},
                {0.276532, 0.247305},
                {0.285289, 0.353846},
                {0.285543, 0.250054},
                {0.234267, 0.278155},
                {0.295207, 0.251877},
                {0.266506, 0.295313},
                {0.260809, 0.256796},
                {0.131869, 0.270825},
                {0.61246, 0.535105},
                {0.49022, 0.480947},
                {0.571812, 0.476382},
                {0.571209, 0.486313},
                {0.534424, 0.511149},
                {0.539493, 0.614158},
                {0.507716, 0.498865},
                {0.543112, 0.524083},
                {0.533156, 0.600863},
                {0.465633, 0.518065},
                {0.52073, 0.509613},
                {0.507347, 0.477256},
                {0.539641, 0.526269},
                {0.594922, 0.553717},
                {0.561669, 0.569483},
                {0.512592, 0.491739},
                {0.544763, 0.515179},
                {0.477403, 0.505459},
                {0.560837, 0.587543},
                {0.537734, 0.607844},
                {0.4756, 0.545831},
                {0.641794, 0.556536},
                {0.598199, 0.5677},
                {0.478587, 0.517512},
                {0.503254, 0.498964},
                {0.508809, 0.483732},
                {0.60105, 0.460454},
                {0.540247, 0.470797},
                {0.484141, 0.503637},
                {0.523965, 0.589127},
                {0.560036, 0.47117},
                {0.50798, 0.518863},
                {0.606842, 0.46195},
                {0.548587, 0.554264},
                {0.553396, 0.553847},
                {0.577529, 0.493469}};

  Clusters clusters{KMeans(points, 3)};
  EXPECT_EQ(clusters.size(), 3);
}

/////////////////////////////////////////////
/// KNN
/////////////////////////////////////////////

TEST(test_algo_data_mining, knn_k_greater_than_unlabeled_data)
{
  Points unlabeled_data{
      {0.0, 1.0}};

  LabeledPoints labeled_points{
      {0.0, 1.0, 0.0, "Jupiter"},
      {0.0, 0.5, 0.0, "Mars"}};

  EXPECT_TRUE(KNearestNeighbor(unlabeled_data, labeled_points, labeled_points.size() + 1).empty());
}

TEST(test_algo_data_mining, knn_k_is_zero)
{
  Points unlabeled_data{
      {0.0, 1.0}};

  LabeledPoints labeled_points{
      {0.0, 1.0, 0.0, "Jupiter"},
      {0.0, 0.5, 0.0, "Mars"}};

  EXPECT_TRUE(KNearestNeighbor(unlabeled_data, labeled_points, 0).empty());
}

TEST(test_algo_data_mining, knn_empty_unlabeled_data)
{
  Points unlabeled_data{};

  LabeledPoints labeled_points{
      {0.0, 1.0, 0.0, "Jupiter"},
      {0.0, 0.5, 0.0, "Mars"}};

  EXPECT_TRUE(KNearestNeighbor(unlabeled_data, labeled_points, 5).empty());
}

TEST(test_algo_data_mining, knn_empty_labeled_data)
{
  Points unlabeled_data{
      {0.0, 1.0}};

  LabeledPoints labeled_points{};

  EXPECT_TRUE(KNearestNeighbor(unlabeled_data, labeled_points, 5).empty());
}

TEST(test_algo_data_mining, knn_standard)
{
  Points unlabeled_data{
      {0.186546, 0.811486},// C1
      {0.266705, 0.872845},// C1
      {0.16989, 0.933001}, // C1
      {0.069951, 0.822314},// C1
      {0.148028, 0.692378},// C1
      {0.262541, 0.733284},// C1
      {0.483239, 0.29535}, // C2
      {0.595671, 0.207523},// C2
      {0.64564, 0.350694}, // C2
      {0.501978, 0.427693},// C2
      {0.660214, 0.214742},// C2
      {0.63523, 0.433708}  // C2
  };

  LabeledPoints labeled_points{
      {0.199039, 0.888485, 0.0, "C1"},
      {0.125126, 0.860814, 0.0, "C1"},
      {0.110551, 0.765768, 0.0, "C1"},
      {0.212572, 0.723659, 0.0, "C1"},
      {0.268788, 0.806674, 0.0, "C1"},
      {0.57485, 0.446943, 0.0, "C2"},
      {0.43327, 0.383178, 0.0, "C2"},
      {0.528004, 0.238804, 0.0, "C2"},
      {0.632107, 0.296553, 0.0, "C2"},
      {0.539455, 0.348287, 0.0, "C2"}};

  LabeledPoints classified{KNearestNeighbor(unlabeled_data, labeled_points, 2)};

  for_each(classified.begin(), classified.begin() + 5, [](const LabeledPoint& lp) {
    EXPECT_EQ(lp.label, "C1");
  });

  for_each(classified.begin() + 6, classified.end(), [](const LabeledPoint& lp) {
    EXPECT_EQ(lp.label, "C2");
  });
}

/////////////////////////////////////////////
/// DBSCAN
/////////////////////////////////////////////

TEST(test_algo_data_mining, dbscan_1)
{
  Points pts{
      {0.0428843, 0.967891},
      {0.0418432, 0.943829},
      {0.0564176, 0.928188},
      {0.0751562, 0.937813},
      {0.0720331, 0.963079},
      {0.0616228, 0.970297},
      {0.0564176, 0.953454},
      {0.0886895, 0.952251},
      {0.0793203, 0.982328},
      {0.0605818, 0.984735},
      {0.032474, 0.95586},
      {0.871543, 0.104055},
      {0.862174, 0.081196},
      {0.867379, 0.0547275},
      {0.903815, 0.0619462},
      {0.900692, 0.0908209},
      {0.889241, 0.0787898},
      {0.890282, 0.116086},
      {0.911102, 0.0884147},
      {0.885077, 0.05954},
      {0.0907716, 0.0980396},
      {0.917348, 0.972703}};

  LabeledPoints lpts{DBSCAN(pts, DistFunc::Euclidean, 0.2, 3)};

  EXPECT_EQ(lpts.size(), pts.size());
  int num_0 = std::count_if(lpts.begin(), lpts.end(), [](const auto& lpt) { return lpt.label == "1"; });
  EXPECT_EQ(num_0, 11);
  int num_1 = std::count_if(lpts.begin(), lpts.end(), [](const auto& lpt) { return lpt.label == "2"; });
  EXPECT_EQ(num_1, 9);
  int num_noise = std::count_if(lpts.begin(), lpts.end(), [](const auto& lpt) { return lpt.label == "0"; });
  EXPECT_EQ(num_noise, 2);
}

TEST(test_algo_data_mining, dbscan_2)
{
  Points pts{
      {0.142823, 0.856001},
      {0.145946, 0.82833},
      {0.164685, 0.829533},
      {0.161562, 0.858408},
      {0.0262278, 0.963079},
      {0.0262278, 0.722456},
      {0.279198, 0.712831},
      {0.238598, 0.970297},
      {0.155315, 0.842767},
      {0.137618, 0.84397},
      {0.148028, 0.872845},
      {0.170931, 0.851189},
      {0.489486, 0.338662},
      {0.48428, 0.326631},
      {0.489486, 0.3146},
      {0.498855, 0.315803},
      {0.50406, 0.329038},
      {0.503019, 0.345881},
      {0.483239, 0.3531},
      {0.474911, 0.335053},
      {0.476993, 0.3146},
      {0.485321, 0.29896},
      {0.498855, 0.360318},
      {0.587342, 0.471005},
      {0.402039, 0.165414},
      {0.348947, 0.434912},
      {0.632107, 0.170226}};

  LabeledPoints lpts{DBSCAN(pts, DistFunc::Euclidean, 0.11, 5)};

  EXPECT_EQ(lpts.size(), pts.size());
  int num_0 = std::count_if(lpts.begin(), lpts.end(), [](const auto& lpt) { return lpt.label == "1"; });
  EXPECT_EQ(num_0, 8);
  int num_1 = std::count_if(lpts.begin(), lpts.end(), [](const auto& lpt) { return lpt.label == "2"; });
  EXPECT_EQ(num_1, 11);
  int num_noise = std::count_if(lpts.begin(), lpts.end(), [](const auto& lpt) { return lpt.label == "0"; });
  EXPECT_EQ(num_noise, 8);
}

TEST(test_algo_data_mining, dbscan_3)
{
  Points pts{
      {0.117838, 0.806674},
      {0.111592, 0.286929},
      {0.602958, 0.640644},
      {0.2209, 0.517926},
      {0.207367, 0.492661},
      {0.20008, 0.463786},
      {0.221941, 0.439724},
      {0.254213, 0.451755},
      {0.263582, 0.49988},
      {0.25109, 0.528754},
      {0.241721, 0.505895},
      {0.228187, 0.479427},
      {0.162603, 0.301366},
      {0.128249, 0.310991},
      {0.1397, 0.291741},
      {0.25109, 0.479427},
      {0.237557, 0.456568},
      {0.226105, 0.502286},
      {0.212572, 0.462583}};

  LabeledPoints lpts{DBSCAN(pts, DistFunc::Euclidean, 0.11, 7)};

  EXPECT_EQ(lpts.size(), pts.size());
  int num_0 = std::count_if(lpts.begin(), lpts.end(), [](const auto& lpt) { return lpt.label == "1"; });
  EXPECT_EQ(num_0, 13);
  int num_noise = std::count_if(lpts.begin(), lpts.end(), [](const auto& lpt) { return lpt.label == "0"; });
  EXPECT_EQ(num_noise, 6);
}

TEST(test_algo_data_mining, dbscan_forbidden_cases)
{
  Points pts{
      {0.0428843, 0.967891},
      {0.0418432, 0.943829},
      {0.885077, 0.05954},
      {0.0907716, 0.0980396},
      {0.917348, 0.972703}};

  // Test min_points too big
  LabeledPoints lpts{DBSCAN(pts, DistFunc::Euclidean, 0.2, 5)};
  EXPECT_TRUE(lpts.empty());

  // Test min_points zero
  lpts = DBSCAN(pts, DistFunc::Euclidean, 0.2, 0);
  EXPECT_TRUE(lpts.empty());

  // Test empty input
  lpts = DBSCAN({}, DistFunc::Euclidean, 0.2, 2);
  EXPECT_TRUE(lpts.empty());

  // Test eps is 0.0
  lpts = DBSCAN(pts, DistFunc::Euclidean, 0.0, 2);
  EXPECT_TRUE(lpts.empty());

  //Test negative eps
  lpts = DBSCAN(pts, DistFunc::Euclidean, -0.1, 2);
  EXPECT_TRUE(lpts.empty());
}
