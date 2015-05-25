#include "keys.h"

using namespace std;

Keys::Keys()
{

	BigInt p, q, fi;
	PrimeGenerator(p);
	PrimeGenerator(q);
	n = p*q;
	fi = (p - one)*(q - one);  
    e = (BigInt)65537; //good choise but I can better))
	d = euclid(e, fi);

}

Keys::~Keys()
{

}



BigInt Keys::euclid(const BigInt& aa, const BigInt& bb) {
    SBigInt a(aa), b(bb), bcopy(bb), x2(one), x1(zero), y2(zero), y1(one);
    while (b.data != zero) {
        SBigInt q = a / b;
        SBigInt r = a - q*b;
        SBigInt x = x2 - q*x1;
        SBigInt y = y2 - q*y1;
        a = b;
        b = r;
        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
    }
    if (!x2.sign) x2 = x2 + bcopy;
    return x2.data;
}



void Keys::Randomiser(BigInt &num, int Digits){
	int supp = 0, temp;
	string str;
    int timemachine=time(NULL)%17;

	str.resize(Digits);
    for(int i=0; i<timemachine; i++)
    {
        rand();
    }
	while (supp < Digits)
	{
		temp = rand() % 10;
		str[supp] = '0' + temp;
		supp += 1;
	}
    random_shuffle(str.begin(),str.end());

	if (str[0] == '0')
		str[0] = '0' + rand() % 9 + 1;
	num = (BigInt)str;
	num = num + num;
	num = num - one;
}


void Keys::RangeRandomiser(BigInt &num, const BigInt &top){

	int Digit = (rand() % (top.data.size()*RAZRYAD - 1)) + 1;
	Randomiser(num, Digit);
}


bool Keys::IsPrime(BigInt &num){

	BigInt num_minus_one;
	num_minus_one = num - one;

	BigInt temp, trans, random, mod, supp;
	trans = num_minus_one;
	temp = num_minus_one%two;

    while (temp == zero)
	{
		trans = trans / two;
		temp = trans%two;
	}

	for (int i = 0; i < PRIME_ACCURACY; i++)
	{
		temp = trans;
		RangeRandomiser(random, num_minus_one);

		mod = fast_power(random, temp, num);

		while (temp != num_minus_one && mod != one && mod != num_minus_one)
		{
			mod = modul_mult(mod, mod, num);
			temp = temp*two;
		}
		supp = temp%two;
        if (mod != num_minus_one && supp == zero)
		{
			return false;
		}

	}
	return true;
}

void Keys::PrimeGenerator(BigInt &num){
	bool supp = false;
	while (!supp){
		Randomiser(num, LENGTH);
		supp = IsPrime(num);
	}
}
