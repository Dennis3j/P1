// added.cpp
#include "added.h"
#include <algorithm>
#include <vector>
#include <limits> // using this to get "infinity" so I can start bestCost super high

// This function quickly gets the cost of the chunk xs[L..R].
// In P0 I looped through everything to compute the cost each time, which was a bit slower
// But now I'm using prefix sums, so I can get the sum of any part of the array pretty instantly
// Basically, prefix sums let me avoid looping through the whole section over and over like how P0 did
static double segmentCost(
    const std::vector<float>& xs,      // the sorted list of numbers we are working with
    const std::vector<double>& prefix, // prefix sums of xs so we can pull range sums fast
    int L, int R,                      // left and right boundaries of the segment
    double& outMedian                  // I fill this with the median so caller doesn't recompute it
) {
    int m = (L + R) / 2; // the median index of this chunk
    double med = xs[m];  // median value for this chunk
    outMedian = med;      // send the median back to the caller

    // sum of values from L to the median
    double sumLeft;
    if (L == 0)
        sumLeft = prefix[m]; // if we start at 0, the prefix already has the full sum
    else
        sumLeft = prefix[m] - prefix[L - 1]; // otherwise subtract to get just [L..m]

    // sum of values from median+1 to R
    double sumRight = prefix[R] - prefix[m];

    int leftCount  = m - L + 1; // how many elements are on the left side including the median
    int rightCount = R - m;     // how many are on the right side

    // These formulas basically do the |x - median| math without looping everytime
    // They work because prefix sums let me turn the whole group into one calculation.
    double costLeft  = leftCount * med - sumLeft;
    double costRight = sumRight - rightCount * med;

    return costLeft + costRight; // total L1 distance for this chunk
}

// This is the full P1 solver. It runs in O(n log n) time.
// Instead of looping through everything like P0,
// 1) sort once (this is the n log n part)
// 2) build prefix sums (O(n))
// 3) try all splits using fast cost lookups (O(n))
// This i
TwoMediansSolution computeTwoMediansSolution(float* numbers, int n) {
    TwoMediansSolution result{}; // struct with everything we want to return

    if (n < 2) {
        // same kind of safety check as P0 but now I return more info
        result.k = 1;
        result.medianLow = result.medianHigh = (n > 0 ? numbers[0] : 0.0);
        result.totalCost = 0.0;
        return result;
    }

    // Just like P0, I copy the numbers and sort them so I don't change the original array
    std::vector<float> xs(numbers, numbers + n);
    std::sort(xs.begin(), xs.end()); // this sort step is what gives us the big speedup later

    // this is  building prefix sums. prefix[i] stores the sum of everything
    // from xs[0] up to xs[i]. This lets me grab the sum of any range super fast
    // without looping through the numbers every time like P0 did
    std::vector<double> prefix(n);
    prefix[0] = xs[0];
    for (int i = 1; i < n; ++i) {
        prefix[i] = prefix[i - 1] + xs[i]; // keep adding the next number to build the running total
    }

    // using infinity so any real cost will replace this immediately
    double bestCost = std::numeric_limits<double>::infinity();

    // same as P0 but now I also store each cluster's median
    int    bestK    = 1;
    double bestMedLow  = xs[0];
    double bestMedHigh = xs[1];

    // Try every possible split point (k) the left side is [0..k-1], the right is [k..n-1]
    // In P0 I had to loop through everything to get the cost. Now segmentCost() is doing it faster because it uses prefix sums
    for (int k = 1; k <= n - 1; ++k) {
        double medLow  = 0.0;
        double medHigh = 0.0;

        // cost for left side of the split the cluster
        double lowCost  = segmentCost(xs, prefix, 0,     k - 1, medLow);

        // cost for right side
        double highCost = segmentCost(xs, prefix, k,     n - 1, medHigh);

        double total = lowCost + highCost; // total cost for this split

        // if this split is better, save it
        if (total < bestCost || (total == bestCost && k < bestK)) {
            bestCost    = total;
            bestK       = k;
            bestMedLow  = medLow;
            bestMedHigh = medHigh;
        }
    }

    // fill the result struct with everything we found
    result.k          = bestK;
    result.medianLow  = bestMedLow;
    result.medianHigh = bestMedHigh;
    result.totalCost  = bestCost;

    return result;
}

// This function now just calls the new function  and returns the size of the low cluster TwoMediansSolution 
int computeLowClusterCardinality(float* numbers, int n) {
    TwoMediansSolution sol = computeTwoMediansSolution(numbers, n);
    return sol.k; // just return the cluster size that contains the smallest value
}

