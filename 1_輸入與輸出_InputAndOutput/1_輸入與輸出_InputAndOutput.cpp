#include<iostream> //for cin,cout
#include<cstdio> //scanf,printf
#include<string> //非常好用，建議用cin,cout處理string，比較簡單
using namespace std;

//請在執行程式後看著註解練習輸入與輸出

int main(){
    int a,b,c;
    //先宣告三個變數a,b,c，它們的型態都是int(數值)，只能儲存整數

    //《cin & cout》
    
    cout << "Please input some number>>";
    cin >> a; //輸入一個數，例如：123，按下Enter後123會被儲存到a這個變數內
    cin >> b >> c; //輸入兩個數，例如：100 200，中間隔一個空格
    //也可以先輸入完100，按下Enter後再輸入200

    cout << c <<' '<< 123 <<' '<< 'a' <<' '<< "Hello World" << endl;
    //範例輸出: 200 123 a Hello World
    //cout在輸出單個字元時要用單引號''括起來，字串(多個字元)則需要用雙引號""


    string F,G; //字串，string可以儲存文字資料(如英文字、符號等)
    cin >> F; //輸入一串字
    cout << F << endl;
    //範例輸入:Good
    //範例輸出:Good

    //getline(cin,G); 
    //getline可以儲存整串字串(包含空格)，例如輸入Very Good，G可以完整接收到Very Good
    //但是!getline不能跟cin混用，cin輸入結束後會暫存一個換行符號，getline檢測到換行符號會直接結束輸入



    //上課常用資料型態整理

    int A=123; //整數，用%d
    float B=3.1415926; //浮點數，用%f，若要指定輸出到小數點後幾位，例如輸出到小數點第二位，則用%.2f
    char C='Z'; //單一字元，用%c，只能儲存單一字元，用單引號括起來
    char D=65; //單一字元(ASCII)，用%c，這裡的65代表的是ASCII編碼中的'A'
    char E[3]="Hi"; //字串，用%s，可儲存多個字元，記得預留一個位子給'\0'，表示字串的終止，內部為{'H','i,','\0'}
    //也可以直接E[]="Hi"，讓電腦自動分配記憶體


    //《scanf & printf》
    printf("%d %.5f %c %c %s \n",A,B,C,D,E);
    //範例輸出: 123 3.14159 Z A Hi

    printf("Please input: (integer) (float number) (one character) (two word string) >> "); 
    
    scanf("%d %f %c %s",&A,&B,&C,E); 
    //範例輸入: 123 1.414 a No

    //用scanf儲存變數時，要使用該變數對應的符號(如int對應%d)，並指定變數的記憶體位置(&A)
    //E[3]="Hi"這個比較特別，E本身就已退化為指標並指向陣列的第一個元素位置(E[0])
    printf("%d %f %c %s",A,B,C,E);
    //範例輸出: 123 1.414 a No


    return 0;
}


//補充
//endl能讓輸出換行('\n')，並將暫存在輸出緩衝區內的文字立即輸出(flush)
//使用endl會比直接輸出'\n'稍微慢一點，追求運行效率建議直接用'\n'換行就行

//本筆記由ChatGPT贊助播出
//有建議或發現錯誤歡迎跟我講
//Create by B.J.Wang 2025/9/15