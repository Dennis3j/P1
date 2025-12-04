##pseudocode
```pseudo
TWO-MEDIANS(X)
    if length(X) < 2
        error "need at least two numbers"

    # Sort the numbers firs, this is what is going to allow us to speed everything else up
    sort X in ascending order
    n = length(X)

    # Build prefix sums this where we improved from P0
    # prefix[i] will hold the sum of X[0] + X[1] + X[2] all the way up to  X[i]
    # With this, we can grab the sum of ANY chunk instantly (in O(1))
    prefix[0] = X[0]
    for i = 1 to n - 1
        prefix[i] = prefix[i - 1] + X[i]

    # Start the best cost at infinity so the first real cost is always smaller
    bestCost = infinity
    bestK = 1   # this will store the size of the cluster with the smallest value

    # This function  SEGMENT-COST(L, R)
    # Computes the L1 distance (sum of |x - median|) for the chunk X[L..R]
    # In P0, I had to loop through everything inside this range every time
    # Now I use prefix sums to do the leftover math instantly
    # This lets the whole thing run faster since we are not going through every single point
    SEGMENT-COST(L, R):
        # Get the median index and the median value
        m = floor((L + R) / 2)
        med = X[m]

        # Sum of the left half (L..m)
        if L == 0
            sumLeft = prefix[m]
        else
            sumLeft = prefix[m] - prefix[L - 1]

        # Sum of the right half (m+1..R)
        sumRight = prefix[R] - prefix[m]

        # Number of items on each side
        leftCount  = m - L + 1
        rightCount = R - m

        # These formulas compute |x - median| without looping
        costLeft  = leftCount * med - sumLeft
        costRight = sumRight - rightCount * med

        return costLeft + costRight


    # Try splitting the sorted array at every position k
    # Left cluster = X[0..k-1]
    # Right cluster = X[k..n-1]
    # In P0 this was O(n^2) because we recomputed cost by looping
    # Now each split check is O(1) because SEGMENT-COST is O(1)
    # So the whole loop is O(n)
    for k = 1 to n - 1
        costL = SEGMENT-COST(0, k - 1)
        costR = SEGMENT-COST(k, n - 1)
        total = costL + costR

        # keep the best split
        if total < bestCost or (total == bestCost and k < bestK)
            bestCost = total
            bestK = k


    # bestCost  = the optimal total L1 cost
    # bestK     = the size of the cluster containing the smallest value

```
Time complexity:
    Sorting is O(n log n).
    Building prefix sums is O(n).
    The loop over k runs O(n) times and each SEGMENT-COST call is O(1),
    so that part is O(n).
    Overall time: O(n log n).

Space complexity:
    I store the sorted array X and a prefix array of length n.
    Extra space: O(n).

```
