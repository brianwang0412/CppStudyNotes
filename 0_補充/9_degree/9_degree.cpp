// https://zerojudge.tw/ShowProblem?problemid=d672

#include<iostream>
#include<string>
using namespace std;

int digitSum(const string& N){  
    int sum = 0;
    for (char c : N){   //就像Python的 for c in N:
        sum += c - '0';
    }
    return sum;
}

int main(){
    string N;
    while (cin >> N && N != "0"){
        int sum = digitSum(N);
        int degree = 1;
        
        while (sum >= 10){
            sum = digitSum(to_string(sum));
            degree++;
        }
        
        if (sum == 9) {
            cout << N << " is a multiple of 9 and has 9-degree " << degree << "." << '\n';
        } 
        else {
            cout << N << " is not a multiple of 9." << '\n';
        }
    }
    return 0;
}


//參考 https://hackmd.io/@LukeTseng/HkU-_p2Ulg#34-2-the-9s