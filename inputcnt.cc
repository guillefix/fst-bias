#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

int main (int argc, char** argv) {
  // std::cout << "hello"<< std::endl;
  int N = atoi(argv[1]);
  std::map<std::string, int> inputcnt;
  ofstream myfile;
  for( int i = 0; i < N; i = i + 1 )
   {
     inputcnt.clear();
    //  std::cout << "lol"<< std::endl;
     std::ifstream infile("strout/" + std::to_string(i));
     std::string line;
     while (std::getline(infile, line))
     {
        //  std::cout << line << std::endl;
        std::stringstream linestream(line);
         std::string data;
         std::string output;
        //  std::string val2;
         std::getline(linestream, data, '\t');
         linestream >> output;
        // std::cout << data << std::endl;
        if (data != "") {inputcnt[output]++;}
     }
     infile.close();
     myfile.open ("inputcnts/" + std::to_string(i));
    //  std::cout << inputcnt.size() << std::endl;
     typedef std::map<std::string, int>::iterator it_type;
      for(it_type iterator = inputcnt.begin(); iterator != inputcnt.end(); ++iterator)
      {
          // iterator->first = key
          // iterator->second = value
          // Repeat if you also want to iterate through the second map.
          // std::cout << iterator->first + "\t" << iterator->second << std::endl;
          myfile << iterator->first + "\t" + std::to_string(iterator->second) + "\n";
          if (iterator->second > 10) {std::cout << iterator->first + "\t" + std::to_string(iterator->second)+"\n";}
      }
     myfile.close();
   }
}
