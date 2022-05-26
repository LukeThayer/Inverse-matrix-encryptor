#include "vector"
#include <iostream>



//matrix class that can store integers in the form of a matrix
// data can be inserted and read using row column indexing
// m - rows
//n - colunms

class matrix
{

public:
// columns
int n;
// rows
int m;
// list of all values whithin the matrix
std::vector<int> entries;


// multiplies two matrices
// AxB (Dot product)
matrix mult(matrix b);

//swaps two rows with eachother
//  rowA <-> rowB
void swap_rows(int rowA, int rowB);

//scales a row by a value
//row - which row will be scaled
//scale - row multiplier
void scale_row(int row, int scale);


//adds two rows index by index
// rowB + rowA -> rowA
void add_rows(int rowA, int rowB, int scale);

//prints the matrix in an interrpretable fashion
void print();

//returns the value at the inputed index
int read(int Im, int In);


// places a value at the indexed location
void insert(int Im, int In, int value);

matrix();
matrix(int Im, int In);
~matrix();
};


