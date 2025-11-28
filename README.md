## pseudocode
```pseudo
TWO-MEDIANS(X)
    if length(X) < 2
        error "need at least two numbers"
    sort X in ascending order
    bestCost = infinity
    bestK = 1
    n = length(X)

    for k = 1 to n - 1	// try each possible split
        mL = floor((1 + k) / 2)
        medL = X[mL]	// left median
        mH = floor((k + 1 + n) / 2)
        medH = X[mH]	// right median

        costL = 0
        for i = 1 to k	// total distance to left median
            costL = costL + abs(X[i] - medL)

        costH = 0
        for i = k + 1 to n	// total distance to right median
            costH = costH + abs(X[i] - medH)

        total = costL + costH
        if total < bestCost or (total == bestCost and k < bestK)
            bestCost = total
            bestK = k

    return bestK
```

## Complexity:
Time: sort O(n log n) + cost loops O(n^2) = O(n^2)
Space: O(n) (store input + sorted copy)

