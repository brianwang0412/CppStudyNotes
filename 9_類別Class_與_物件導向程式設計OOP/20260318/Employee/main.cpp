#include"Employee.h"
#include<string>
#include<iostream>
using namespace std;

int main(){
    Employee MyName{"Brian", "Wang"};
    cout << MyName.getFirstName() << " " << MyName.getLastName() << endl;


    Employee MyName2{};
    MyName2.setFirstName("Paul").setLastName("ShyBoy");
    /*
    由於setFirstName跟setLastName的回傳值為Employee& 即*this 即該物件本身 即MyName2

    所以這行可以看成
    MyName2.setFirstName("Paul").setLastName("ShyBoy");
    
    執行完setFirstName("Paul")後，MyName2.setFirstName("Paul") = MyName2
    MyName2.setLastName("ShyBoy");
    
    */
    cout << MyName2.getFirstName() << " " << MyName2.getLastName() << endl;
}