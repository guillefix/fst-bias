# fst-bias
Code for the exploration of bias for simplicity in the output of random finite state transducers

See more [in my TiddlyWiki](http://guillefix.me/cosmos.html#MMathPhys%20oral%20presentation)

After exploration using Python (in py-fst folder), we are looking for faster implementation in C++ (see cpp-fst folder)

##C++ implementation

Currently the best option seems to be the [HFST - Helsinki Finite-State Transducer Technology - C++ API](https://hfst.github.io/cplusplus/index.html)

### Installation instructions

as found [here](https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstDownloads#Installing_HFST_to_Linux_from_Ap). For *Linux* (for other options see [here](https://hfst.github.io/downloads/index.html))

1. Go to [Downloads page](http://apertium.projectjj.com/apt/nightly/pool/main/h/hfst/). You need the following files ``libhfst42``, ``hfst``, ``libhfst42-dev``. The version can be found with the command ``lsb_release -a``, and looking at the output of ``Codename``.

2. Install them. `` dpkg --install libhfst42_***.deb``
  ``dpkg --install libhfst-dev_***.deb``
  ``dpkg --install hfst_***.deb``

See also their code, and instructions for installing from source in [their GitHub](https://github.com/hfst/hfst) (doesn't work for me)

One can then see examples of using the library [here](https://hfst.github.io/cplusplus/QuickStart.html), and the main classes in the library [here](https://hfst.github.io/cplusplus/namespacehfst.html).

To see the result of running a word (in command-line), one can use [hfst-lookup](https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstLookUp), and this has worked for me!. The documentation seems to have an option to do this from the C++ code itself; however, I've not been able to make it work. Note to use the command-line one needs a FST binary file. These can be created from the C++ code as explained [here](https://hfst.github.io/cplusplus/classhfst_1_1HfstOutputStream.html#acc3adf89b52ddb96509536c2c6a8f758)

The current test c++ file where I'm trying these ideas is ``cpp-fst/fst_bias.cc``, which can be compiled using ``make``.

##Python implementation

Using [FAdo](http://fado.dcc.fc.up.pt/software/) [docs](http://www.dcc.fc.up.pt/~rvr/FAdoDoc/index.html))

##FST generation and lookup

Use `genfst.py` to generate random FSTs, it has arguments:

* `n`, number of states
* `ki`, size of input alphabet
* `ko`, size of output alphabet
* `N`, number of FSTs produced. Not yet implemented.

This prints the FST into AT&T format. To convert to HFST look-up-optimized binary format, use `hfst-txt2fst -f optimized-lookup-unweighted [input file] > [output file]`. Then one can use the HFST interactive lookup prompt, by typing `hfst-lookup [output file]`. **Note**: output states **are** taken into account, so that looking-up a string that doesn't end up in a final state, doesn't print the result..
