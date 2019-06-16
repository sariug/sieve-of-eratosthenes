# Sieve Of Eratosthenes

In mathematics, the Sieve of Eratosthenes is a simple, ancient algorithm for finding all prime numbers up to any given limit. 
[Wikipedia](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)

Here a simple code with MPI is written. 
Passing the maximum number as command line is necessary. 
### Build
```
ccmake . 
```
```
make
```
#### Example usage
```
mpirun -np 4 ./sieve_of_eratosthenes 100000
```
#### Example output 
```
Number entered is : 100000
Domain 0 has the size of 25000
Square Root N : 316
Domain 1 has the size of 25000
Domain 2 has the size of 25000
Domain 3 has the size of 25000
Results: 
    Global minimum =317
    Iteration number = 65
    Global maximum =99991
Elapsed time is 0.003232 s.
```
