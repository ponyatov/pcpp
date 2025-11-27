# Neural Code Comprehension

The goal of the Neural Code Comprehension (NCC) system is
to extract code semantics using a fusion of programmatic structural representations in addition to
ML-based modeling [2]. NCC introduces a novel structure called the conteXtual flow graph ([[XFG]])
to extract semantic meaning through identified data dependencies. The XFG, however, is limited to
languages supported by low level virtual machine intermediate representations ([[LLVM-IR]]) for which
it is lowered to. Moreover, as the XFG is principally grounded to lower-level syntactic representations,
its structure may have challenges in extracting the underlying semantic meaning of code.