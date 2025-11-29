TWO-MEDIANS-FAST(X)
    if length(X) < 2
        error "need at least two numbers"

    sort X in ascending order
    n = length(X)

    # build prefix sums
    prefix[0] = X[0]
    for i = 1 to n - 1
        prefix[i] = prefix[i - 1] + X[i]

    bestCost = infinity
    bestK = 1

    # helper to compute L1 cost of segment [L..R]
    SEGMENT-COST(L, R):
        m = floor((L + R) / 2)
        med = X[m]

        if L == 0
            sumLeft = prefix[m]
        else
            sumLeft = prefix[m] - prefix[L - 1]

        sumRight = prefix[R] - prefix[m]

        leftCount  = m - L + 1
        rightCount = R - m

        costLeft  = leftCount * med - sumLeft
        costRight = sumRight - rightCount * med

        return costLeft + costRight

    # try each possible split
    for k = 1 to n - 1
        costL = SEGMENT-COST(0, k - 1)
        costR = SEGMENT-COST(k, n - 1)
        total = costL + costR

        if total < bestCost or (total == bestCost and k < bestK)
            bestCost = total
            bestK = k

    # bestCost is the optimal 2-medians solution value
    # bestK is the size of the cluster containing the smallest value

Time complexity:
    Sorting takes O(n log n).
    Building prefix sums is O(n).
    The loop over k runs O(n) times and each SEGMENT-COST call is O(1),
    so that part is O(n).
    Overall time: O(n log n).

Space complexity:
    We store the array X and a prefix array of length n.
    Extra space: O(n).

