#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

int main (int argc, char** argv) {
  // std::cout << "hello"<< std::endl;
  int N = atoi(argv[1]); //Number of files
  int n = atoi(argv[2]); //input string size
  map<string, pair<int, int>> genrob;
  ofstream myfile;
  for( int i = 0; i < N; i = i + 1 )
   {
     genrob.clear();
     ifstream infile("neistrout/" + to_string(i));
     string line;
     int j = 0;
     string parentpheno;
     while (std::getline(infile, line))
     {
       vector<string> tokens = split(line, '\t');
       if (tokens.size() == 0) {continue;}
       string geno = tokens[0];
       string pheno = tokens[1];
       j = j % n;
      //  cout << to_string(j);
       if (j == 0) {
         if (genrob.find(pheno) == genrob.end()) {genrob[pheno] = make_pair(0,0);}
         parentpheno = pheno;
         ++genrob[parentpheno].second;
       } else {
         cout << "test";
         cout << parentpheno;
         if (pheno == parentpheno) {++genrob[parentpheno].first;}
       }
       ++j;
     }
     infile.close();
     myfile.open ("genrobs/" + to_string(i));
    //  std::cout << inputcnt.size() << std::endl;
     typedef map<string, pair<int, int>>::iterator it_type;
      for(it_type iterator = genrob.begin(); iterator != genrob.end(); ++iterator)
      {
          // iterator->first = key
          // iterator->second = value
          // Repeat if you also want to iterate through the second map.
          // std::cout << iterator->first + "\t" << iterator->second << std::endl;
          pair<int, int> phenopair = iterator->second;
          string pheno = iterator->first;
          myfile << pheno + "\t" + to_string((double)phenopair.first/(double)(phenopair.second*n)) + "\n";
          // if (iterator->second > 10) {std::cout << iterator->first + "\t" + std::to_string(iterator->second)+"\n";}
      }
     myfile.close();
   }
}
