#ifndef KEYS_H
#define KEYS_H
#include "bigint.h"
#include<algorithm>
#include <string>
#include <time.h>
const unsigned int LENGTH = 12;
const unsigned  int PRIME_ACCURACY = 5; //Rabin-Miller test accuracy

class Keys
{
public:
	Keys();
	~Keys();
	BigInt n, e, d;

private:
	void Randomiser(BigInt &num, int Didgits);
	void PrimeGenerator(BigInt &num);
	bool IsPrime(BigInt &num);
	void RangeRandomiser(BigInt &num, const BigInt &top);
	BigInt euclid(const BigInt &e,const BigInt &modul);
};

#endif // KEYS_H
