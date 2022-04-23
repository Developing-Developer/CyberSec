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
double encryptionRSA(int, int, int);
double decryptionRSA(double, int, int);
// double binaryExpansion(double, double, int, vector<int>);
// double binaryExpansion(double, double, int, int);
int power(long long, unsigned int, int);

int main(int argc, char* argv[]){
    string userInput;
    cout<<"Enter plaintext: ";
    cin>>userInput;

    vector<int> nums;
    // vector<int> binaries;
    // // array of binaries used for binary expansion
    // for (int i = 0; i < 21; i++){
    //     binaries.emplace_back(pow(2, i));
    // }
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

    for (int i = 1000; i < 10000; i++){
        // checks for prime
        prime = primeCheck(i);
        // puts prime num into array
        if (prime == true) nums.emplace_back(i);
        if (nums.size() > 19) break;
    }

    // calculate p, q, n, m
    int p = nums.at(9), q = nums.at(18), 
    n = p*q, m = (p-1)*(q-1);
    double e, d;
    int count1 = 1;
    // find e where gcd(e, m) = 1 and e < m
    for (int i = 2; i < m; i++){
        if (__gcd(i, m) == 1) {
            if (primeCheck(i)){
                if (count1 == 3){
                    e = i;
                    // find d where e*d % m == 1 and d < m
                    for (int j = 1; j < m; j++){
                        if (fmod(e*j, m) == 1) {
                            if (primeCheck(j)){
                                d = j;
                                break;
                            }
                        }
                    }
                    break;
                }
                count1++;
            }
        }
    }

    int publicKey[2] = {e, n}, privateKey[3] = {d, p, q};
    cout<<"String: "<<convertedInput<<endl;
    double c = encryptionRSA(stoi(convertedInput), e, n);
    cout<<"Encipher: "<<c<<endl;
    double msg = decryptionRSA(c, d, n);
    cout<<"Decipher: "<<msg;

    return 0;
}

bool primeCheck(int num){
    for (int i = 2; i < num/2; i++){
        if (num % i == 0) return false;
    }
    return true;
}

double encryptionRSA(int m, int e, int n){
    double me;
    // me = binaryExpansion(m, e, n, binaries);
    me = power(m, e, n);
    return me;
}

double decryptionRSA(double c, int d, int n){
    double cd;
    // cd = binaryExpansion(c, d, n, binaries);
    cd = power(c, d, n);
    return cd;
}

// double binaryExpansion(double x, double y, int n, vector<int> binaries){
//     double result = 1, prevResult;
//     double yTemp = y;
//     for (int i = binaries.size() - 1; i >= 0; i--){
//         if (binaries.at(i) <= yTemp){
//             prevResult = result;
//             result *= pow(x, binaries.at(i));
//             if (isinf(result) || result == INFINITY) {
//                 double resultTemp = binaryExpansion(x, binaries.at(i), n, binaries.at(i - 1));
//                 prevResult *= resultTemp;
//                 result = prevResult;
//             }
//             result = fmod(result, n);
//             yTemp -= binaries.at(i);
//         }
//     }
//     return result;
// }

// double binaryExpansion(double x, double y, int n, int binary){
//     double result = 1, prevResult;
//     double yTemp;
    
//     for (yTemp = y; yTemp > 0; yTemp -= binary){
//         prevResult = result;
//         result *= pow(x, binary);
//         if (isinf(result) || result == INFINITY){
//             double resultTemp = binaryExpansion(x, binary, n, binary/2);
//             prevResult *= resultTemp;
//             result = prevResult;
//         }
//         result = fmod(result, n);
//     }
//     // cout<<"Result: "<<result<<endl;
//     return result;
// }

int power(long long x, unsigned int y, int p)
{
    int res = 1;     // Initialize result
 
    x = x % p; // Update x if it is more than or
                // equal to p
  
    if (x == 0) return 0; // In case x is divisible by p;
 
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;
 
        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}