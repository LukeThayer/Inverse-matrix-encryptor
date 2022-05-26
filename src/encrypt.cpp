#include <encrypt.h>

key generateKey(int complexity, int seed, int chunkSize, int n)
{
    key nKey;

    nKey.complexity = complexity;
    nKey.seed = seed;
    nKey.chunkM = chunkSize;
    nKey.n = n;

    for (int i = 0; i < complexity; i++)
    {
       std::vector<matrix> temp = _generateElem(seed + i, n);
       nKey.forward.push_back(temp[0]);
       nKey.inverse.push_back(temp[1]);
    }
    
return nKey;
}

std::vector<matrix> _generateElem(int seed, int n)
{
    //intiallizes A and B as the identity matrix
    matrix A(n,n);
    matrix B(n,n);
    for(int i = 1; i <= n; i++)
    {
        A.insert(i,i,1);
        B.insert(i,i,1);
    }

    int rowA;
    int rowB;


    srand(seed);
    int type = rand() % 3;


if (type == 0 )
{
    rowA = rand() % n + 1;
    rowB = rand() % n + 1;
        
    A.swap_rows(rowA,rowB);
    B.swap_rows(rowB,rowA);
}
// else if(type == 1)
// {
//     rowA = rand() % n + 1;
//     int scale = rand() % 10 + 1;

//     A.scale_row(rowA,scale);
// }
else
{
    rowA = rand() % n + 1;

    rowB = rand() % n + 1;
    if (rowA == rowB && rowA == 1)
    {
        rowB = 2;
    }
    else if(rowA == rowB)
    {
        rowB = 1;
    }
    
        
    A.add_rows(rowA,rowB,1);
    B.add_rows(rowA,rowB,-1);
}

    std::vector<matrix> C;
    C.push_back(A);
    C.push_back(B);

  return C;
}



matrix _string_to_chunk(std::string in, key &nkey)
{

    matrix A(nkey.chunkM,nkey.n);
    int string_L = nkey.chunkM * nkey.n;

    for (int i = 0; i < string_L; i++)
    {
        int y = i/nkey.n+1 ;
        int x = i%nkey.n+1;
        A.insert(y,x,int(in[i]));
    }
    
    return A;
}


matrix _encrypt_chunk (matrix A, key &nkey)
{
    matrix B = A;
    for (int i = 0; i < nkey.complexity; i++)
    {
       B =  nkey.forward[i].mult(B);
    }
    
    return B;
}

matrix _decrypt_chunk (matrix A,  key &nkey)
{

    matrix B = A;
    for (int i = 0; i < nkey.complexity; i++)
    {
       B =  nkey.inverse[nkey.complexity-1-i].mult(B);
    }
    
    return B;

}


std::string _chunk_to_string(matrix A, key &nkey)
{
    std::string out;

    int string_L = nkey.chunkM * nkey.n;

    for (int i = 0; i < string_L; i++)
    {
        int y = i/nkey.n+1 ;
        int x = i%nkey.n+1;
       out = out + char(A.read(y,x));
    }

return out;
}


void writeKey(key nkey){
    std::fstream fout;
    fout.open("key.txt");

    fout << nkey.complexity << ","
         << nkey.n << ","
         << nkey.chunkM << ","
         << nkey.seed << ",";
         for (int i = 0; i < nkey.complexity; i++)
         {
          fout << nkey.forward[i].m << ","
               << nkey.forward[i].n << ",";
               for (int j = 0; j < nkey.forward[i].m*nkey.forward[i].n; j++)
               {
                   fout << nkey.forward[i].entries[j] << ",";
               }
               
         }

         for (int i = 0; i < nkey.complexity; i++)
         {
          fout << nkey.inverse[i].m << ","
               << nkey.inverse[i].n << ",";
               for (int j = 0; j < nkey.inverse[i].m*nkey.inverse[i].n; j++)
               {
                   fout << nkey.inverse[i].entries[j] << ",";
               }
               
         }
    fout.close();
}

