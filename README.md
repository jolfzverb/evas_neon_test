evas-neon-test
==============

Set of tests to check correctness and performance of my NEON implementations of evas procedures.

How it is used
--------------

Copy test folder, you are interested in, to arm/arm64 buildroot or device, that have gcc, binutils and make installed, enter that folder and type

make; make check

This is not guaranteed to work, but this is how I'm using it.
There is also script build.sh, which I use to build several tests in several buildroots (arm and arm64).
