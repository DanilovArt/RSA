#include "bigint.h"
#include <string>
#include <stack>
#include<stdlib.h>
using namespace std;

BigInt::BigInt() {
}
BigInt::~BigInt() {
    data.clear();
}

BigInt::BigInt(unsigned long x) {
	if (x == 0)
		data.push_back(x);
	else
	while (x) {
		data.push_back(x % BASE);
		x /= BASE;
	}
}

BigInt::BigInt(const BigInt &x) : data(x.data) {
}









int BigInt::toint(){
     if (data.size()>1)
         return 0;
     else{
         int result=data[0];
         if (data.size() == 1)
             result += data[1] * BASE;
         return result;
     }
 }

 QString biginttostr(BigInt number){

    QString result,trans;
    QString supp;
int razryad=number.data.size()-1;
    supp=QString::number(number.data[razryad], 10);
    result = supp;

    for (int i = razryad-1; i >= 0; i--){
        supp=QString::number(number.data[i],10);
        trans = supp;
        while (trans.length() < RAZRYAD)
            trans = "0" + trans;

        result += trans;
        trans.clear();
    }



    //result = number.znak + result;
    return result;
}










BigInt::BigInt(std::string x){
	data.resize(1);
	int size = x.size();
	int c = -1;
	for (int j = 0; j < size; j++){
		for (int i = c; i >= 0; i--){
			data[i + 1] = data[i + 1] + (data[i] * 10 / BASE);
			data[i] = (data[i] * 10) % BASE;
		}
		data[0] = data[0] + (x[j] - '0');
		if (data[c + 1]>0){
			c += 1;
			data.push_back(0);
		}
	}
	data.pop_back();
}

void BigInt::mul10() {
	if (!data.size())
		return;
	vector< int >::reverse_iterator i;
	*(data.end() - 1) *= 10;
	for (i = data.rbegin() + 1; i != data.rend(); i++) {
		*i *= 10;

		*(i - 1) += (*i) / BASE;
		*i %= BASE;
	}

	if (*(data.end() - 1) > BASE) {
		data.push_back(*(data.end() - 1) / BASE);
		*(data.end() - 2) %= BASE;
	}
}

void BigInt::div10() {
	if (!data.size())
		return;
	vector< int >::reverse_iterator i;
	for (i = data.rbegin(); i + 1 != data.rend(); i++) {
		*(i + 1) += (*i % 10) * BASE;
		*i /= 10;
	}
	*i /= 10;

	if (!*(data.end() - 1))
		data.erase(data.end() - 1);
}

BigInt& BigInt::operator=(const BigInt &x){
	if (this != &x)
	{
		data = x.data;
	}
	return *this;
}

ostream &operator << (ostream &os, const BigInt &num) {
	if (num.data.size() == 0) {
		os << 0;
		return os;
	}
	vector< int >::const_reverse_iterator i = num.data.rbegin();
	if (*i)
		os << *i;
	i++;
	for (; i != num.data.rend(); i++) {
		os.width(RAZRYAD);
		os.fill('0');
		os << *i;
	}
	return os;
}

istream &operator >> (istream &is, BigInt &num) {
	num = 0;

	string s;
	stack< int > st;

	is >> s;

	int t = 0;
	for (string::iterator i = s.begin(); i != s.end(); i++) {
		if ((i != s.begin()) && (s.end() - i) % RAZRYAD == 0) {
			st.push(t);
			t = 0;
		}
		t *= 10;
		t += *i - '0';
	}
	if (t) {
		st.push(t);
	}

	while (st.size()) {
		num.data.push_back(st.top());
		st.pop();
	}

	return is;
}

BigInt operator + (const BigInt &a, const BigInt &b) {
	BigInt c;

	vector< int >::const_iterator
		ai = a.data.begin(),
		bi = b.data.begin();

	while (ai != a.data.end() || bi != b.data.end()) {
		c.data.push_back(
			(ai != a.data.end() ? *(ai++) : 0)
			+ (bi != b.data.end() ? *(bi++) : 0)
			);
	}

	vector< int >::iterator i;
	for (i = c.data.begin();
		i + 1 != c.data.end(); i++) {
		(*(i + 1)) += (*i) / BASE;
		(*i) %= BASE;
	}

	if ((*i) >= BASE) {
		c.data.push_back(*i / BASE);
		*(c.data.end() - 2) %= BASE;
	}

	return c;
}

