#pragma once
#include <vector>
#include <iterator>
#include <string>
#include <iostream>


const unsigned int  BASE = 10000;
const unsigned int RAZRYAD = 4;

class BigInt {
public:

	std::vector< int > data;

	void mul10();
	void div10();


	BigInt();
    ~BigInt();
	BigInt(unsigned long x);
	BigInt(const BigInt &x);
	BigInt(std::string x);

	friend std::ostream &operator << (std::ostream &os, const BigInt &num);
	friend std::istream &operator >> (std::istream &is, BigInt &num);
	friend BigInt operator + (const BigInt &a, const BigInt &b);
	friend BigInt operator - (const BigInt &a, const BigInt &b);
	friend BigInt operator * (const BigInt &a, const BigInt &b);
	friend BigInt operator / (BigInt a, BigInt b);
	friend BigInt operator % (BigInt a, BigInt b);

	BigInt& operator=(const BigInt &x);

	friend BigInt power(const BigInt &a, const BigInt &b);
	friend BigInt fast_power(BigInt &num, BigInt &power, BigInt &modulus);
	friend BigInt modul_mult(BigInt &a, BigInt &b, BigInt &modul);

	friend int cmp(const BigInt &a, const BigInt &b);
	friend bool operator < (const BigInt &a, const BigInt &b);
	friend bool operator > (const BigInt &a, const BigInt &b);
	friend bool operator <= (const BigInt &a, const BigInt &b);
	friend bool operator >= (const BigInt &a, const BigInt &b);
	friend bool operator == (const BigInt &a, const BigInt &b);
	friend bool operator != (const BigInt &a, const BigInt &b);
};


const BigInt one(1);
const BigInt two(2);
const BigInt zero(0);

class SBigInt
{
public:
	SBigInt();
	~SBigInt();

	SBigInt(const SBigInt &x);


	friend SBigInt operator + (const SBigInt &a, const SBigInt &b);
	friend SBigInt operator - (const SBigInt &a, const SBigInt &b);
	friend SBigInt operator * (const SBigInt &a, const SBigInt &b);
	friend SBigInt operator / (SBigInt a, SBigInt b);
	friend SBigInt operator % (SBigInt a, SBigInt b);

	SBigInt& operator=(const SBigInt &x);

	BigInt data;
	bool sign;
};
