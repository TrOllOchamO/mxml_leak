# mxml leak
This repo is a quick and dirty way to reproduce a memory leak in mxml I encountered on my LTS Ubuntu 24.04 and
covered in [this issue](https://github.com/michaelrsweet/mxml/issues/341).
I first suspected the leak was caused by a miss configuration of the cmake used to compile the library,
that is why the version of mxml used in this example is the one from this [fork](https://github.com/BarronKane/mxml/tree/cmake), 
from [this PR](https://github.com/michaelrsweet/mxml/pull/330). It turned ou that the leak was in reality caused by a miss use
of the pthread API. 

The last version of this repo include a proposition of fix, previously, running
the main with [valgrind](https://valgrind.org/) was showing the leak of a global memory allocation
below :
```
==2518462== HEAP SUMMARY:
==2518462==     in use at exit: 24 bytes in 1 blocks
==2518462==   total heap usage: 44 allocs, 43 frees, 6,532 bytes allocated
==2518462==
==2518462== 24 bytes in 1 blocks are still reachable in loss record 1 of 1
==2518462==    at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==2518462==    by 0x10F9F2: _mxml_global (mxml-private.c:173)
==2518462==    by 0x10F8C0: _mxml_strcopy (mxml-private.c:89)
==2518462==    by 0x10E944: mxmlNewDirective (mxml-node.c:470)
==2518462==    by 0x10B34E: mxml_load_data (mxml-file.c:1163)
==2518462==    by 0x109783: mxmlLoadFilename (mxml-file.c:158)
==2518462==    by 0x1095CE: work (main.c:9)
==2518462==    by 0x109654: main (main.c:24)
==2518462==
==2518462== LEAK SUMMARY:
==2518462==    definitely lost: 0 bytes in 0 blocks
==2518462==    indirectly lost: 0 bytes in 0 blocks
==2518462==      possibly lost: 0 bytes in 0 blocks
==2518462==    still reachable: 24 bytes in 1 blocks
==2518462==         suppressed: 0 bytes in 0 blocks
==2518462==
==2518462== For lists of detected and suppressed errors, rerun with: -s
==2518462== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
The fix works when the program compile mxml statically. The fix should also work
when the library is loaded dynamically by linking mxml at compile time since
the library will be loaded before calling the main (so the id of the thread stored 
in `_mxml_loading_thread_id` will successfully be the main thread id (not tested)).
The fix should work when loading the library with [`dlopen`](https://man7.org/linux/man-pages/man3/dlopen.3.html)
in the main thread (not tested). But the leak should still happen when the library
is loaded with [`dlopen`](https://man7.org/linux/man-pages/man3/dlopen.3.html) outside of the
main thread (when [`dlopen`](https://man7.org/linux/man-pages/man3/dlopen.3.html) is caled in a pthread thread).
