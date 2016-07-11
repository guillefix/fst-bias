#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <regal/include/RandomDFAGenerator.hpp>
#include <regal/include/DFAAutomaton.hpp>
#include <regal/include/Alphabet.hpp>
#include <regal/include/BoltzmannSampler.hpp>
#include <cstring>

using namespace regal;

int main(int argc, char const *argv[]) {

  int n = atoi(argv[1]); //size of transducer
  int ki = atoi(argv[2]); //input alphabet size
  int ko = atoi(argv[3]); //output alphabet size
  int N = atoi(argv[4]); //number of files generated

  N=1;

  DFAAutomaton<int,char>*result; //Result DFA
  Alphabet<char> alpha; //Create an alphabet
  alpha.insert ('0'); alpha.insert ('1');
  RandomDFAGenerator<int,char,DFAAutomaton<int,char>> rg(n ,alpha, 1.0);
  for (int counter=0; counter<N; counter++) result=rg.random();

  // ofstream outfile;
  // outfile.open("test"); //create and open file
  // a::toDOT(outfile);

  return 0;
}
