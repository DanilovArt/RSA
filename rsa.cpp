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


//void RSA::encrypt(std::vector<BigInt>& cryptmes,std::string& message, BigInt& e, BigInt& n){
//BigInt mes;
//cryptmes.clear();

//for(auto it:message){
//mes=(BigInt)it;
//cryptmes.push_back(fast_power(mes, e, n));
//}

//}



void RSA::encrypt(BigInt& cryptmes, BigInt& message){
    cryptmes= fast_power(message, dog.e, dog.n);

}


//void decrypt(std::vector<BigInt>& cryptmes, std::string& message){}

void RSA::decrypt(BigInt& cryptmes,BigInt& message){
	message= fast_power(cryptmes, dog.d, dog.n);
}

void RSA::PublicKey(BigInt &exp, BigInt &modulus){
	exp = dog.e;
	modulus = dog.n;
}
