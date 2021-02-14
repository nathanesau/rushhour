# RushHour Solver

C++, Python and Rust implementations of RushHour solver. Uses A* algorithm.

* jams: contains test cases for the solvers.
* [cpp](cpp/README.md): contains C++ implementation of solver.
* [python](python/README.md): contains Python implementation of solver.
* [rust](rust/README.md): contains Rust implementation of solver.

## Runtime Comparison

The C++ solver is the fastest out of the three versions of the solver.

### C++

Total: 41.572774 seconds.

```bash
[1] search count: 11587 (97553 ms)
[2] search count: 33503 (920993 ms)
[3] search count: 7814 (56069 ms)
[4] search count: 3491 (21607 ms)
[5] search count: 24135 (482325 ms)
[6] search count: 16980 (283643 ms)
[7] search count: 61014 (2204841 ms)
[8] search count: 6470 (90286 ms)
[9] search count: 5913 (71611 ms)
[10] search count: 16197 (260467 ms)
[11] search count: 6895 (50547 ms)
[12] search count: 11686 (103831 ms)
[13] search count: 75397 (5164445 ms)
[14] search count: 121252 (11428597 ms)
[15] search count: 3188 (39917 ms)
[16] search count: 23095 (527619 ms)
[17] search count: 19682 (310663 ms)
[18] search count: 13923 (170341 ms)
[19] search count: 3589 (41118 ms)
[20] search count: 15314 (231643 ms)
[21] search count: 1697 (13087 ms)
[22] search count: 32603 (881978 ms)
[23] search count: 20431 (374592 ms)
[24] search count: 45552 (1289630 ms)
[25] search count: 82852 (5279277 ms)
[26] search count: 40089 (1508133 ms)
[27] search count: 21362 (401149 ms)
[28] search count: 16727 (301042 ms)
[29] search count: 38335 (1202183 ms)
[30] search count: 8633 (88789 ms)
[31] search count: 33130 (1021219 ms)
[32] search count: 3292 (30677 ms)
[33] search count: 36603 (1497901 ms)
[34] search count: 37556 (1104451 ms)
[35] search count: 34035 (1090497 ms)
[36] search count: 22229 (442613 ms)
[37] search count: 15270 (307541 ms)
[38] search count: 28612 (668606 ms)
[39] search count: 24877 (684687 ms)
[40] search count: 24467 (574323 ms)
total: (41572774 ms)
```

### Python

Total: 359.4311 seconds.

```bash
finished solve for jam 1 (elapsed = 0:00:00.920000, search_count = 11587
finished solve for jam 2 (elapsed = 0:00:08.125838, search_count = 32850
finished solve for jam 3 (elapsed = 0:00:00.413685, search_count = 7856
finished solve for jam 4 (elapsed = 0:00:00.127007, search_count = 3427
finished solve for jam 5 (elapsed = 0:00:03.745302, search_count = 24220
finished solve for jam 6 (elapsed = 0:00:01.927614, search_count = 16927
finished solve for jam 7 (elapsed = 0:00:19.109896, search_count = 61026
finished solve for jam 8 (elapsed = 0:00:00.597996, search_count = 6470
finished solve for jam 9 (elapsed = 0:00:00.425014, search_count = 5928
finished solve for jam 10 (elapsed = 0:00:02.139001, search_count = 15891
finished solve for jam 11 (elapsed = 0:00:00.388999, search_count = 6859
finished solve for jam 12 (elapsed = 0:00:01.037000, search_count = 11686
finished solve for jam 13 (elapsed = 0:00:38.607385, search_count = 72340
finished solve for jam 14 (elapsed = 0:01:59.787784, search_count = 112095
finished solve for jam 15 (elapsed = 0:00:00.186012, search_count = 3188
finished solve for jam 16 (elapsed = 0:00:03.512013, search_count = 22853
finished solve for jam 17 (elapsed = 0:00:02.599997, search_count = 19809
finished solve for jam 18 (elapsed = 0:00:01.514003, search_count = 13916
finished solve for jam 19 (elapsed = 0:00:00.156012, search_count = 3589
finished solve for jam 20 (elapsed = 0:00:01.688984, search_count = 12623
finished solve for jam 21 (elapsed = 0:00:00.047999, search_count = 1697
finished solve for jam 22 (elapsed = 0:00:07.391000, search_count = 32204
finished solve for jam 23 (elapsed = 0:00:03.114997, search_count = 19901
finished solve for jam 24 (elapsed = 0:00:11.387999, search_count = 46321
finished solve for jam 25 (elapsed = 0:00:47.222471, search_count = 81562
finished solve for jam 26 (elapsed = 0:00:11.662998, search_count = 40089
finished solve for jam 27 (elapsed = 0:00:03.489997, search_count = 21351
finished solve for jam 28 (elapsed = 0:00:02.378084, search_count = 16767
finished solve for jam 29 (elapsed = 0:00:09.390998, search_count = 38396
finished solve for jam 30 (elapsed = 0:00:00.732001, search_count = 8610
finished solve for jam 31 (elapsed = 0:00:07.832997, search_count = 33193
finished solve for jam 32 (elapsed = 0:00:00.181015, search_count = 3292
finished solve for jam 33 (elapsed = 0:00:08.625361, search_count = 36586
finished solve for jam 34 (elapsed = 0:00:09.428000, search_count = 37431
finished solve for jam 35 (elapsed = 0:00:07.986791, search_count = 34141
finished solve for jam 36 (elapsed = 0:00:03.755999, search_count = 22661
finished solve for jam 37 (elapsed = 0:00:02.174012, search_count = 15270
finished solve for jam 38 (elapsed = 0:00:05.813989, search_count = 28034
finished solve for jam 39 (elapsed = 0:00:05.022875, search_count = 24792
finished solve for jam 40 (elapsed = 0:00:04.781983, search_count = 24467
```

### Rust

Total: 110 seconds.

```bash
[1] search_count: 11587
[2] search_count: 32529
[3] search_count: 7814
[4] search_count: 3491
[5] search_count: 24639
[6] search_count: 16980
[7] search_count: 61014
[8] search_count: 6470
[9] search_count: 5913
[10] search_count: 16197
[11] search_count: 6895
[12] search_count: 11686
[13] search_count: 75397
[14] search_count: 121979
[15] search_count: 3188
[16] search_count: 23095
[17] search_count: 19682
[18] search_count: 13923
[19] search_count: 3589
[20] search_count: 14761
[21] search_count: 1697
[22] search_count: 32603
[23] search_count: 19479
[24] search_count: 45544
[25] search_count: 82852
[26] search_count: 40089
[27] search_count: 21351
[28] search_count: 16727
[29] search_count: 38335
[30] search_count: 8633
[31] search_count: 33193
[32] search_count: 3292
[33] search_count: 36603
[34] search_count: 37544
[35] search_count: 34035
[36] search_count: 22229
[37] search_count: 15270
[38] search_count: 28612
[39] search_count: 24877
[40] search_count: 24467
```

## References

Inspirations for solve algorithm:

* Java Rush Hour Solve Algorithm: https://github.com/saschazar21/rushhour

* A* Search Algorithm: https://en.wikipedia.org/wiki/A*_search_algorithm

* Sudoku Solver: https://github.com/nathanesau/sudoku_solver