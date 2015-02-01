/**
    This is a CPP template for CS3230 - Programming Assignment 1 - Part 1
    (January-2015)

    You are not required to follow the template. Feel free to modify any part.

    Comment your code!
**/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

const string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char RADIX_POINT = '.';
const int MAX_LEN = 10010;

int lenV;
int lenM;
int lenTotal;

int valueOf(char x) { // integer value of a digit
    if ('0' <= x and x <= '9') {
        return x - '0';
    }
    
    if ('A' <= x and x <= 'Z') {
        return x - 'A' + 10;
    }

    return 0;
};

char digitOf(int val) { // val must be < base <= 36
    return digits[val];
};

//Trim leading and trailing zeros, and radixpoint
string trim(string aStr) {
    string X = aStr;
    //leading zeros: 000.001
    while (X.length() > 1 and X[0] == '0' and X[1] != RADIX_POINT) {
        X.erase(0,1);
    }

    // trailing zeros and radix point:
    if (X.find(RADIX_POINT) != string::npos) {
        // 0.010; 1.000
        while (X.length() >= 1 and X[X.length()-1] =='0') {
            X.erase(X.length() - 1, 1);
        }

        // 123.
        if (X.length() >= 1 and X[X.length()-1] == RADIX_POINT) {
            X.erase(X.length() - 1); 
        }
        if (X[0] == RADIX_POINT) {
            X = "0" + X; // insert "0" into ".123"
        }
    }

    if (X == "") {
        X = "0";
    }

    return X;
};

void resetArray(int* arr, int len) {
    memset(arr, 0, sizeof(int) * len);
}

void convertStrToIntArr(string str, int* arr, int len) {
    string::iterator it;
    int i = 0;
    for (it = str.begin(); it < str.end(); it++, i++) {
        arr[i] = valueOf(*it);
    }
};

string convertIntArrToStr(int arr[], int len) {
    char *tmp = new char[len];
    for (int i = 0; i < len; i++) {
        tmp[i] = digitOf(arr[i]);
    }
    string S(tmp);
    return S;
};

void reverseStr(string &str) {
    std::reverse(str.begin(), str.end());
};

void printStrArray(char arr[]) {
    int len = strlen(arr);
    for (int i = 0; i < len; i++) {
        cout << arr[i];
    }
    cout << endl;
};

void printIntArray(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        cout << arr[i];
    }
    cout << endl;
};

void printArrayAsNumber(int arr[], int len) {

    string result = "";
    for (int i = len-1; i >= 0; i--) {
        result.append(1, digitOf(arr[i]));
    }

    cout << trim(result) << endl;
}

void intToString(int number, int base, int arr[]) {
    arr[0] = digitOf(number % base);
    arr[1] = digitOf(number / base);
};

void multiplyArrays(int aArray[], int bArray[], int lenA, int lenB, int base, int rArray[]) {
    int lenTotal = lenA + lenB;
    resetArray(rArray, lenTotal);

    int iArray[lenTotal];
    int *tempArray = new int[lenTotal];
    int carryOver = 0;
    for (int i = 0; i < lenA; i++) {
        carryOver = 0;
        resetArray(iArray, lenTotal);
        int j = 0;
        for (j = 0; j < lenB; j++) {
            int product = aArray[i] * bArray[j] + carryOver;
            iArray[j+i] = product % base;
            carryOver = product / base;
        }
        iArray[j+i] = carryOver;

        // Add iArray to existing rArray
        carryOver = 0;
        for (int k = i; k <= j+i; k++) {
            int product = rArray[k] + iArray[k] + carryOver;
            rArray[k] = product % base;
            carryOver = product / base;
        }
        // cout << j+i << endl;
        rArray[j+i+1] = carryOver;
        // cout << lenA << "," << lenB << "," << j+i << endl;
    }
}

long int milisecond(struct timeval tp){
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    return ms;
};

int main() {
    int T;
    cin >> T;
    int base;
    string V, M, P;
    for (int i = 0; i < T; i++) {
        cin >> base;
        cin >> V;
        cin >> M;
        reverseStr(V);
        reverseStr(M);
        
        lenV = V.length();
        lenM = M.length();
        lenTotal = lenV + lenM;

        int vArray[lenV];
        int mArray[lenM];
        int *rArray = new int[lenTotal];

        resetArray(vArray, lenV);
        resetArray(mArray, lenM);
        resetArray(rArray, lenTotal);

        convertStrToIntArr(V, vArray, lenV);
        convertStrToIntArr(M, mArray, lenM);
        // cout << lenV << lenM << lenTotal << endl;
        multiplyArrays(vArray, mArray, lenV, lenM, base, rArray);
        // printIntArray(rArray, lenTotal);
        printArrayAsNumber(rArray, lenTotal);
    };

    return 0;
}
