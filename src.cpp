#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct Toado{
    int x, y;
    Toado(){
    }
    Toado(int a, int b){
        x = a;
        y = b;
    }
};
void draw_frame(){
    int row = 27;
    int col = 77;
    //27-2 = 25; 77 - 2 = 75
    for(int j =0; j<col;j++){
            cout<<"_";
        }
    cout<<endl;
    for(int i = 1;i<row-1;i++){
        for(int j =0; j<col;j++){
            if(j==0||j==col-1)
                cout<<"|";
            else cout<<" ";
        }
        cout<<endl;
    }
    for(int j = 0; j<col;j++){
            cout<<"*";
        }

}

int main(){
    draw_frame();
}
