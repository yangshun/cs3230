// CS3230-PA1-DE
// Multiplication of 2 n-digit integers.
// Naive O(n^2) multiplication algorithm (Karatsuba + Long Multiplication)
// Name: Tay Yang Shun

#include <sys/time.h>
#include <sys/resource.h>
#include <iostream>
#include <sstream>
#include <math.h>
#include <stdint.h>

using namespace std;

#define     FOR(i,s,e)      for(int64_t (i) = (s); (i) <  (e); ++(i))
#define     REP(i,n)        FOR(i,0,n)
#define     FORE(i,s,e)     for(int64_t (i) = (s); (i) <= (e); ++(i))

const string        Digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char          RADIX_POINT = '.';
const int64_t       CHUNK_SIZE = 8;
const int64_t       MAXSIZE = 200000;
const int64_t       CUT_OFF = 500;
const int64_t       CHUNK_BASE = pow(10, CHUNK_SIZE);

long getMemoryUsage() {
    struct rusage usage;
    if(0 == getrusage(RUSAGE_SELF, &usage)) {
        return usage.ru_maxrss / 1000; // bytes
    } else {
        return 0;
    }
}

inline int64_t valueOf(char x){ // integer value of a digit
    if ('0' <= x and x <= '9') return x - '0';
    if ('A' <= x and x <= 'Z') return x - 'A' +10;
    return 255;
};

int64_t A[MAXSIZE], B[MAXSIZE], *temp, *res;

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
// X = "123456789"
// A = {3,6789,2345,1};
void convert2IntArr(string X, int64_t *A){

    X = trim(X);
    int64_t len = X.length() / CHUNK_SIZE;
    int64_t rem = (X.length() % CHUNK_SIZE);
    int64_t padLength;
    if (rem > 0) {
        padLength = CHUNK_SIZE - rem;
        for (int64_t i = 0; i < padLength; i++) {
            X = "0" + X;
        }
        len += 1;
    }
    A[0] = len;
    int64_t j = 1;
    for (int64_t i = X.length()-1; i >= 0; i-=CHUNK_SIZE) {
        int64_t num = 0;
        for (int64_t k = 0; k < CHUNK_SIZE; k++) {
            num += valueOf(X[i-k]) * pow(10, k);
        }
        A[j] = num;
        j++;
    }
}

string numberToString(int64_t number) {
    string s = "";
    if (number == 0) {
        return "0";
    } else {
        while (number > 0) {
            int64_t digit = number % 10;
            s = Digits[digit] + s;
            number /= 10;
        }
        return s;
    }
}

// Convert an array A to string:
string convertIntArr2Str(int64_t *A){
    string result = "";
    int64_t len = A[0];
    
    for (int64_t i = len; i >= 1; i--) {
        string s = numberToString(A[i]);
        int64_t currLen = s.length();
        for (int64_t j = 0; j < CHUNK_SIZE - currLen; j++) {
            s = "0" + s;
        }
        result += s;
    }
    return trim(result);
};

// Adding two arrays with offset: USEFUL for karatsuba algorithm!!
// A = A + B * base^offset
inline void add(int64_t *A, int64_t *B, int64_t offset, int64_t base){
    int64_t lenA = A[0], lenB = B[0];
    int64_t carry = 0;
    int64_t i = 1;
    offset++;

    int64_t b;
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

inline void subtract(int64_t *A, int64_t *B, int64_t base) {
    // A = A - B
    // Requirement: A > B
    int64_t lenA = A[0];
    int64_t lenB = B[0];
    for (int64_t i = 1; i <= lenB; i++) {
        if (A[i] < B[i]) {
            int64_t j = i + 1;
            while (A[j] == 0) {
                A[j] = base - 1;
                j++;
            }
            A[j] -= 1;
            int64_t temp = A[i];
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

// Faster multiplication:
// res = A * B;
inline int64_t* mulTwoArrays(int64_t *A, int64_t *B, int64_t base) {
    res = new int64_t[MAXSIZE];
    temp = new int64_t[MAXSIZE];
    REP(i, A[0]+2) res[i] = temp[i] = 0;
    int64_t lenA = A[0];
    int64_t lenB = B[0];

    FORE(i, 1, lenA)
    FORE(j, 1, lenB) {
        temp[i+j-1] += A[i] * B[j];
    };

    int64_t lenR = lenA + lenB + 1;
    int64_t carry = 0;
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

inline void splitAt(int64_t *input, int64_t *high, int64_t *low, int64_t R) {
    int64_t lenInput = input[0];

    for (int64_t i = 1; i <= R; i++) {
        low[i] = (i <= lenInput) ? input[i] : 0;
    }
    low[0] = (lenInput <= R) ? lenInput : R;

    for (int64_t i = 1; i <= R; i++) {
        high[i] = (i <= lenInput) ? input[i+R] : 0;
    }
    high[0] = (lenInput - R > 0) ? lenInput - R : 0;
};

int64_t* karatsuba(int64_t *A, int64_t *B, int64_t base) {
    int64_t lenA = A[0];
    int64_t lenB = B[0];

    if (lenA < CUT_OFF or lenB < CUT_OFF) {
        return mulTwoArrays(A, B, base);
    }

    int64_t R = ((lenA > lenB ? lenA : lenB)+1) / 2;

    int64_t highX[R+2];
    int64_t lowX[R+2];
    int64_t highY[R+2];
    int64_t lowY[R+2];
    splitAt(A, highX, lowX, R);
    splitAt(B, highY, lowY, R);

    int64_t *z0 = karatsuba(lowX, lowY, base);
    int64_t *z2 = karatsuba(highX, highY, base);

    add(lowX, highX, 0, base);
    add(lowY, highY, 0, base);

    int64_t *z1 = karatsuba(lowX, lowY, base);

    subtract(z1, z0, base);
    subtract(z1, z2, base);
    add(z0, z2, 2 * R, base);
    add(z0, z1, R, base);

    return z0;
}

int main() {
    int64_t T;
    string V, M, P;
    int64_t base;

    cin >> T;
    FORE(t, 1, T) {
        cin >> base;
        cin >> V >> M;

        convert2IntArr(V, A);
        convert2IntArr(M, B);
        cout << convertIntArr2Str(karatsuba(A, B, CHUNK_BASE)) << endl;
    };
    // cout << "Memory used: " << getMemoryUsage() << " KB" << endl;
    return 0;
}
