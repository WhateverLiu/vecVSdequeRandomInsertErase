// [[Rcpp::plugins(cpp17)]]
#include <Rcpp.h>
using namespace Rcpp;
#include "h/MiniPCG.hpp"
#include "h/tiktok.hpp"


template <typename C>
double testContainer(int seed, int size)
{
  C x;
  Charlie::MiniPCG rng(seed);
  auto U = std::uniform_real_distribution<float>(0, 1);
  for (int i = 0; i < size; ++i)
  {
    int xsize = x.size();
    if (xsize == 0) x.emplace_back(U(rng));
    else
    { 
      auto it = rng() % xsize + x.begin();  
      if (U(rng) < 1.0/3) x.erase(it);
      else x.insert(it, U(rng));
    } 
  }
  return std::accumulate(x.begin(), x.end(), 0.0);
}




// [[Rcpp::export]]
NumericVector testTime(int seed, int size) 
{
  Charlie::tiktok<std::chrono::microseconds> timer;
  timer.tik();
  double vecRst = testContainer<std::vector<double>> (seed, size);
  auto vectime = timer.tok();
  
  
  // Rcout << "sizeof(std::deque<double>) = " << sizeof(std::deque<double>) << "\n";
  // Rcout << "sizeof(std::deque<int>) = " << sizeof(std::deque<double>) << "\n";
  // Rcout << "sizeof(std::deque<float>) = " << sizeof(std::deque<double>) << "\n";
  
  
  timer.tik();
  double deqRst = testContainer<std::deque<double>> (seed, size);
  auto deqtime = timer.tok();
  
  
  timer.tik();
  vecRst += testContainer<std::vector<double>> (seed + 1, size);
  vectime += timer.tok();
  
  
  timer.tik();
  deqRst += testContainer<std::deque<double>>  (seed + 1, size);
  deqtime += timer.tok();
  
  
  NumericVector rst(2);
  rst[0] = vectime;
  rst[1] = deqtime;
  
  
  return rst;
}
















