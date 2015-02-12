// CS3230-PA1-ABC
// Multiplication of 2 n-digit integers.
// Naive O(n^2) multiplication algorithm (Long Multiplication)
// Name:
// Date:

#include <iostream>
using namespace std;
#define     FOR(i,s,e)      for(int (i) = (s); (i) <  (e); ++(i))
#define     REP(i,n)        FOR(i,0,n)
#define     FORE(i,s,e)     for(int (i) = (s); (i) <= (e); ++(i))

const string    Digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char      RADIX_POINT = '.';
const int       MAXSIZE = 10100;

inline int valueOf(char x){ // integer value of a digit
    if ('0' <= x and x <= '9') return x - '0';
    if ('A' <= x and x <= 'Z') return x - 'A' +10;
    return 255;
};

int A[MAXSIZE], B[MAXSIZE], *Temp, *Res;

//trim unnecessary zeros and radix point
string trim(string aStr){
    string X = aStr;
    //leading zeros:
    while(X.length()>1 and X[0] == '0'and X[1] != RADIX_POINT) X.erase(0,1); //000.001

    //trailing zeros and radix point:
    if (X.find(RADIX_POINT) != string::npos){
        while(X.length()>=1 and X[X.length()-1] =='0')
            X.erase(X.length()-1,1);//0.010; 1.000
        if   (X.length()>=1 and X[X.length()-1] == RADIX_POINT)
            X.erase(X.length()-1);//123.
        if (X[0] == RADIX_POINT)
            X = "0" + X; // insert "0" into ".123"
    };
    if (X == "") X = "0";
    return X;
};



// Convert string into array of integer:
// A[0] stores length of the number;
// Digits are stored in reverse order, example:
// X = "12.444"
// A = {5,4,4,4,2,1}, rpA = 3;
void convert2IntArr(string X, int *A, int &rpA){

    rpA = X.find(RADIX_POINT);
    if (rpA == string::npos) rpA = 0;
    else rpA = X.length()-1-rpA;

    if (rpA!=0) X.erase(X.find(RADIX_POINT),1);
    X = trim(X);

    A[0] = X.length();
    REP(i,X.length())
        A[X.length()-i] = valueOf(X[i]);
}

//Convert an array A to string:
string convertIntArr2Str(int *A, int rpA){
    while(A[0]<=rpA){
        A[0]++;
        A[A[0]] = 0;
    };
    string S = "";
    REP(i,A[0]){
        if (rpA and i == rpA ) S = RADIX_POINT + S;
        S = Digits[A[i+1]] + S;
    }
    return trim(S);
};

// Adding two arrays with offset: USEFUL for karatsuba algorithm!!
// A = A + B * base^offset
inline void add(int *A, int *B, int offset, int base){
    int lenA = A[0], lenB = B[0];
    //A.resize(MAXSIZE);
    int carry = 0;
    int i=1;
    offset++;

    int b;
    while(i<=lenB or carry>0){
        if (offset > lenA) A[offset] = 0;
        if (i > lenB) b = 0; else b = B[i];

        carry       = A[offset] + b + carry;
        A[offset]   = carry%base;
        carry       = carry>=base?1:0;

        i++;
        offset++;
    };

    offset--;
    while(offset>1 and A[offset] == 0) offset--;
    if (offset>lenA) A[0] = offset;
};

//Multiply an array A to a digit d
//Temp = A * d;
inline int* mul(int *A, int d, int base){
    int lenA  = A[0];
    Temp[0] = lenA;
    int carry = 0;
    int i=1;

    while(i<=lenA or carry>0){
        if (i>lenA) A[i] = 0;

        carry       = A[i] * d + carry;
        Temp[i]     = carry % base;
        carry       = carry / base;

        i++;
    };

    i--;
    while(i>1 and Temp[i]==0) i--;
    if (i>=lenA) Temp[0] = i;

    return Temp;
};

// Multiply 2 arrays:
// A = A * B;
int* mul(int *A, int* B, int base){
    Temp    = new int [MAXSIZE];
    Res     = new int [MAXSIZE];
    REP(i, A[0]+2) Res[i] = 0;

    int i = 1;
    while(i<=B[0]){
        //REP(j,C[0]+2) D[j]=C[j];
        Temp = mul(A,B[i],base);
        add(Res,Temp ,i-1,base);
        i++;
    };

    return Res;
};


//Faster multiplication:
// Res = A * B;
int * mul2Arrays(int *A, int *B, int base){
    Res = new int [MAXSIZE];
    Temp    = new int [MAXSIZE];
    REP(i, A[0]+2) Res[i] = Temp[i] = 0;
    int lenA = A[0];
    int lenB = B[0];

    FORE(i,1,lenA)
    FORE(j,1,lenB){
        Temp[i+j-1] += A[i] * B[j];
    };

    int lenR = lenA+lenB+1;
    int carry = 0;
    FORE(i,1,lenR){
        carry += Temp[i];
        Res[i] = carry%base;
        carry  = carry/base;
    };

    while(lenR>1 and Res[lenR]==0) lenR--;
    Res[0] = lenR;

    return Res;
};


int main()
{
    int T;
    string V,M,P;
    int base;

    //vector<int> A,B;
    int rpA, rpB, rpC;

    cin>>T;
    FORE(t,1,T){
        cin>>base;
        cin>>V>>M;

        convert2IntArr(V,A,rpA);
        convert2IntArr(M,B,rpB);

        //Res = mul(A,B,base);      // naive - slow
        Res = mul2Arrays(A,B,base); // direct multiply - faster

        P = convertIntArr2Str(Res,rpA+rpB);
        cout <<P<<endl;
    };

    return 0;
}
