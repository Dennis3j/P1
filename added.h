// added.h
#ifndef ADDED_H
#define ADDED_H

//Full solution container
struct TwoMediansSolution {
    int    k;          // size of the low cluster the min one
    double medianLow;  // median of the low cluster
    double medianHigh; // median of the high cluster
    double totalCost;  // sum of absolute deviations to both medians
};


// Returns the cardinality of the cluster that contains the minimum value
// under optimal 2-medians clustering.
int computeLowClusterCardinality(float* numbers, int n);

// Returns the full optimal solution (k, medians, total L1 cost)
TwoMediansSolution computeTwoMediansSolution(float* numbers, int n);


#endif

