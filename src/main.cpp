
#include <iostream>
#include <encrypt.h>




int main()
{

    key poog = generateKey(15,3,3,3);

    encrypt(poog,"test.txt");
    decrypt(poog,"encrypted.txt");
}
