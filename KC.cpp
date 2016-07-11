#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;
// #include <boost/lexical_cast.hpp>

double KC( char* s, int length )
{
    int n,c,l,i,k,k_max,stop;
    // double b;
    double complexity;

    n=length;
    c=1; l=1; i=0; k=1; k_max=1; stop=0;

    while (stop==0)
    {
        if ( s[i+k]!=s[l+k] )
        {
            if ( k>k_max )
                k_max=k;

            i=i+1;

            if ( i==l )
            {
                c=c+1;
                l=l+k_max;

                if ( l+1>n )
                    stop=1;
                else
                {
                    i=0;
                    k=1;
                    k_max=1;
                }
            }
            else
                k=1;
        }
        else
        {
            k=k+1;
            if ( l+k>n )
            {
                c=c+1;
                stop=1;
            }
        }
    }

    // b=n*log(2)/log(n);


/* a la Lempel and Ziv (IEEE trans inf theory it-22,75 (1976),
** h(n)=c(n)/b(n) where c(n) is the kolmogorov complexity
** and h(n) is a normalised measure of complexity. */

    /* complexity=1.0*c/b; */
    complexity=1.0*c;

    return complexity;
}

/* Below, there's a function in python: it needs to be translated to C++
   ( I haven't used the C++ implementation in a while ) */

double calc_KC( char* s) {
  int L = strlen(s);
  bool is_zeros=true, is_ones=true;
  char strrev[L];
  for (int i = 0; i < L; i++) {
    if (s[i] != '0') is_zeros=false;
    if (s[i] != '1') is_ones=false;
    strrev[i] = s[L-i];
  }
  if (is_zeros || is_ones) return log2(L);
  else return log2(L)*(KC(s, L)+KC(strrev,L))/2.0;
}

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
  int N = atoi(argv[1]);
  // printf("complexity: %f\n", calc_KC(argv[1]));
  printf("hi %d",1);

  for( int i = 0; i < N; i++)
   {
     ifstream infile;
     infile.open("inputcnts/" + to_string(i));
     ofstream outfile;
     outfile.open("comp/" + to_string(i));
     string line;
     while (getline (infile,line))
     {
        vector<string> tokens = split(line, '\t');
        string output = tokens[0];
        string cnt = tokens[1];
        char *cstr = new char[output.length() + 1];
        strcpy(cstr, output.c_str());
        char comp[50];
        snprintf(comp,sizeof(comp),"%f",calc_KC(cstr));
        outfile << comp << ' ' << cnt << '\n';
     }
     infile.close();
     outfile.close();
   }
   return 0;
}
