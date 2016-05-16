#include <cstdio>
#include "hfst/HfstTransducer.h"
#include <hfst/HfstOutputStream.h>

using namespace hfst;

int main()
{
  HfstTransducer tr1("foo", "bar", FOMA_TYPE);
  HfstTransducer tr2("bar", "baz", FOMA_TYPE);
  tr1.compose(tr2);
  tr1.write_in_att_format(stdout);

  HfstOutputStream out("testfile", FOMA_TYPE);
  out << tr1;
  out.close();

  // tr1.lookup("foo");
  // ImplementationType type = SFST_TYPE;
  // HfstTransducer tr1("a", "b", type);
  // tr1.repeat_star();
  // HfstTransducer tr2("c", "d", type);
  // tr2.repeat_star();
  // tr1.concatenate(tr2).minimize();
  // HfstTwoLevelPaths results;
  // int MAX_NUM = -1;
  // int CYCLES = 1;
  // tr1.extract_paths(results, MAX_NUM, CYCLES);
  // for (HfstTwoLevelPaths::const_iterator it = results.begin();
  //        it != results.end(); it++)
  //     {
  //       std::string istring;
  //       std::string ostring;
  //
  //       for (StringPairVector::const_iterator IT = it->second.begin();
  //            IT != it->second.end(); IT++)
  //         {
  //           istring.append(IT->first);
  //           ostring.append(IT->second);
  //         }
  //       // Print input and output strings of each path
  //       std::cerr << istring << ":" << ostring;
  //       // and optionally the weight of the path.
  //       //std::cerr << "\t" << it->first;
  //       std::cerr << std::endl;
  //     }
}
