#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;

float Trans(float Angel); //角度轉換弳度，寫在在最下面

int main(){
    //  1.pow(a,b)__a的b次方__使用<cmath>
    float A1,A2;
    A1 = pow(2,10); //A1 = 1024 = 2的10次方
    A2 = pow(36,0.5); //A2 = 6 = 36的0.5次方 = 36開根號

    cout<<"pow(2,10) = " << A1 <<endl; //pow(2,10) = 1024
    cout<<"pow(36,0.5) = " << A2 <<endl; //pow(36,0.5) = 6


    cout<<"\n=================="<<"\n\n";//分隔線


    //  2.sqrt(a)__a開根號__使用<cmath>
    float B1,B2,B3;
    B1 = sqrt(16); //B1 = 4 = 16開根號
    B2 = sqrt(2); //B2 = 1.41421 = 2開根號
    B3 = sqrt(-9); //B3 = nan
    //負數開根號未定義

    cout<<"sqrt(16) = "<< B1 <<endl; //sqrt(16) = 4
    cout<<"sqrt(2) = "<< B2 <<endl; //sqrt(2) = 1.41421
    cout<<"sqrt(-9) = "<< B3 <<endl; //sqrt(-9) = nan


    cout<<"\n=================="<<"\n\n";//分隔線


    //  3.abs(a)__a取絕對值__使用<cmath>
    // abs()可用於整數與浮點數取絕對值
    int C1;
    float C2;
    C1 = abs(-123); //C1 = 123 = -123的絕對值
    C2 = abs(-3.14); //C2 = 3.14 = -3.14的絕對值

    cout<<"abs(-123) = "<< C1 <<endl; //abs(-123) = 123
    cout<<"abs(-3.14) = "<< C2 <<endl; //abs(-3.14) = 3.14
    cout<<"(0.1*3-0.3) = "<<fixed<<setprecision(30)<<(0.1*3-0.3);
    //浮點數的誤差值: (0.1*3-0.3) = 0.000000000000000055511151231258
    //0.1*3-0.3不會等於0，因為二進位儲存浮點數會有誤差


    cout<<defaultfloat;
    cout<<"\n=================="<<"\n\n";//分隔線


    //  4.fmod(a,b)__a餘除b(浮點數)__使用<cmath>
    float D1,D2,D3,D4,D5;
    D1 = fmod(7.5, 2); // 7.5餘除2: 7.5-2=5.5 -> 5.5-2=3.5 -> 3.5-2=1.5 -> 1.5<2結束，答案為1.5
    D2 = fmod(7, 2.5);
    D3 = fmod(-7.5, 3.5); 
    //有負號時，先把所有負號去掉，做fmod(7.5, 3.5)，再把「被餘除數」的符號放上去
    //像這裡被除數是-7.5，則答案也會是負的，即-0.5

    D4 = fmod(7.5, -3.5);
    //跟D3一樣，這裡「被餘除數」是7.5，是正的
    //不管後面3.5是正是負，答案一定跟7.5的符號一樣，即0.5

    D5 = fmod(-7.5, -3.5);
    //fmod(7.5, 3.5)=0.5，而-7.5符號為負，則答案為負: -0.5
    
    cout<<"fmod(7.5, 2) = "<<D1<<endl; //fmod(7.5, 2) = 1.5
    cout<<"fmod(7, 2.5) = "<<D2<<endl; //fmod(7, 2.5) = 2
    cout<<"fmod(-7.5, 3.5) = "<<D3<<endl; //fmod(-7.5, 3.5) = -0.5
    cout<<"fmod(7.5, -3.5) = "<<D4<<endl; //fmod(7.5, -3.5) = 0.5
    cout<<"fmod(-7.5, -3.5) = "<<D5<<endl; //fmod(-7.5, -3.5) = -0.5

    //fmod(a)應用: 角度正規化到[0,360)
    float Angel = -450.0;
    Angel = fmod(Angel,360.0); //先做Angel餘除360，確保Angel的值在(-360,360)內
    if (Angel < 0) Angel+=360; 
    cout<<"normalize Angel -450 -> "<<Angel<<endl;


    cout<<"\n=================="<<"\n\n";//分隔線


    //  5.向下取整floor(a), 向上取整ceil(a), 捨去小數trunc(a), 四捨五入round(a)
    float E1,E2,E3,E4,E5,E6,E7,E8;
    E1 = floor(2.9); //2.9向下取整，小於2.9的最大整數為2，故floor(2.9)=2
    E2 = floor(-2.9); //-2.9向下取整，小於-2.9小的最大整數為-3，故floor(-2.9)=-3

    E3 = ceil(2.1); //2.1向上取整，大於2.1的最小整數為3，故ceil(2.1)=3
    E4 = ceil(-2.1); //-2.1向上取整，大於-2.1的最小整數為-2，故ceil(-2.1)=-2

    E5 = trunc(1234.5678); //直接捨去小數部分，trunc(1234.5678)=1234

    E6 = round(2.3); //2.3四捨五入後為2，round(2.3)=2
    E7 = round(2.5); //2.5四捨五入後為3，round(2.5)=3
    E8 = round(2.7); //2.7四捨五入後為3，round(2.7)=3

    cout<<"floor(2.9) = "<<E1<<endl;         //floor(2.9) = 2
    cout<<"floor(-2.9) = "<<E2<<endl;        //floor(-2.9) = -3
    cout<<"ceil(2.1) = "<<E3<<endl;          //ceil(2.1) = 3
    cout<<"ceil(-2.1) = "<<E4<<endl;         //ceil(-2.1) = -2
    cout<<"trunc(1234.5678) = "<<E5<<endl;   //trunc(1234.5678) = 1234
    cout<<"round(2.3) = "<<E6<<endl;         //round(2.3) = 2
    cout<<"round(2.5) = "<<E7<<endl;         //round(2.5) = 3
    cout<<"round(2.7) = "<<E8<<endl;         //round(2.7) = 3


    cout<<"\n=================="<<"\n\n";//分隔線


    //  6.畢氏定理hypot(a,b)__使用<cmath>
    float F1,F2;
    F1 = hypot(3,4); 
    //F1 = hypot(3,4) = √(3**2 + 4**2) = 5
    //畢氏定理，z=√(x**2+y**2)，3比4比5
    F2 = hypot(1,sqrt(3));
    //F2 = hypot(1,sqrt(3)) = √(1**2 + √3) = 2
    //畢氏定理，z=√(x**2+y**2)，1比√3比2

    cout<<"hypot(3,4) = "<<F1<<endl; //hypot(3,4) = 5
    cout<<"hypot(1,sqrt(3)) = "<<F2<<endl; //hypot(1,sqrt(3)) = 2


    cout<<"\n=================="<<"\n\n";//分隔線


    //  7.角度轉換弳度
    //  公式: 弳度 = 角度 * (圓周率 / 180)
    //  自訂函式 Radian() 在最下面

    constexpr double PI = 3.1415926535897323846;
    //const: 在程式執行時才會確定值
    //constexpr: 在編譯器編譯時就會確定值
    //故constexpr一定不會用到程式執行時才能用的函式，如<cmath>的pow()，因為#include<cmath>是程式執行時才會做的
    //can do: constexpr float MyNumber=123.456;
    //can't do: constexpr float MyNumber=pow(2,10);

    // 公式: 弳度 = 角度 * (圓周率 / 180)
    float Radian;
    Angel=30.0;
    Radian = Angel * (PI / 180.0);
    cout<<fixed<<setprecision(1);
    cout<<"sin30 degree = "<<sin(Radian)<<endl; //sin30 degree = 0.5
    cout<<"cos60 degree = "<<cos(60*(PI/180.0))<<endl; //cos60 degree = 0.5


    cout<<"\n=================="<<"\n\n";//分隔線


    //  8.三角函數sin(a),cos(a),tan(a),asin(a),acos(a),atan(a),atan2(a,b)__使用<cmath>
    //  在使用三角函數的函式時，要先將角度轉換成弳度，Randian=Trans(Angel)，Trans是我自己寫的轉換函數
    float H1_1,H1_2,H1_3,H1_4,H2,H3,H4,H5,H6,H7;
    float Angel1=30, Angel2=60, Angel3=210, Angel4=240, Angel5=390;
    float Radian1=Trans(Angel1), Radian2=Trans(Angel2), Radian3=Trans(Angel3), 
    Radian4=Trans(Angel4), Radian5=Trans(Angel5), Radian6=Trans(-Angel1);

    H1_1 = sin(Radian1); // H1_1 = sin30° = 0.5 = 1/2
    H1_2 = sin(Radian3); // H1_2 = sin210° = -0.5 = -1/2
    H1_3 = sin(Radian5); // H1_3 = sin390° = sin30° = 1/2，角度大於360°可以直接用
    H1_4 = sin(Radian6); // H1_4 = sin-30° = -0.5，角度是負的也可以
    H2 = cos(Radian2); // H2 = cos60° = 0.5 = 1/2
    H3 = tan(Radian2); // H3 = tan60° = ✓3/1 = ✓3 ≓ 1.732

    H4 = asin(H1_1); // H4 = asin(0.5) = Trans(30°)
    //給定一個正弦值0.5，asin會回傳它對應的角度的弳度，0.5=sin(30°)，asin(0.5)=Trans(30°)

    H5 = acos(H2);   // H5 = acos(0.5) = Trans(60°)
    //給定一個餘弦值0.5，acos會回傳它對應的角度的弳度，0.5=cos(60°)，acos(0.5)=Trans(60°)

    H6 = atan(H3);   // H6 = atan(1.732) = Trans(60°)
    //給定一個正切值1.7321，atan會回傳它對應的角度的弳度，1.7321=tan(60°)，atan(1.732)=Trans(60°)

    H7 = atan2(1,1); // H7 = 直角坐標(1,1)與正x軸的夾角(以弳度表示) = Trans(45°)

    cout<<setprecision(1);
    cout<<"sin30 degree = "<<H1_1<<endl;  //sin30 degree = 0.5
    cout<<"sin210 degree = "<<H1_2<<endl; //sin210 degree = -0.5
    cout<<"sin390 degree = "<<H1_3<<endl; //sin390 degree = 0.5
    cout<<"sin-30 degree = "<<H1_4<<endl; //sin-30 degree = -0.5
    cout<<"cos60 degree = "<<H2<<endl;    //cos60 degree = 0.5
    cout<<"tan60 degree = "<<H3<<endl;    //tan60 degree = 1.7

    cout<<"asin("<<H1_1<<") = "<<H4<<" radians = sin"<<Angel1<<" degree"<<endl;
    //asin(0.5) = 0.5 radians = sin30.0 degree

    cout<<"acos("<<H2<<") = "<<H5<<" radians = cos"<<Angel2<<" degree"<<endl;
    //acos(0.5) = 1.0 radians = cos60.0 degree

    cout<<"atan("<<H3<<") = "<<H6<<" radians = tan"<<Angel2<<" degree"<<endl;
    //atan(1.7) = 1.0 radians = tan60.0 degree

    cout<<setprecision(3);
    cout<<"atan2(1,1) = "<<H7<<" radians = 45 degree"<<endl;
    //atan2(1,1) = 0.785 radians = 45 degree


    cout<<"\n=================="<<"\n\n";//分隔線


    //  9.隨機取數rand()__使用<cstdlib>和<ctime>
    //  srand() : 設定取樣碼
    //  rand() : 隨機輸出0~32767之間的數字(RAND_MAX=32767)
    

    srand(static_cast<unsigned int>(time(0))); //將srand取樣碼隨時間做變化
    //若題目有給seed，就改成srand(seed);

    for(int i = 0 ; i < 5 ; i++){
        cout<<(rand() % 100 + 1)<< endl; //隨機輸出1~100的整數5次
    }
    /*
    要讓隨機數位於1~100之間，先算出有(100-1+1)=100個數字，最小值為1
    則程式為: rand() % 100 + 1
    
    公式: rand()%(最大值 - 最小值 + 1) + 最小值
    */
}


//角度轉換為弳度
//<cmath>有內建的圓周率 M_PI，可以直接拿來用，不用自己寫
float Trans(float Angel){
    return Angel*(M_PI/180.0); 
}

//本篇筆記參考嘉義大學資訊工程學系許政穆老師的授課內容與講義
//Created by B.J.Wang 2025/11/13