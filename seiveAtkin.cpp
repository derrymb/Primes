/*! \mainpage Prime Pairs Concurrency
    \author Derry Brennan 
    \date 11/02/2021
    \copyright This code is covered by the GNU General Public License v3.0
    \name Prime Pairs
*/
// C++ program for implementation of Sieve of Atkin 
#include <bits/stdc++.h> 
#include <math.h>
using namespace std; 

void SieveOfAtkin(long long limit) 
{ 
	// Initialise the sieve array with false values 
	bool *sieve = new bool[limit]; 
	memset(sieve, false, sizeof(sieve));  

	/* Mark siev[n] is true if one 
	of the following is true: 
	a) n = (4*x*x)+(y*y) has odd number of 
	solutions, i.e., there exist 
	odd number of distinct pairs (x, y) 
	that satisfy the equation and 
		n % 12 = 1 or n % 12 = 5. 
	b) n = (3*x*x)+(y*y) has odd number of 
	solutions and n % 12 = 7 
	c) n = (3*x*x)-(y*y) has odd number of 
	solutions, x > y and n % 12 = 11 */
	for (long long x = 1; x * x < limit; ++x) { 
		for (long long y = 1; y * y < limit; ++y) { 
			
			// Main part of Sieve of Atkin 
			long long n = (4 * x * x) + (y * y); 
			if (n <= limit && (n % 12 == 1 || n % 12 == 5)) 
				sieve[n] ^= true; 

			n = (3 * x * x) + (y * y); 
			if (n <= limit && n % 12 == 7) 
				sieve[n] ^= true; 

			n = (3 * x * x) - (y * y); 
			if (x > y && n <= limit && n % 12 == 11) 
				sieve[n] ^= true; 
		} 
	} 

	// Mark all multiples of squares as non-prime 
    const unsigned long limit_sqrt = sqrt(limit);
	for (long long r = 5; r <= limit_sqrt; ++r) { 
		if (sieve[r]) { 
			for (long long i = r * r; i < limit; i += r * r) 
				sieve[i] = false; 
		} 
	} 
    delete[] sieve;
	// // Print primes using sieve[] 
	// for (int a = 5; a < limit; a++) 
	// 	if (sieve[a]) 
	// 		cout << a << " "; 
} 

// Driver program 
int main(void) 
{ 
	long long limit = 100000000L; 
	SieveOfAtkin(limit); 
	return 0; 
} 


// This code is contributed by nitin mittal 
