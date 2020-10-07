# lincat

This folder contains a Singular code that can be used for approximating linear categories of partitions with given generators. The algorithm is described in [2].

## Usage

The actual code is contained in the file `lincat.sing`. The usage is illustrated in several jupyter notebooks, which refer to specific computations described in [2, Section 4]. Let us here point out two remarks.

First of all, the code uses some pre-computed information stored in the file `maps`. Namely those are so-to-say matrix entries of the categorical opeartions (see [2, Section 3.2]). Those are computed for all partitions up to length nine. If one wants to increase the length bound (`lmax` in the code by default set to eight), one has to recompute this file. This can be done using the C++ code `maps.cpp`, which has to be compiled together with `../words/word.cpp`.

Secondly, let us comment on how the partitions are actually represented in the Singular code since this may not be totally clear from the examples. Well, they are represented by the basis vectors `gen(i)`, where `i` is some natural number. More concretely, let us fix some length $k$. The we can represent all partitions of $k$ points by words over some letters a, b, c, d,... and for each partition choose the lexicographically smallest representation. Then order those partitions with respect to the lexicographical order and this gives the corresponding labels `i` for those partitions. All partitions (of length up to eight) lexicographically ordered are available in the file `wlist`, which can be used as kind of a dictionary when working with partitions. (When working with partitions of length $k<8$, just ignore the first $8-k$ letters in each row.)

## Acknowledgement

This work was done as a part of a PhD project of Daniel Gromada at Saarland University. It was supported by the collaborative research centre SFB-TRR 195 "Symbolic tools in mathematics and their Application".

## Authors

  * Daniel Gromada -- gromada@math.uni-sb.de

## References

  [1] D. Gromada: Compact matrix quantum groups and their representation categories.
      PhD thesis, Saarland University (2020). [doi:10.22028/D291-32389](http://dx.doi.org/10.22028/D291-32389).
  [2] D. Gromada, M. Weber: Generating linear categories of partitions.
      Preprint (2019). [arXiv:1904.00166](https://arxiv.org/abs/1904.00166).
