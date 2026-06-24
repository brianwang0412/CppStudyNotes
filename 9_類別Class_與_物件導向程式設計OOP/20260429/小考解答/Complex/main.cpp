#include<iostream>
using namespace std;

class Complex{
    friend Complex operator+(Complex& A, Complex& B){
        return Complex(A.rel+B.rel, A.img+B.img);
    }

    friend Complex operator-(Complex& A, Complex& B){
        return Complex(A.rel-B.rel, A.img-B.img);
    }

    public:
        Complex(){}
        Complex(int r, int i)
            :rel{r}, img{i}{}

        int getRel(){return rel;}
        int getImg(){return img;}

        // 等號的過載應為member function
        Complex& operator=(const Complex& right){
            if (this != &right){  // avoid self-assignment
                this->rel = right.rel;
                this->img = right.img;
            }
            return *this;
        }
    private:
        int rel, img;
};


int main(){
    int a1,a2;
    int b1,b2;
    cin>>a1>>a2>>b1>>b2;
    Complex A(a1,a2);
    Complex B(b1,b2);
    Complex C;

    cout<<"A= "<<A.getRel()<<' '<<A.getImg()<<endl;
    cout<<"B= "<<B.getRel()<<' '<<B.getImg()<<endl;
    cout<<"A+B= "<< (A+B).getRel() <<' '<< (A+B).getImg()<<endl;
    cout<<"A-B= "<< (A-B).getRel() <<' '<< (A-B).getImg()<<endl;
    C = A;
    cout<<"C=A, C= "<< C.getRel() <<' '<<C.getImg()<<endl;
}

/*
測資一
輸入:
1 2 3 4

輸出:
A= 1 2
B= 3 4
A+B= 4 6
A-B= -2 -2
C=A, C= 1 2
*/

//Created by B.J.Wang 20260429