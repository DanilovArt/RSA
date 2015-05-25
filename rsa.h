#ifndef RSA_H
#define RSA_H
#include"bigint.h"
#include"keys.h"

class RSA
{
public:
	RSA();
	~RSA();
	void encrypt(BigInt& cryptmes, BigInt& message, BigInt& e, BigInt& n);
    void encrypt(BigInt& cryptmes, BigInt& message);

   // void encrypt(std::vector<BigInt>& cryptmes, std::string& message, BigInt& e, BigInt& n);
   // void decrypt(std::vector<BigInt>& cryptmes, std::string& message);
	void decrypt(BigInt& cryptmes, BigInt& message);
	void PublicKey(BigInt &exp, BigInt& modulus);
private:
	Keys dog;
};

#endif // RSA_H
