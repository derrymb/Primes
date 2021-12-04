/*! \mainpage Prime Pairs Concurrency
    \author Derry Brennan 
    \date 11/02/2021
    \copyright This code is covered by the GNU General Public License v3.0
    \name Prime Pairs

    Using C++ and OpenMP to have a program calculate the prime numbers up until N and then find the prime pairs out of those
    Prime numbers, a prime pair is two prime numbers that are exactly 2 different from each other, e.g 3&5 or 5&7
    The calculations will be preformed concurrently using openmp to spin up threads and preak the computations up into chunks
    of the appropriate size for the number of threads. The program is timed to check the scalability of it as both the amount
    of numbers being calculated and the amount of threads preforming these calculations increase
*/
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <omp.h>
using namespace std;
/*! Gloabal vector used to store the prime numbers*/
vector<int> primes;     
/*! Gloabal vector used to store the prime pairs*/
vector<int> primepairs;  

/*! \fn void calculatePrime(int n)
    \brief this function will take in a number n and calculate the primes up until that number and add them to the global vector primes
    \param n the number entered by the user, used as the upper limit of the calculation of prime numbers
    
    OpenMP parrallel for is used, we use dynamic scheduling to allow the cpu to assign tasks to 
    threads dynamically, giving faster threads more work and slower threads less work. OpenMp will the split up the for loop into 
    tasks and have the threads preform it in parallel. The inital for loop goes from 2 the smallest prime up until n.
    inside we have a boolean not_prime, set to an intial value of false. then the inner for  loop which is not run concurrently as 
    openmp does not allow for the break statement to be used inside of threaded for loops and as this for loop will terminate once
    a modulo operation equals 0 the speed up benefit of making this concurrent was not deemed to be necessary.
    if a prime is found it gets pushed to the global vector primes. The openmp critical annotation is used when pushing values 
    to the vector to avoid race conditions.

*/
void calculatePrime(int n)
{
    #pragma omp parallel for schedule(dynamic) //num_threads(2048) 
    for(int i = 2; i <= n; i++)
    {
        bool not_prime = false;
        for (int j = 2; j < i; j++)
        {
            if(i%j == 0)
            {
                not_prime = true;
                break;
            }
        }
        if (!not_prime)
        {
            #pragma omp critical
            primes.push_back(i);
        }
        else if(i==2)
        {
            #pragma omp critical
            primes.push_back(i);
        }
        
    }
}
/*! \fn void findPrimePairs()
    \brief This function preforms a check on the global vertor primes and looks for prime pairs within it
    
    OpenMP parrallel for is used, and default static scheduling is used as the task here is not intensive. 
    the for loop runs from 0 to the length of the primes vector and checks if a prime +2 is equal in value to its right most neighbour
    if they are both primes are added to the global primepair vector. The openmp critical annotation is used when pushing values 
    to the vector to avoid race cconditions. 
*/
void findPrimePairs()
{
    for (int i = 0; i < primes.size() -1; i++)
    {
        if(primes[i]+2 == primes[i+1])
        {
            {
                primepairs.push_back(primes[i]);
                primepairs.push_back(primes[i+1]);
            }
        }
    }
}
/*! \fn void printPairs()
    \brief Function to have the vector primepairs out put onto the console
    
    No need to do this in parallel as the output would be all over the place with each thread doing their own thing, so it is done sequintally.
    Some flurishes were added to pretty up the printing, but nothing of consequence. 
*/
void printPairs()
{
    std::cout << "( ";
    for (int j = 0; j < primepairs.size(); j++)
    {
        if(j%2 == 0 && j != 0)
        {
            std::cout << ")"<< endl << "( ";
        }
        std::cout << primepairs[j] << " ";
    }
    std::cout << ")"<< endl;
}
/*! \fn int main(void)
    \brief The ever famous main function that runs our driver to show off primes and OpenMP 
    
    Take in a number from the user, start the timer using chrono. call the calculatePrime(number) function,
    sort the vector primes as the threads will have put in the primes out of order.
    call find primepairs(), sort primepairs once they have been found for the same 
    reason as they will have been placed in the vector out of order.
    Then call printPairs() and end the timer and calculate the total duration of operations.
    and the some last print outs displaying the total time, the total prime up to N and the total number of prime pairs
*/
int main(void)
{
    int number = 1000000;
    //cout << "Enter a number to calculate the Prime Pairs up until: \n";
    //cin >> number;
    auto startTime = std::chrono::high_resolution_clock::now();
    calculatePrime(number);
    sort(primes.begin(), primes.end());
    findPrimePairs();
    sort(primepairs.begin(), primepairs.end());
    printPairs();
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << std::endl;
    std::cout << "Parallel execution for " << number << " numbers was : " << duration << " milliseconds." << endl;
    std::cout << "Total Prime numbers from 0 to " << number << " = " << primes.size() << endl;
    std::cout << "Total Prime Pairs from 0 to " << number << " = " << primepairs.size()/2 << endl;
}