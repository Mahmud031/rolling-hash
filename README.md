# rolling-hash
Implementation of a rolling hash based file diff. It's only calculate the hash and find the match and mismatches. UTs are yet to be added.

Compilation:
    g++ -o rolling-hash Main.cpp RollingHash.cpp FileOperations.cpp

for tests,
    g++ -o rolling-hash-test TestRollingHash.cpp RollingHash.cpp FileOperations.cpp

