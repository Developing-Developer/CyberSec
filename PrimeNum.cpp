/*
* RSA Crypto System
* C++14
*/
#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

// function declarations
bool primeCheck(int);
double encryptionRSA(int, int, int, vector<int>);
double decryptionRSA(double, int, int, vector<int>);
double binaryExpansion(double, double, int, vector<int>);

int main(int argc, char* argv[]){
    string userInput;
    cout<<"Enter plaintext: ";
    cin>>userInput;

    vector<int> nums;
    vector<int> binaries;
    // int binaries[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    for (int i = 0; i < 21; i++){
        binaries.emplace_back(pow(2, i));
    }
    bool prime;
    map<char, string> letters;
    int count = 0;
    // map of all letters to values (0-25)
    for (char alphabet = 'a'; alphabet <= 'z'; alphabet++){
        letters.insert(pair<char, string>(alphabet, to_string(count)));
        count++;
    }

    // convert userinput to numbers using mapped letters
    string convertedInput;
    for (int i = 0; i < userInput.length(); i++){
        convertedInput += letters.find(userInput[i])->second;
    }
    // string to int stoi(string)


    for (int i = 1000; i < 10000; i++){
        // checks for prime
        prime = primeCheck(i);
        // puts prime num into array
        if (prime == true) nums.emplace_back(i);
        if (nums.size() > 19) break;
    }

    // calculate p, q, n, m
    int p = nums.at(9), q = nums.at(18), n = p*q, m = (p-1)*(q-1);
    int e, d;
    // find lowest e where gcd(e, m) = 1 and e < m
    for (int i = 2; i < m; i++){
        if (__gcd(i, m) == 1) {
            if (primeCheck(i)){
                e = i;
                break;
            }
        }
    }

    // find d where e*d % m == 1 and d < m
    for (int j = 1; j < m; j++){
        if ((e*j % m) == 1) {
            d = j;
            break;
        }
    }
    // cout<<"e: "<<e<<endl;
    // cout<<"d: "<<d<<endl;
    int publicKey[2] = {e, n}, privateKey[3] = {d, p, q};
    cout<<"String: "<<convertedInput<<endl;
    double c = encryptionRSA(stoi(convertedInput), e, n, binaries);
    double msg = decryptionRSA(c, d, n, binaries);
    cout<<"Decipher: "<<msg;

    return 0;
}

bool primeCheck(int num){
    for (int i = 2; i < num/2; i++){
        if (num % i == 0) return false;
    }
    return true;
}

double encryptionRSA(int m, int e, int n, vector<int> binaries){
    // binary expand e, multiply (base^expanded e % n) together
    // 4^3 % 5 == (4^0 % 5) * (4^1 % 5)
    // 2^0 + 2^1 = 3
    double me;
    me = binaryExpansion(m, e, n, binaries);
    cout<<"M^e: "<<me<<endl;
    return me;
}

double decryptionRSA(double c, int d, int n, vector<int> binaries){
    double cd;
    cout<<"C: "<<c<<" D: "<<d<<endl;
    cd = binaryExpansion(c, d, n, binaries);
    return cd;
}

double binaryExpansion(double x, double y, int n, vector<int> binaries){
    double result = 1;
    
    double yTemp = y;
    for (int i = binaries.size() - 1; i >= 0; i--){
        if (binaries.at(i) <= yTemp){
            result *= pow(x, binaries.at(i));
            cout<<"Result: "<<result<<endl;
            result = fmod(result, n);
            yTemp -= binaries.at(i);
        }
    }
    return result;
}