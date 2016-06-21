// #include <iostream>
#include <fst/fstlib.h>
// using namespace std;
using namespace fst;

int main ()
{
  // Reads in an input FST.
  StdVectorFst *input = StdVectorFst::Read("input.fst");

  // Reads in the transduction model.
  StdVectorFst *model = StdVectorFst::Read("model.fst");

  // The FSTs must be sorted along the dimensions they will be joined.
  // In fact, only one needs to be so sorted.
  // This could have instead been done for "model.fst" when it was created.
  ArcSort(input, StdOLabelCompare());
  ArcSort(model, StdILabelCompare());

  // Container for composition result.
  StdVectorFst result;

  // Creates the composed FST.
  Compose(*input, *model, &result);

  // Just keeps the output labels.
  Project(&result, PROJECT_OUTPUT);

  // Writes the result FST to a file.
  result.Write("result.fst");

//   // A vector FST is a general mutable FST
// StdVectorFst fst;
//
// // Adds state 0 to the initially empty FST and make it the start state.
// fst.AddState();   // 1st state will be state 0 (returned by AddState)
// fst.SetStart(0);  // arg is state ID
//
// // Adds two arcs exiting state 0.
// // Arc constructor args: ilabel, olabel, weight, dest state ID.
// fst.AddArc(0, StdArc(1, 1, 0.5, 1));  // 1st arg is src state ID
// fst.AddArc(0, StdArc(2, 2, 1.5, 1));
//
// // Adds state 1 and its arc.
// fst.AddState();
// fst.AddArc(1, StdArc(3, 3, 2.5, 2));
//
// // Adds state 2 and set its final weight.
// fst.AddState();
// fst.SetFinal(2, 3.5);
// // 1st arg is state ID, 2nd arg weight
// // We can save this FST to a file with:
// fst.Write("binary.fst");
  return 0;
}
