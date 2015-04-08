#include "rsa.h"

RSA::RSA()
{
}

RSA::~RSA()
{

}

void RSA::encrypt(BigInt& cryptmes,BigInt& message, BigInt& e, BigInt& n){
	cryptmes= fast_power(message, e, n);
}

void RSA::decrypt(BigInt& cryptmes,BigInt& message){
	message= fast_power(cryptmes, dog.d, dog.n);
}

void RSA::PublicKey(BigInt &exp, BigInt &modulus){
	exp = dog.e;
	modulus = dog.n;
}
