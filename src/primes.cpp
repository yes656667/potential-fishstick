#include "primes.h"

/*
*Just a prime checker, you know how this works.
* (this needs to check one at a time, in increments of 1)
*/

int64_t max = 1;
std::unordered_map<int64_t,bool> primes;
std::vector<int64_t> primeList;
bool isPrime(int64_t i)
{
	if(i <= max) return primes[i];
	max = i;
	for(const int &a : primeList)
	{
		if(i % a == 0)
		{
			return false;
		}
	}
	primes[i] = true;
	primeList.push_back(i);
	return true;
}