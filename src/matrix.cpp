#include <matrix.h>



void matrix::swap_rows(int rowA, int rowB)
{

for (int i = 1; i <= n; i++)
    {
        int valA = read(rowA,i);
        int valB = read(rowB,i);

        insert(rowA,i,valB);

        insert(rowB,i,valA);
        
    }
}


void matrix::scale_row(int row, int scale)
{

    for (int i = 1; i <= n; i++)
    {
        int temp = read(row,i) * scale;

        insert(row,i, temp);
    }
}

void matrix::add_rows(int rowA, int rowB, int scale)
{
     for (int i = 1; i <= n; i++)
    {
        int temp = read(rowA,i) + read(rowB,i)*scale;

        insert(rowA,i, temp);
    }

}



matrix matrix::mult(matrix b)
{
    matrix nMatrix(m,b.n);
    int result = 0;


    if (n == b.m)
    {
       for (int i = 1; i <= b.n; i++)
       {
          for(int j = 1; j <= m; j++)
          {
              for(int k = 1; k <= n; k++)
              {
                
                result += read(i,k)*b.read(k,j);
              }
            nMatrix.insert(i,j,result);
            result = 0;
          }
       }
       
    }
    else
    {
        std::cerr<< "A.N != B.M"<< std::endl;
        return b;
    }


    return nMatrix;
}


int matrix::read(int Im, int In)
{
    In--;
    Im--;
    int index = n*Im + In;
    int returnVal;
    if (index < entries.size())
    {
        returnVal = entries[index];
    }
    else
    {
        returnVal =  -99999;
    }
    return returnVal;

}


void matrix::insert(int Im, int In, int value)
{
    In--;
    Im--;
    int index = n*Im + In;
    if (index < entries.size())
    {
        entries[index] = value;
    }
    else
    {
        std::cerr<< "INVALID INDEX"<< std::endl;
    }
    
}


void matrix::print()
{

    
       for (int j = 1; j <= m; j++)
       {
          for(int i = 1; i <= n; i++)
          {
              
            std::cout<<read(j,i)<<" ";
          }
           std::cout << std::endl;
       }
    std::cout << std::endl;
}

matrix::matrix(int Im, int In)
{
    n = In;
    m = Im;
    entries.resize(n*m);
    for(int i = 0; i < entries.size(); i++)
    {
       entries[i]= 0;
    }
    
}

matrix::matrix()
{
}

matrix::~matrix()
{
}


