A brief after-action report of the homework:

The issues I ran into:
1. It takes time to read all the files in the source codes for sort to
figure out how the program works.
2. I had difficulty accessing the variables and finally came up with the idea
that we can use global variables for simplicity.
3. At first time I did not realize that I need to add -lpthread to the Makefile.

Conclusions:

From the make-log.txt, we get the following output:

time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m46.257s
user    0m46.251s
sys     0m0.003s

time ./srt 2-test.ppm >2-test.ppm.tmp

real    0m23.393s
user    0m46.497s
sys     0m0.003s

time ./srt 4-test.ppm >4-test.ppm.tmp

real    0m11.726s
user    0m46.357s
sys     0m0.002s

time ./srt 8-test.ppm >8-test.ppm.tmp

real    0m5.975s
user    0m46.380s
sys     0m0.001s

By inspection, we can find that the real time is approximately
the user time divided by the number of paralled threads.
Also, the real time decreases as the number of threads increases.
This verify the advantage of parallelism.
Thus, using 8 threads is fastest among the tested versions.

