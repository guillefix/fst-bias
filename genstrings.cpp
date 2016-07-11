#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <bitset>
#include <random>
#include <string>
#include <iostream>
#include <boost/random/uniform_int.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <time.h>
#include <boost/random/variate_generator.hpp>

using namespace std;

typedef boost::uniform_int<> NumberDistribution;
typedef boost::mt19937 RandomNumberGenerator;
typedef boost::variate_generator<RandomNumberGenerator&,NumberDistribution> Generator;

// boost::random::mt19937 rng;
// boost::random::uniform_int_distribution<> dist(0,1);
// mt19937 mt(1); //declare random generator engine as global variable..
// uniform_int_distribution<int> dist(0,1); //declare random generator engine as global variable..

string rand_bits(const int size, const int ki, RandomNumberGenerator rng,   Generator dist) {
  string bits="";
  for (int i = 0; i < size; i++) {
    bits.append(to_string(dist()));
  }
  return bits;
}

int main(int argc, char const *argv[]) {
  int n = atoi(argv[1]); //input string size
  int ki = atoi(argv[2]); //alphabet size
  int Ni = atoi(argv[3]); //number of input strings generated
  int N = atoi(argv[4]); //number of files generated
  int nei = 0;
  if (argc == 6) {
    nei = atoi(argv[5]); //whether you create neighbours or not
  }
  // random_device rd; //random seed
  // mt19937 mt(rd()); //random generator engine
  // uniform_int_distribution<int> dist(0,ki-1); //uniform distribution over ki integers. ki should be < 10 ..
  NumberDistribution intdist(0,ki-1);
  RandomNumberGenerator rng;
  Generator dist(rng, intdist);
  rng.seed(time(0) + getpid());
  for (int i = 0; i < N; i++) {
    ofstream outfile;
    string folder = "str/";
    if (nei == 1) {
      folder = "strnei/";
    }
    outfile.open(folder+to_string(i)); //create and open file
    for (int j = 0; j < Ni; j++) { //write Ni random strings to file
      string inputstr = rand_bits(n, ki, rng, dist);
      outfile << inputstr << '\n';
      if (nei == 1) {
        for (size_t i = 0; i < inputstr.length(); i++) {
          string neistr = inputstr;
          string newbit = "1";
          if (inputstr.at(i) == '1') {
            newbit = "0";
          }
          neistr.replace(i,1,newbit);
          outfile << neistr << '\n';
        }
      }
    }
  }
  return 0;
}
