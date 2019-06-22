/** ------------------------------------------------------------
* Sorting tests
* Alexander Karlsson, begun 2015-06-21
* -------------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdio.h>
#include <time.h>
#include "../heapsort.cc"
#include "../quicksort.cc"
#include "../insertion_sort.cc"
#include "../merge_sort.cc"
#include "../bubble_sort.cc"
#include "../gnome_sort.cpp"
#include "../bucket_sort.cc"

using namespace std;

int main() {
	vector<int> vec(20000);
	iota(vec.begin(), vec.end(), 0);
	random_shuffle(vec.begin(),vec.end());

	clock_t t0, t1;

	/* QUICKSORT TEST */

	cout << "-------------------------------------------------------" << endl;
	cout << "quicksort test " << endl;
	cout << endl;
	t0 = clock();
	quicksort(vec, 0, vec.size()-1);
	t1 = clock();
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);

	cout << endl;
	for (size_t i = 0; i < 4; i++) {
		cout << vec[i] << " ";
	}
	cout << endl;

	for (size_t i = vec.size()-4; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;

	/* HEAPSORT TEST */

	cout << "-------------------------------------------------------" << endl;
	cout << "heapsort test  " << endl;
	cout << endl;
	random_shuffle(vec.begin(),vec.end());
	t0 = clock();
	heapsort(vec, vec.size());
	t1 = clock();
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);

	cout << endl;
	for (size_t i = 0; i < 4; i++) {
		cout << vec[i] << " ";
	}
	cout << endl;

	for (size_t i = vec.size()-4; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}

	cout << endl;


	/* INSERTION SORT */

	cout << "-------------------------------------------------------" << endl;
	cout << "Insertion sort test" << endl;
	cout << endl;
	random_shuffle(vec.begin(),vec.end());
	t0 = clock();
	insertion_sort(vec);
	t1 = clock();
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);

	cout << endl;
	for (size_t i = 0; i < 4; i++) {
		cout << vec[i] << " ";
	}
	cout << endl;

	for (size_t i = vec.size()-4; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}

	cout << endl;


	/* MERGE SORT */
	/*
	cout << "-------------------------------------------------------" << endl;
	cout << "Merge sort test  " << endl;
	cout << endl;

	random_shuffle(vec.begin(),vec.end());
	t0 = clock();
	vector<int> res = merge_sort(vec);
	t1 = clock();
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);

	cout << endl;
	for (size_t i = 0; i < 4; i++) {
		cout << res[i] << " ";
	}
	cout << endl;

	for (size_t i = res.size()-4; i < res.size(); i++) {
		cout << res[i] << " ";
	}

	cout << endl;
	*/

	/* BUBBLE SORT */

	cout << "-------------------------------------------------------" << endl;
	cout << "Bubble sort test" << endl;
	cout << endl;

	random_shuffle(vec.begin(),vec.end());
	t0 = clock();
	vector<int> res2 = bubble_sort(vec);
	t1 = clock();
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);

	cout << endl;
	for (size_t i = 0; i < 4; i++) {
		cout << res2[i] << " ";
	}
	cout << endl;

	for (size_t i = res2.size()-4; i < res2.size(); i++) {
		cout << res2[i] << " ";
	}

	cout << endl;

	/* GNOME SORT */

	cout << "-------------------------------------------------------" << endl;
	cout << "Gnome sort " << endl;
	cout << endl;

	random_shuffle(vec.begin(),vec.end());
	res2 = vec;
	t0 = clock();
	gnome_sort(res2);
	t1 = clock();
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);

	cout << endl;
	for (size_t i = 0; i < 4; i++) {
		cout << res2[i] << " ";
	}
	cout << endl;

	for (size_t i = res2.size()-4; i < res2.size(); i++) {
		cout << res2[i] << " ";
	}

	cout << endl;

	/* BUCKET SORT */

	cout << "-------------------------------------------------------" << endl;
	cout << "Bucket sort " << endl;
	cout << endl;

	random_shuffle(vec.begin(),vec.end());
	res2 = vec;
	t0 = clock();
	bucket_sort(res2);
	t1 = clock();
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);

	cout << endl;
	for (size_t i = 0; i < 4; i++) {
		cout << res2[i] << " ";
	}
	cout << endl;

	for (size_t i = res2.size()-4; i < res2.size(); i++) {
		cout << res2[i] << " ";
	}

	cout << endl;




}