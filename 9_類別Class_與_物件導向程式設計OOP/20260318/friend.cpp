#include<iostream>
using namespace std;

class Count{

    friend void setX(Count &, int);
    //public外的函數不能用this，但friend可以直接存取private內的東西
public:
    int getX() const {
        return x;
    }
    void output();//public內的函數可以用this
private:
    int x{0};
};

void Count::output(){
    cout<<this->x<<endl;
}

//用&c 直接修改c的值
void setX(Count &c, int val){
    c.x = val;
}


int main(){
    Count counter;
    setX(counter, 666);
    counter.output();

}