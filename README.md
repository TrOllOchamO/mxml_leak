# mxml leak
This repo is a quick and dirty way to reproduce a memory leak I encountered on my LTS Ubuntu 24.04.
I suspect the leak not to be caused directly by mxml but instead because of a cmake miss configuration.
The version of mxml used in this example is the one from this [fork](https://github.com/BarronKane/mxml/tree/cmake), 
from [this PR](https://github.com/michaelrsweet/mxml/pull/330). I've used it for simplicitys sake but i've faced the
issue on my side with my own cmake modified version of mxml 4.0.4.

Running the main with [valgrind](https://valgrind.org/) it shows the leak of a global memory allocation.
```
==2400600== HEAP SUMMARY:
==2400600==     in use at exit: 24 bytes in 1 blocks
==2400600==   total heap usage: 44 allocs, 43 frees, 6,532 bytes allocated
==2400600==
==2400600== 24 bytes in 1 blocks are still reachable in loss record 1 of 1
==2400600==    at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==2400600==    by 0x10F9A3: _mxml_global (mxml-private.c:173)
==2400600==    by 0x10F871: _mxml_strcopy (mxml-private.c:89)
==2400600==    by 0x10E8F5: mxmlNewDirective (mxml-node.c:470)
==2400600==    by 0x10B2FF: mxml_load_data (mxml-file.c:1163)
==2400600==    by 0x109734: mxmlLoadFilename (mxml-file.c:158)
==2400600==    by 0x1095AE: main (main.c:8)
==2400600==
==2400600== LEAK SUMMARY:
==2400600==    definitely lost: 0 bytes in 0 blocks
==2400600==    indirectly lost: 0 bytes in 0 blocks
==2400600==      possibly lost: 0 bytes in 0 blocks
==2400600==    still reachable: 24 bytes in 1 blocks
==2400600==         suppressed: 0 bytes in 0 blocks
==2400600==
==2400600== For lists of detected and suppressed errors, rerun with: -s
==2400600== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
