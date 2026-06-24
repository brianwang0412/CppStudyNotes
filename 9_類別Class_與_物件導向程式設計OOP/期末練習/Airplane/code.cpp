#include<iostream>
using namespace std;

// 作答區啟始
#include<string>

class Airplane{
    protected:
        int x,y;
    public:
        virtual string name(){
            return "Airplane";
        }
        void moveTo(int newX, int newY){
            x = newX;
            y = newY;
        }
        void draw(){
            cout<<name()<<" at ("<<x<<", "<<y<<")"<<'\n';
        }
};

class Fighter : public Airplane{
    public:
        virtual string name() override{
            return "Fighter";
        }
};

class Transport : public Airplane{
    public:
        virtual string name() override{
            return "Transport";
        }
};

class Tanker : public Airplane{
    public:
        virtual string name() override{
            return "Tanker";
        }
};

class Recon : public Airplane{
    public:
        virtual string name() override{
            return "Recon";
        }
};
//作答區結束

int main() {
    int n;
    int type;
    int x;
    int y;

    cin >> n;

    Airplane** objlist = new Airplane*[n];

    for (int i = 0; i < n; i++) {
        cin >> type >> x >> y;

        switch (type) {
        case 1:
            objlist[i] = new Fighter();
            break;
        case 2:
            objlist[i] = new Transport();
            break;
        case 3:
            objlist[i] = new Tanker();
            break;
        case 4:
            objlist[i] = new Recon();
            break;
        default:
            objlist[i] = new Airplane();
            break;
        }

        objlist[i]->moveTo(x, y);
    }

    return 0;
}

// 本篇筆記為嘉義大學資訊工程學系物件導向程式設計之課堂題目
// //Created by B.J.Wang 20260609