BigInt operator - (const BigInt &a, const BigInt &b) {

	BigInt c;

	if (a < b) {
		throw 1;
	}

	for (vector< int >::const_iterator
		ai = a.data.begin(),
		bi = b.data.begin();

	ai != a.data.end();
	) {
		c.data.push_back(*ai++ - (bi != b.data.end() ? *bi++ : 0));
	}

	for (vector< int >::iterator i = c.data.begin();
		i + 1 != c.data.end(); i++) {
		(*i) += BASE;
		(*(i + 1))--;
		(*(i + 1)) += (*i) / BASE;
		(*i) %= BASE;
	}

	vector< int >::iterator i = c.data.end() - 1;
	if (c.data.size() > 1)
	while (c.data.size() && *i == 0) {
		i = c.data.erase(i) - 1;
	}

	return c;
}

BigInt operator * (const BigInt &a, const BigInt &b) {

	BigInt c;
    c.data = vector< int >(a.data.size() + b.data.size() + 1, 0);

	for (vector< int >::const_iterator ai = a.data.begin();
		ai != a.data.end(); ai++) {
		vector< int >::iterator
			ci = c.data.begin() + (ai - a.data.begin());
		for (vector< int >::const_iterator bi = b.data.begin();
			bi != b.data.end(); bi++, ci++) {
			*ci += ((*ai) * (*bi));
			*(ci + 1) += (*ci) / BASE;
			*ci %= BASE;
		}
	}

	vector< int >::iterator i = c.data.end() - 1;
	while (c.data.size() > 1 && *i == 0) {
		i = c.data.erase(i) - 1;
	}

	return c;
}

BigInt operator / (BigInt a, BigInt b) {

	if (a < b)
		return 0;
	if (!b.data.size())
		throw 1;
	BigInt c;
	int x = 0;
	while (a >= b) {
		b.mul10();
		x++;
	}
	b.div10();
	while (x--) {
		while (a >= b) {
			a = a - b;
			c = c + 1;
		}
		c.mul10();
		b.div10();
	}

	c.div10();
	if (c.data.size() == 0)
		c.data.push_back(0);
	return c;
}

BigInt operator % (BigInt a, BigInt b) {
	if (a < b)
		return a;
	int x = 0;
	while (a >= b) {
		b.mul10();
		x++;
	}
	b.div10();
	while (x--) {
		while (a >= b) {
			a = a - b;
		}
		b.div10();
	}
	return a;
}

BigInt power(const BigInt &a, const BigInt &b) {

	if (b.data.size() == 0) {
		return 1;
	}

	if (b == 1) {
		return a;
	}

	BigInt t = power(a, b / 2);
	if (b.data[0] % 2)
		return t * t * a;
	else
		return t * t;
}

BigInt modul_mult(BigInt &a, BigInt &b, BigInt &modul){
    BigInt one(1), two(2), zero(0);
    if (b == zero)
        return one;
	if (b == one)
		return a;
	BigInt trans, supp;
    trans = b % two;
    if (trans == zero)
	{
        supp = b / two;
		trans = modul_mult(a, supp, modul);
		supp = trans*two;
		supp = supp%modul;
		return supp;
	}
	supp = b - one;
	trans = modul_mult(a, supp, modul);
	supp = trans + a;
	supp = supp%modul;
	return supp;
}

BigInt fast_power(BigInt &num, BigInt &power, BigInt &modulus){
    BigInt one(1), two(2), zero(0);
    if (power == zero)
		return one;
	if (power == one)
		return num;


	BigInt trans, supp;
    trans = power % two;
    if (trans == zero)
	{
        supp = power / two;
		trans = fast_power(num, supp, modulus);
		supp = modul_mult(trans, trans, modulus);
		supp = supp%modulus;
		return supp;
	}
	supp = power - one;
	trans = fast_power(num, supp, modulus);
	supp = modul_mult(trans, num, modulus);
	supp = supp%modulus;
	return supp;
}

