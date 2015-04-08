#include "rsa.h"
#include <iostream>
using namespace std;
int main(void){
	RSA tryhard;
	BigInt e, n, mes, result;
    mes = (BigInt)"12";
	tryhard.PublicKey(e, n);
    cout << e << " exp" << endl << n << "   modulus" << endl<<tryhard.dog.d<<"  secret"<<endl;

	cout << "incoming message " << mes << endl;

	 tryhard.encrypt(result,mes, e, n);
    cout << "encrypt  " << result << endl;

    tryhard.decrypt(result,mes);

    cout << "decrypt message " << mes << endl;

	return 0;
}
