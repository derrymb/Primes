/*! \mainpage Prime Pairs Concurrency
    \author Derry Brennan 
    \date 11/02/2021
    \copyright This code is covered by the GNU General Public License v3.0
    \name Prime Pairs

*/
// C++ program to prlong long primes smaller than n using 
// Sieve of Sundaram. 
#include <bits/stdc++.h> 
using namespace std; 

//long longs all prime numbers smaller 
void SieveOfSundaram(long long n) 
{ 
	// In general Sieve of Sundaram, produces primes smaller 
	// than (2*x + 2) for a number given number x. 
	// Since we want primes smaller than n, we reduce n to half 
	long long nNew = (n-1)/2; 

	// This array is used to separate numbers of the form i+j+2ij 
	// from others where 1 <= i <= j 
	bool *marked = new bool[nNew + 1]; 

	// Initialize all elements as not marked 
	memset(marked, false, sizeof(marked)); 

	// Main logic of Sundaram. Mark all numbers of the 
	// form i + j + 2ij as true where 1 <= i <= j 
	for (long long i=1; i<=nNew; i++) 
		for (long long j=i; (i + j + 2*i*j) <= nNew; j++) 
			marked[i + j + 2*i*j] = true; 

	// Since 2 is a prime number 
	// if (n > 2) 
	// 	cout << 2 << " "; 

	// Prlong long other primes. Remaining primes are of the form 
	// 2*i + 1 such that marked[i] is false. 
	// for (long long i=1; i<=nNew; i++) 
	// 	if (marked[i] == false) 
	// 		cout << 2*i + 1 << " "; 
    delete[] marked;
} 

// Driver program to test above 
int main(void) 
{ 
	long long n = 100000000L; 
	SieveOfSundaram(n); 
	return 0; 
} 
