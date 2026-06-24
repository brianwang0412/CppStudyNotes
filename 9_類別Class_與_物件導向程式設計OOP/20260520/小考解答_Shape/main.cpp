#include<iostream>
#include<iomanip>
using namespace std;

class Shape{
    public:
        Shape(){} //可省略
        virtual ~Shape()=default;
        virtual double area() const =0;
};

class Circle : public Shape{
    private:
        double r;
    public:
        Circle(){} //可省略
        virtual ~Circle()=default; //可省略
        virtual double area() const override{
            return 3.14159*r*r;
        }
    friend istream& operator>>(istream& input, Circle& C){
        input>>C.r;
        return input;
    }
    friend ostream& operator<<(ostream& output, const Circle& C){
        output<<"Circle"<<fixed<<setprecision(2)
              <<"\nradius: "<<C.r
              <<"\narea: "<<C.area()<<'\n';
        return output;
    }
};

class Rectangle : public Shape{
    private:
        double w,h;
    public:
        Rectangle(){} //可省略
        virtual ~Rectangle()=default; //可省略
        virtual double area() const override{
            return w*h;
        }
    friend istream& operator>>(istream& input, Rectangle& R){
        input>>R.w>>R.h;
        return input;
    }
    friend ostream& operator<<(ostream& output, const Rectangle& R){
        output<<"Rectangle"<<fixed<<setprecision(2)
              <<"\nwidth: "<<R.w
              <<"\nheight: "<<R.h
              <<"\narea: "<<R.area()<<'\n';
        return output;
    }
};

class Square : public Shape{
    private:
        double s;
    public:
        Square(){} //可省略
        virtual ~Square()=default; //可省略
        virtual double area() const override{
            return s*s;
        }
    friend istream& operator>>(istream& input, Square& S){
        input>>S.s;
        return input;
    }
    friend ostream& operator<<(ostream& output, const Square& S){
        output<<"Square"<<fixed<<setprecision(2)
              <<"\nside: "<<S.s
              <<"\narea: "<<S.area()<<'\n';
        return output;
    }
};

class Triangle : public Shape{
    private:
        double b,h;
    public:
        Triangle(){} //可省略
        virtual ~Triangle()=default; //可省略
        virtual double area() const override{
            return b*h/2;
        }
    friend istream& operator>>(istream& input, Triangle& T){
        input>>T.b>>T.h;
        return input;
    }
    friend ostream& operator<<(ostream& output, const Triangle& T){
        output<<"Triangle"<<fixed<<setprecision(2)
              <<"\nbase: "<<T.b
              <<"\nheight: "<<T.h
              <<"\narea: "<<T.area()<<'\n';
        return output;
    }
};


int main() {
    int n;
    int type;

    cin >> n;

    Shape** shapes = new Shape*[n];

    for (int i = 0; i < n; i++) {
        cin >> type;

        switch (type) {
            case 1: {
                Circle* c = new Circle();
                cin >> *c;
                shapes[i] = c;
                break;
            }
            case 2: {
                Rectangle* r = new Rectangle();
                cin >> *r;
                shapes[i] = r;
                break;
            }
            case 3: {
                Triangle* t = new Triangle();
                cin >> *t;
                shapes[i] = t;
                break;
            }
            case 4: {
                Square* s = new Square();
                cin >> *s;
                shapes[i] = s;
                break;
            }
            default: {
                shapes[i] = nullptr;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (Circle* c = dynamic_cast<Circle*>(shapes[i])) {
            cout << *c;
        }
        else if (Rectangle* r = dynamic_cast<Rectangle*>(shapes[i])) {
            cout << *r;
        }
        else if (Triangle* t = dynamic_cast<Triangle*>(shapes[i])) {
            cout << *t;
        }
        else if (Square* s = dynamic_cast<Square*>(shapes[i])) {
            cout << *s;
        }

        if (i != n - 1) {
            cout << endl;
        }
    }

    for (int i = 0; i < n; i++) {
        delete shapes[i];
    }

    delete[] shapes;

    return 0;
}

/*
測資一
輸入:
4
1 3
2 4 5
3 10 6
4 7

輸出:
Circle
radius: 3.00
area: 28.27

Rectangle
width: 4.00
height: 5.00
area: 20.00

Triangle
base: 10.00
height: 6.00
area: 30.00

Square
side: 7.00
area: 49.00

測資二
輸入:
3
4 5
1 2.5
2 6 8

輸出:
Square
side: 5.00
area: 25.00

Circle
radius: 2.50
area: 19.63

Rectangle
width: 6.00
height: 8.00
area: 48.00

測資三
輸入:
5
3 8 4
4 10
1 1.5
2 3 9
3 12 5

輸出:
Triangle
base: 8.00
height: 4.00
area: 16.00

Square
side: 10.00
area: 100.00

Circle
radius: 1.50
area: 7.07

Rectangle
width: 3.00
height: 9.00
area: 27.00

Triangle
base: 12.00
height: 5.00
area: 30.00
*/

//已AC
//本篇筆記為嘉義大學資訊工程學系大一OOP的上機考題目
//Created by B.J.Wang 20260520
//最後更新 20260523 解構子加上=default