int cmp(const BigInt &a, const BigInt &b) {
	if (a.data.size() != b.data.size())
		return a.data.size() - b.data.size();

	for (vector< int >::const_reverse_iterator
		ai = a.data.rbegin(),
		bi = b.data.rbegin();

	ai != a.data.rend();

	ai++, bi++
		) {

		if (*ai != *bi)
			return *ai - *bi;
	}
	return 0;
}

bool operator < (const BigInt &a, const BigInt &b) {
	return cmp(a, b) < 0;
}

bool operator > (const BigInt &a, const BigInt &b) {
	return cmp(a, b) > 0;
}

bool operator <= (const BigInt &a, const BigInt &b) {
	return cmp(a, b) <= 0;
}

bool operator >= (const BigInt &a, const BigInt &b) {
	return cmp(a, b) >= 0;
}

bool operator == (const BigInt &a, const BigInt &b) {
	return cmp(a, b) == 0;
}

bool operator != (const BigInt &a, const BigInt &b) {
	return cmp(a, b) != 0;
}








SBigInt::SBigInt()
{
	sign = true;
}

SBigInt::~SBigInt()
{
}

SBigInt::SBigInt(const SBigInt &x){
	data = x.data;
	sign = x.sign;
}

SBigInt& SBigInt::operator=(const SBigInt &x){
	if (this != &x)
	{
		data = x.data;
		sign = x.sign;
	}
	return *this;
}

SBigInt operator + (const SBigInt &a, const SBigInt &b){
	SBigInt temp;
	if (a.sign != b.sign)
	{
		if (a.sign)
		{
			if (b.data == a.data)
			{
				temp.sign = true;
                temp.data = zero;
				return temp;
			}
			if (b.data < a.data)
			{
				temp.sign = true;
				temp.data = a.data - b.data;
				return temp;
			}
			else
			{
				temp.sign = false;
				temp.data = b.data - a.data;
				return temp;
			}
		}
		else
		{
			if (b.data == a.data)
			{
				temp.sign = true;
                temp.data = zero;
				return temp;
			}
			if (b.data > a.data)
			{
				temp.sign = true;
				temp.data = b.data - a.data;
				return temp;
			}
			else
			{
				temp.sign = false;
				temp.data = a.data - b.data;
				return temp;
			}
		}
	}
	else
	{
		if (!a.sign)
		{
			temp.sign = false;
			temp.data = a.data + b.data;
			return temp;
		}
		if (a.sign)
		{
			temp.sign = true;
			temp.data = a.data + b.data;
			return temp;
		}
	}
}

SBigInt operator - (const SBigInt &a, const SBigInt &b){
	SBigInt temp;
	if (a.sign == b.sign)
	{
		if (a.data == b.data)
		{
			temp.data = true;
            temp.data = zero;
			return temp;
		}
		if (a.sign)
		{
			if (a.data > b.data)
			{
				temp.sign = true;
				temp.data = a.data - b.data;
				return temp;
			}
			else
			{
				temp.sign = false;
				temp.data = b.data - a.data;
				return temp;
			}
		}
		else
		{
			if (a.data > b.data)
			{
				temp.sign = false;
				temp.data = a.data - b.data;
				return temp;
			}
			else
			{
				temp.sign = true;
				temp.data = b.data - a.data;
				return temp;
			}
		}
	}
	else
	{
		if (a.sign)
		{
			temp.sign = true;
			temp.data = a.data + b.data;
			return temp;
		}
		else
		{
			temp.sign = false;
			temp.data = a.data + b.data;
			return temp;
		}
	}
}

SBigInt operator * (const SBigInt &a, const SBigInt &b){
	SBigInt temp;

	if (a.sign != b.sign)
		temp.sign = false;

	temp.data = a.data * b.data;
	return temp;
}

SBigInt operator / (SBigInt a, SBigInt b){

	SBigInt temp;

	if (a.sign != b.sign)
		temp.sign = false;

    temp.data = a.data / b.data;
	return temp;

}

SBigInt operator % (SBigInt a, SBigInt b){
	SBigInt temp;

	temp.data = a.data % b.data;

	return temp;
}

SBigInt::SBigInt(const BigInt &x){
    data =x;
    sign=true;
}


ostream &operator << (ostream &os, const SBigInt &num){
    if(!num.sign)
        os<<"-";
    os<<num.data;
    return os;
}
