# EA Problem Report
### Contributors
* Duarte Dias 2018293526 duartedias@student.dei.uc.pt
* Maria Dias ---- -----

## Algorithm Description
Note : To Describe complexity, O(n) is considered to be one complete full pass in the matrix.

The Algorithm contains two main steps: 
* A preprocessing step, where cases that are inately correct or incorrect are verified. This step takes O(n);
```
// Assuming that GB is an n-by-n matrix that represents the gameBoard, sum() is a function that sums all values in k, and check() verifies if there there is only non-zero element in k
    Function preprocess(GB):
        sumGB <- sum(GB)
        if floor(lg(sumGB)):
            return false;
        if check(GB):
            return true;
```
The second step of this algorithm consists in a recursive function over the game board. It follows a DFS scheme, meaning that it searches in Depth first. This recursive step contains 3 base cases:
* When check() return true means that the board is valid, ie only has one single value remaining;
* When k = m means the the current level of recursion is equal to the max, since k starts in 0, means that when this condition is reached the max recursion depth is reached;
* When k >= best, means the current solution is already worse then best previously calculated, and therefore no further steps shoulld be taken;

If all the above cases fail, it means the current iteration may be a valid solution. To calculate this solution we need to calculate the state of the GameBoard for all for directions. As a speedup technique, only in some cases this is necessary, if in layer k there were no merges in an axis (UpDown or LeftRight Axis), in the next recursive step, k + 1, both operations in such axis would be the same as the ones in layer k. Example:

```
0. Initial State (k - 1)
0 0 0 
2 2 2
0 0 0

1. k-th Layer Transformations (k)
0 0 0  U  2 2 2
2 2 2 ->  0 0 0 
0 0 0     0 0 0

0 0 0  D  0 0 0
2 2 2 ->  0 0 0 
0 0 0     2 2 2

2. k+1-th Layer Transformation (Following branch with U transformation from k)
2 2 2  U  2 2 2
0 0 0 ->  0 0 0 
0 0 0     0 0 0

2 2 2  D  0 0 0
0 0 0 ->  0 0 0 
0 0 0     2 2 2

No merge example 
```
As we can see we obtain the same results in the k+1th layer as in the k-th layer.

It should also be noted that any slide operation can be done in O(2n), by doing one pass in the matrix to merge all the possible cells and another to shift the cells to the correct positions. The merge and swap counters used to perform the trick above are calculated inside this sliding operation in O(1) time;




Pseudo code:
```cpp
//Best is a global variable that yield the current best result found

Function solve(GB, k, m , validSides, validUpDown)
    val <- check(GB)
    if val = true then
        best <- max(best, k)
        return
    
    if k = m or k >= best then
        return

    m1 <- m2 <-m3 <- m4 <- 0
    s1 <- s2 <-s3 <- s4 <- 0
    if validSides is true then
        GB1 <- copy GB
        GB2 <- copy GB
        sl1deL(GB1, m1,s1)
        slideR(GB2, m2,s2)

        if m1 or s1 then
            solve(GB1, k+1, m, m1, 1)
        end if
        if m2 or s2 then
            solve(GB2, k+1, m, m2, 1)
        end if
    end if

    if validUpDown is true then
        GB3 <- copy GB
        GB4 <- copy GB
        slideU(GB3, m3,s3)
        slideD(GB4, m4,s4)

        if m3 or s3 then
            solve(GB3, k+1, m, m3, 1)
        end if
        if m4 or s4 then
            solve(GB4, k+1, m, m4, 1)
        end if
    end if

return
```

## Data Structures
    To solve this problem, the default implementation of vector was used.

```cpp
std::vector<std::vector<int>> Matrix;
```
Such data structure allows to perform random access in O(1). It also takes advantage of the caching effect of the system, making it much faster than a list (which uses random memory locations) when doing the sliding operations;

## Correctness
    Score: 200 Points;
    The problem 2048 is NP complete, which means it cannot be calculated in polynomial time, therefore all combinations must be tested. The backtracking approach lies on this premisse, testing all feasible solutions (ie making cuts in the certain branches where no better solution/ no solution could be found)
## Algorithm Analysis

### Memory
    Using Big-O notation, the memory complexity of each recursive step is O(4^n), because each step 4 copys of the matrix are created;
    The complexity of the base case is O(1);

### Time
    The time complexity of each recursive step is O(n):
    * O(n) for checking;
    * 4.O(n) for creating each copy of the matrix;
    * 8.O(n) for all the slide operations;
    Which Total 13.O(n) ~ O(n)
    
    

## References
* Algorithms, Jeff Erikson