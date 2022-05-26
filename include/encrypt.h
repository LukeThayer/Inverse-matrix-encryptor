#include <matrix.h>
#include <stdlib.h>
#include <fstream>

//key object used to decrypt a file
struct key
{
    //number of elementary steps 
    int complexity;

    //n is the size of the key
    // key needs to be square to have inverses
    int n;

    //size of chunks used when being operated on
    // file is read in as chunks
    // this is the amount of rows
    int chunkM;

    // seed used to generate the elementary steps
    int seed;

    // list of elementary matrixes used
    std::vector<matrix> forward;
    std::vector<matrix> inverse;
};


// file that is going to operated upon
struct file
{

    // wether the file is encrypted or decrypted
    bool encrytped;

    // file to be operated on
    std::fstream stream;
};


// generates a key
// complexity -  the number of elemetary steps
// seed -  used with rand() to determine the steps
// chunkSize - determines size of chunk
// n - determines row count
key generateKey(int complexity, int seed, int chunkSize, int n);

// loads a key from the users directory to be used
// dir - directory to load file from
key loadKey(std::string dir);

// writes the key to the computer of the user for later use
void writeKey(key nkey);

// encrypts the loaded file
void encrypt(key nkey, std::string dir);

// decrypts the loaded file
void decrypt(key nkey, std::string dir);



/****************************************/
//          INTERNAL FUNCTIONS
/****************************************/

//generates a single elementary matrix with the given seed
//seed - seed used for elem generation
//n  - size of matrix to be generated
// returns a vector of both inverse and forward matrixs
// [0] - forward matrix
// [1] - inverse matrix
std::vector<matrix> _generateElem(int seed, int n);

// converts the string into a chunk usable by the given key
// in - the string that will be made into a chunk
// nkey -  reference to the key that will be used
matrix _string_to_chunk(std::string in,  key &nkey);


//uses the given key to attempt and encrypt a chunk
//A - chunk that will be encrypted
//nkey - key being used
matrix _encrypt_chunk (matrix A,  key &nkey);


//uses the given key to decrypt the given chunk
//A - chunk to be decrypted
//nkey - key used to decrypt the chunk
matrix _decrypt_chunk (matrix A,  key &nkey);

//converts the chunk to a string
// A - chunk to made into a string
//nkey - the key used
std::string _chunk_to_string(matrix A, key &nkey);







