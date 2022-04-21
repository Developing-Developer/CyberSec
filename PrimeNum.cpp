#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){
    vector<int> nums;
    bool prime;

    for (int i = 1000; i < 10000; i++){
        prime = true;
        // checks for prime, if not prime break out of loop
        for (int j = 2; j < i/2; j++){
            if (i % j == 0) {
                prime = false;
                break;
            }
        }
        // puts prime num into array
        if (prime == true) nums.emplace_back(i);
        if (nums.size() > 19) break;
    }

    // get 10th and 19th prime nums
    cout<<nums.at(9)<<endl;
    cout<<nums.at(18);
    return 0;
}