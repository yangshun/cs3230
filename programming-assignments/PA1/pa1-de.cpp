// CS3230-PA1-DE
// Multiplication of 2 n-digit integers.
// Naive O(n^2) multiplication algorithm (Long Multiplication)
// Name: Tay Yang Shun

#include <iostream>
using namespace std;
#define     FOR(i,s,e)      for(int (i) = (s); (i) <  (e); ++(i))
#define     REP(i,n)        FOR(i,0,n)
#define     FORE(i,s,e)     for(int (i) = (s); (i) <= (e); ++(i))

const string    Digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char      RADIX_POINT = '.';
const int       MAXSIZE = 20200;
const int       CUT_OFF = 3;

inline int valueOf(char x){ // integer value of a digit
    if ('0' <= x and x <= '9') return x - '0';
    if ('A' <= x and x <= 'Z') return x - 'A' +10;
    return 255;
};

int A[MAXSIZE], B[MAXSIZE], *temp, *res;

// Trim unnecessary zeros and radix point
string trim(string aStr){
    string X = aStr;
    //leading zeros:
    while(X.length()>1 and X[0] == '0'and X[1] != RADIX_POINT) X.erase(0,1); //000.001

    //trailing zeros and radix point:
    if (X.find(RADIX_POINT) != string::npos) {
        while (X.length() >= 1 and X[X.length()-1] == '0') {
            X.erase(X.length()-1,1);//0.010; 1.000
        }
        if (X.length() >= 1 and X[X.length()-1] == RADIX_POINT) {
            X.erase(X.length()-1);//123.
        }
        if (X[0] == RADIX_POINT) {
            X = "0" + X; // insert "0" into ".123"
        }
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
    if (rpA == string::npos) {
        rpA = 0;
    } else {
        rpA = X.length() - 1 - rpA;
    }

    if (rpA!=0) {
        X.erase(X.find(RADIX_POINT), 1);
    }
    X = trim(X);
    A[0] = X.length();
    REP(i, X.length()) {
        A[X.length()-i] = valueOf(X[i]);
    }
}

// Convert an array A to string:
string convertIntArr2Str(int *A, int rpA){
    while (A[0] <= rpA) {
        A[0]++;
        A[A[0]] = 0;
    };
    string S = "";
    REP(i, A[0]) {
        if (rpA and i == rpA ) {
            S = RADIX_POINT + S;
        }
        S = Digits[A[i+1]] + S;
    }
    return trim(S);
};

// Adding two arrays with offset: USEFUL for karatsuba algorithm!!
// A = A + B * base^offset
inline void add(int *A, int *B, int offset, int base){
    int lenA = A[0], lenB = B[0];
    int carry = 0;
    int i = 1;
    offset++;

    int b;
    while (i <= lenB or carry > 0) {
        if (offset > lenA) {
            A[offset] = 0;
        }
        if (i > lenB) {
            b = 0;
        } else {
            b = B[i];
        }

        carry = A[offset] + b + carry;
        A[offset] = carry % base;
        carry = carry >= base ? 1 : 0;

        i++;
        offset++;
    };

    offset--;
    while (offset > 1 and A[offset] == 0) {
        offset--;
    }
    if (offset > lenA) {
        A[0] = offset;
    }
};

inline void subtract(int *A, int *B, int base) {
    // A = A - B
    // Requirement: A > B
    int lenA = A[0];
    int lenB = B[0];
    for (int i = 1; i <= lenB; i++) {
        if (A[i] < B[i]) {
            int j = i + 1;
            while (A[j] == 0) {
                A[j] = base - 1;
                j++;
            }
            A[j] -= 1;
            A[i] = base + A[i] - B[i];
        } else {
            A[i] -= B[i];
        }
    }
    while (lenA > 1 and A[lenA] == 0) {
        lenA--;
    }
    A[0] = lenA;
};

// Multiply an array A to a digit d
// temp = A * d;
inline int* mul(int *A, int d, int base){
    int lenA  = A[0];
    temp[0] = lenA;
    int carry = 0;
    int i = 1;

    while (i<=lenA or carry>0) {
        if (i > lenA) {
            A[i] = 0;
        }

        carry = A[i] * d + carry;
        temp[i] = carry % base;
        carry = carry / base;

        i++;
    };

    i--;
    while (i>1 and temp[i]==0) {
        i--;
    }

    if (i>=lenA) {
        temp[0] = i;
    }

    return temp;
};

// Multiply 2 arrays:
// A = A * B;
int* mul(int *A, int* B, int base){
    temp = new int[MAXSIZE];
    res = new int[MAXSIZE];
    REP(i, A[0]+2) res[i] = 0;

    int i = 1;
    while (i<=B[0]) {
        // REP(j,C[0]+2) D[j]=C[j];
        temp = mul(A, B[i], base);
        add(res, temp, i-1, base);
        i++;
    };

    return res;
};

// Faster multiplication:
// res = A * B;
int* mulTwoArrays(int *A, int *B, int base) {
    res = new int[MAXSIZE];
    temp = new int[MAXSIZE];
    REP(i, A[0]+2) res[i] = temp[i] = 0;
    int lenA = A[0];
    int lenB = B[0];

    FORE(i, 1, lenA)
    FORE(j, 1, lenB) {
        temp[i+j-1] += A[i] * B[j];
    };

    int lenR = lenA + lenB + 1;
    int carry = 0;
    FORE(i, 1, lenR) {
        carry += temp[i];
        res[i] = carry % base;
        carry  = carry / base;
    };

    while (lenR>1 and res[lenR] == 0) {
        lenR--;
    }
    res[0] = lenR;

    return res;
};

void splitAt(int *input, int *high, int *low, int R) {
    int lenInput = input[0];

    for (int i = 1; i <= R; i++) {
        low[i] = (i <= lenInput) ? input[i] : 0;
    }
    low[0] = (lenInput <= R) ? lenInput : R;

    for (int i = 1; i <= R; i++) {
        high[i] = (i <= lenInput) ? input[i+R] : 0;
    }
    high[0] = (lenInput - R > 0) ? lenInput - R : 0;
}

void printIntArray(int arr[]) {
    for (int i = 10; i >= 1; i--) {
        cout << arr[i];
    }
    cout << endl;
};

int* karatsuba(int *A, int *B, int base) {
    int lenA = A[0];
    int lenB = B[0];

    if (lenA < CUT_OFF or lenB < CUT_OFF) {
        return mul(A, B, base);
    }

    int R = ((lenA > lenB ? lenA : lenB)+1) / 2;

    int *highX = new int[R+2];
    int *lowX = new int[R+2];
    int *highY = new int[R+2];
    int *lowY = new int[R+2];
    splitAt(A, highX, lowX, R);
    splitAt(B, highY, lowY, R);

    int *z0 = karatsuba(lowX, lowY, base);
    int *z2 = karatsuba(highX, highY, base);

    add(lowX, highX, 0, base);
    add(lowY, highY, 0, base);

    int *z1 = karatsuba(lowX, lowY, base);

    subtract(z1, z0, base);
    subtract(z1, z2, base);
    add(z0, z2, 2 * R, base);
    add(z0, z1, R, base);

    return z0;
}

int main() {
    int T;
    string V, M, P;
    int base;

    int rpA, rpB, rpC;

    cin >> T;
    FORE(t, 1, T) {
        cin >> base;
        cin >> V >> M;

        convert2IntArr(V, A, rpA);
        convert2IntArr(M, B, rpB);

        cout << convertIntArr2Str(karatsuba(A, B, base), 0) << endl;
    };

    return 0;
}
