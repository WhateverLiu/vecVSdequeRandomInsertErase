

Rcpp::sourceCpp('test.cpp', verbose = 1)
testTime(123, 1e5)
# 194789 269726 deque is only suitable for adding/erasing elements at the front
#   or back

