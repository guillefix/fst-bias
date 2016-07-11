#include <cstdio>
#include "hfst/HfstTransducer.h"
#include <hfst/implementations/optimized-lookup/transducer.h>
#include <hfst/implementations/optimized-lookup/convert.h>
#include <hfst/HfstOutputStream.h>

using namespace hfst;
// using namespace hfst_ol;

int main()
{
  HfstTransducer tr1("foo", "bar", FOMA_TYPE);
  HfstTransducer tr2("bar", "baz", FOMA_TYPE);
  tr1.compose(tr2);
  tr1.write_in_att_format(stdout);

  // HfstOutputStream out("testfile", FOMA_TYPE);
  // out << tr1;
  // out.close();

  ConvertTransducer(tr1)

  hfst::HfstOneLevelPaths* inputs = tr1.lookup("foo");
  // std::cout << inputs;
  // hfst::HfstOneLevelPaths inputs2 = *inputs;
  // for (hfst::HfstOneLevelPaths::iterator i = inputs2.begin(); i != inputs2.end(); i++) {
  //    std::pair<float, std::vector<std::__cxx11::basic_string<char> > > element = *i;
  // }



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
