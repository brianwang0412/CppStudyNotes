//分糖果

#include<iostream>
using namespace std;

int main(){
    int Candy,Student;
    cin >> Candy;
    cin >> Student;

    int Student_Candy=0,Ass_Candy=0;

    while (Candy>=Student){
        Candy = Candy-Student;
        Student_Candy++;
    }
    Ass_Candy += Candy;
    cout << Student_Candy<<" "<<Ass_Candy;
}

int main(){
    int Candy,Student;
    cin >> Candy >> Student;
    cout << Candy/Student <<" " <<Candy%Student;
}