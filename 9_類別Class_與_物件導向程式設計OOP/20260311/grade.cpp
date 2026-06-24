#include<iostream>
#include<string>
using namespace std;


class Grade{
    private:
        string name;
        int Chinese;
        int English;
        int Math;
    public:
        Grade(string N,int C, int E, int M) : name{N}, Chinese{C}, English{E}, Math{M}{}
        
        string getName(){
            return name;
        }
        double getAverage(){
            double A=0;
            A = A + Chinese + English + Math;
            return A/3.0;
        }
        char getGrade(){
            if (getAverage()>=90)
                return 'A';
            else if (getAverage()>=80)
                return 'B';
            else if (getAverage()>=70)
                return 'C';
            else if (getAverage()>=60)
                return 'D';
            else
                return 'F';
        }
};



int main(){
    Grade YunYun{"Boy",100,90,80};

    cout<<YunYun.getName()<<endl;
    cout<<YunYun.getAverage()<<endl;
    cout<<YunYun.getGrade()<<endl;


    return 0;
}