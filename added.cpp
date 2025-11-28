// added.cpp
#include "added.h"
#include <algorithm>
#include <vector>
#include <limits>

// Helper: compute L1 cost of segment [L..R] in sorted xs, using prefix sums.
// xs is sorted; prefix[i] = xs[0] + ... + xs[i].
static double segmentCost(
    const std::vector<float>& xs,
    const std::vector<double>& prefix,
    int L, int R,
    double& outMedian
) {
    int m = (L + R) / 2;      // median index
    double med = xs[m];
    outMedian = med;

    double sumLeft;
    if (L == 0)
        sumLeft = prefix[m];
    else
        sumLeft = prefix[m] - prefix[L - 1];

    double sumRight = prefix[R] - prefix[m];

    int leftCount  = m - L + 1;
    int rightCount = R - m;

    double costLeft  = leftCount * med - sumLeft;
    double costRight = sumRight - rightCount * med;

    return costLeft + costRight;
}

// Full optimal 2-medians solution in O(n log n)
TwoMediansSolution computeTwoMediansSolution(float* numbers, int n) {
    TwoMediansSolution result{};
    if (n < 2) {
        // Caller should guard; safe default
        result.k = 1;
        result.medianLow = result.medianHigh = (n > 0 ? numbers[0] : 0.0);
        result.totalCost = 0.0;
        return result;
    }

    // Work on a sorted copy (keeps caller data intact, as in P0)
    std::vector<float> xs(numbers, numbers + n);
    std::sort(xs.begin(), xs.end());

    // Build prefix sums in double precision
    std::vector<double> prefix(n);
    prefix[0] = xs[0];
    for (int i = 1; i < n; ++i) {
        prefix[i] = prefix[i - 1] + xs[i];
    }

    double bestCost = std::numeric_limits<double>::infinity();
    int    bestK    = 1;
    double bestMedLow  = xs[0];
    double bestMedHigh = xs[1];

    // Try every split: low = [0..k-1], high = [k..n-1]
    for (int k = 1; k <= n - 1; ++k) {
        double medLow  = 0.0;
        double medHigh = 0.0;

        double lowCost  = segmentCost(xs, prefix, 0,     k - 1, medLow);
        double highCost = segmentCost(xs, prefix, k,     n - 1, medHigh);
        double total    = lowCost + highCost;

        if (total < bestCost || (total == bestCost && k < bestK)) {
            bestCost    = total;
            bestK       = k;
            bestMedLow  = medLow;
            bestMedHigh = medHigh;
        }
    }

    result.k          = bestK;
    result.medianLow  = bestMedLow;
    result.medianHigh = bestMedHigh;
    result.totalCost  = bestCost;
    return result;
}

// Keep the old interface, but now use the faster algorithm
int computeLowClusterCardinality(float* numbers, int n) {
    TwoMediansSolution sol = computeTwoMediansSolution(numbers, n);
    return sol.k;
}

