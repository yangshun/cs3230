/**
    This is a CPP template for CS3230 - Programming Assignment 1 - Part 1
    (January-2015)

    You are not required to follow the template. Feel free to modify any part.

    Comment your code!
**/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char RADIX_POINT = '.';
const int MAX_LEN = 10010;

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

// Trim leading and trailing zeros, and radixpoint
string trim(string aStr) {
    string X = aStr;
    // leading zeros: 000.001
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

void convertStrToArr(string str, char* arr) {
    strcpy(arr, str.c_str());
};

void resetArr(char* arr) {
    for (int i = 0; i < strlen(arr); i++) {
        arr[i] = '0';
    }
}

string convertArrToStr(char arr[]) {
    string S(arr);
    return S;
};

void reverseStr(string &str) {
    std::reverse(str.begin(), str.end());
};

void printArray(char arr[]) {
    for (int i = 0; i < strlen(arr); i++) {
        cout << arr[i];
    }
    cout << endl;
};

void printArrayAsNumber(char arr[]) {
    string sum = convertArrToStr(arr);
    reverseStr(sum);
    cout << trim(sum) << endl;
}

void intToString(int number, int base, char arr[]) {
    arr[0] = digitOf(number % base);
    arr[1] = digitOf(number / base);
};


void copyArrays(char srcArray[], char dstArray[]) {
    for (int i = 0; i < MAX_LEN; i++) {
        dstArray[i] = srcArray[i];
    }
}

void addArrays(char aArray[], char bArray[], int base, char rArray[]) {
    resetArr(rArray);
    int lenA = strlen(aArray);
    int lenB = strlen(bArray);
    int longerLength = lenA > lenB ? lenA : lenB;
    char carryOver = '0';
    for (int i = 0; i < longerLength; i++) {
        int aDigit = valueOf(aArray[i]);
        int bDigit = valueOf(bArray[i]);
        char productAsString[2];
        intToString(aDigit + bDigit + valueOf(carryOver), base, productAsString);
        rArray[i] = productAsString[0];
        carryOver = productAsString[1];
    }
    rArray[longerLength] = carryOver;
}

void multiplyArrays(char aArray[], char bArray[], int base, char rArray[]) {
    resetArr(rArray);
    for (int i = 0; i < strlen(aArray); i++) {
        char carryOver = '0';
        char iArray[MAX_LEN];
        resetArr(iArray);
        int j = 0;
        for (j = 0; j < strlen(bArray); j++) {
            int aDigit = valueOf(aArray[i]);
            int bDigit = valueOf(bArray[j]);
            char productAsString[2];
            intToString(aDigit * bDigit + valueOf(carryOver), base, productAsString);
            iArray[j+i] = productAsString[0];
            carryOver = productAsString[1];
        }

        iArray[j+i] = carryOver;
        char tempArray[MAX_LEN];
        addArrays(rArray, iArray, base, tempArray);
        copyArrays(tempArray, rArray);
    }
}

int main() {
    int T;
    cin >> T;
    int base;
    string V, M, P;
    char vArray[MAX_LEN];
    char mArray[MAX_LEN];
    char rArray[MAX_LEN];
    for (int i = 0; i < T; i++) {
        cin >> base;
        cin >> V;
        cin >> M;
        reverseStr(V);
        reverseStr(M);

        resetArr(vArray);
        resetArr(mArray);
        resetArr(rArray);

        convertStrToArr(V, vArray);
        convertStrToArr(M, mArray);
        multiplyArrays(vArray, mArray, base, rArray);

        printArrayAsNumber(rArray);
    };

    return 0;
}