key loadKey(std::string dir)
{
    std::fstream fout;
    fout.open(dir);
    char comma;
    key nkey;

    int Tent;
    matrix empty;

    fout>>nkey.complexity>>comma   
        >>nkey.n>>comma
        >>nkey.chunkM>>comma
        >>nkey.seed>>comma;

        for (int i = 0; i < nkey.complexity; i++)
         {
             nkey.forward.push_back(empty);
          fout >> nkey.forward[i].m >> comma
               >> nkey.forward[i].n >> comma;
               for (int j = 0; j < nkey.forward[i].m*nkey.forward[i].n; j++)
               {
                   fout >> Tent >> comma;
                   nkey.forward[i].entries.push_back(Tent);
               }
               
         }

         for (int i = 0; i < nkey.complexity; i++)
         {
          nkey.inverse.push_back(empty);
          fout >> nkey.inverse[i].m >> comma
               >> nkey.inverse[i].n >> comma;
               for (int j = 0; j < nkey.inverse[i].m*nkey.inverse[i].n; j++)
               {
                   fout >> Tent >> comma;
                   nkey.inverse[i].entries.push_back(Tent);
               }
               
         }
    fout.close();

    return nkey;
} 


void encrypt(key nkey, std::string dir)
{
    std::fstream fin;
    fin.open(dir);

    char p;

    std::string buf;
    char tchunk;
    matrix chunk(nkey.chunkM,nkey.n);

    bool working = true;

    bool firstitr = true;
   
    while (working)
    {

        for (int i = 0; i < nkey.chunkM*nkey.n; i++)
        {

            int y = i/nkey.n+1 ;
            int x = i%nkey.n+1;

            if (fin.peek()!=EOF)
            {
             fin.get(tchunk);
            chunk.insert(y,x,int(tchunk));
            
            }
            else
            {
                chunk.insert(y,x,0);
                working = false;
            }
            
        }

        std::cout << "---chunk--"<< std::endl;
        chunk.print();

        chunk =  _encrypt_chunk(chunk,nkey);

        std::cout << "---encrypt chunk--"<< std::endl;
        chunk.print();
    

        for (int i = 0; i < nkey.n*nkey.n -1; i++)
        {
            int y = i/nkey.n+1 ;
            int x = i%nkey.n+1;

            if (firstitr)
            {
                buf = char(chunk.read(y,x));
                firstitr = false;
            }
            else
            {
                buf = buf + char(chunk.read(y,x));
            }
            
        }
        if (fin.peek()==EOF)
        {
            working = false;
        }
        

    }

    fin.close();

    std::cout << buf.size()<< std::endl;
    fin.open("encrypted.txt");
    fin<<buf;
    

}


void decrypt(key nkey, std::string dir)
{
   std::fstream fin;
    fin.open(dir);

    char p;

    std::string buf;
    char tchunk;
    matrix chunk(nkey.n,nkey.n);

    bool working = true;

    while (working)
    {

        for (int i = 0; i < nkey.n*nkey.n; i++)
        {

            int y = i/nkey.n+1 ;
            int x = i%nkey.n+1;

            if (fin.peek()!=EOF)
            {
             fin.get(tchunk);
             
             chunk.insert(y,x,int(tchunk));
            
            }
            else
            {
                chunk.insert(y,x,32);
                working = false;
            }
            
        }
        std::cout << "---read encrypt--"<< std::endl;
        chunk.print();
        chunk =  _decrypt_chunk(chunk,nkey);
        

     for (int i = 0; i < nkey.chunkM*nkey.n-1; i++)
        {
            int y = i/nkey.n+1 ;
            int x = i%nkey.n+1;

            if (i == 0)
            {
                buf = char(chunk.read(y,x));
            }
            else
            {
                buf = buf + char(chunk.read(y,x));
            }
        }

        if (fin.peek()==EOF)
        {
            working = false;
        }
        

    }
    fin.close();

    fin.open("decrypted.txt");
    fin<<buf;
    
}