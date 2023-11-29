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
struct Food{
    Toado position;
    int age;
    int mark;
    bool isSpecial;
    Food(){}
    Food(int x, int y, int _mark, bool mask){
        position = Toado(x,y);
        mark = _mark;
        isSpecial = mask;
        age = 10000;
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
struct Snake{
    Toado body[255];
    int length;
    int status;
    int stack;
    Food food;
    int mark;
    int _time = 125;
    Snake(){
        srand(time(0));
        length = 3;
        status = 0;
        stack = 0;
        mark = 0;
        body[0] = Toado(10,5);
        body[1] = Toado(11,5);
        body[2] = Toado(12,5);
        show_mark();
    }
    void generate_food(){
        int x = rand() % 75 + 1;
        int y = rand() % 25 + 1;
        for(int i = 0; i<length;i++){
            Toado toado = body[i];
            if(toado.x == x && toado.y == y){
                generate_food();
                return;
            }
        }
        gotoxy(x,y);
        if(stack==5){
            food = Food(x,y,length,1);
            cout<<"$";
            stack = 0;
        }
        else{
            food = Food(x,y,1,0);
            cout<<"#";
        }
    }
     void move(){
        Toado tail = body[0];
        switch(status){
            case 0:
                for(int i = 0; i<length-1;i++){
                    body[i] = body[i+1];
                }
                body[length-1].x++;
                break;
            case 1:
                for(int i = 0; i<length-1;i++){
                    body[i] = body[i+1];
                }
                body[length-1].y--;
                break;
            case 2:
                for(int i = 0; i<length-1;i++){
                    body[i] = body[i+1];
                }
                body[length-1].x--;
                break;
            case 3:
                for(int i = 0; i<length-1;i++){
                    body[i] = body[i+1];
                }
                body[length-1].y++;
                break;
            default:
                status = status % 4;
        }
        if(food.isSpecial){
            food.age -= _time;
            if(food.age<=0){
                gotoxy(70,29);
                cout<<"              ";
                gotoxy(food.position.x,food.position.y);
                cout<<" ";
                generate_food();
            }
            else{
                food.mark = length*(food.age/10000.0 + 1);
                show_specialFoodTime();
            }
        }
        if(body[length-1].x == food.position.x && body[length-1].y == food.position.y){
            eat();
            show_mark();
            for(int i = length - 1; i>0;i--){
                    body[i] = body[i-1];
            }
            body[0] = tail;
        }

    }
    bool check(){
        Toado head = body[length-1];
        if(head.x == 0 || head.x == 76 || head.y == 0 || head.y == 26)
            return false;
        for(int i = 0;i<length-1;i++){
            if(body[i].x == head.x && body[i].y == head.y)
                return false;
        }
        return true;
    }
    void update(){
        int ch;
        int change;
        if (_kbhit()) {
            ch = _getch();
            //100-d 119-w 97-a 115-s
            switch(ch){
                case 100:
                    change = 0;
                    break;
                case 119:
                    change = 1;
                    break;

                case 97:
                    change = 2;
                    break;

                case 115:
                    change = 3;
                    break;
                default:
                    status += 0;

            }
                if((status-change)%2){
                status = change;
                }
        }

    }
    void show(){
        for(int i = 0; i<length-1;i++){
            Toado toado = body[i];
            gotoxy(toado.x, toado.y);
            cout<<"o"<<endl;
        }
        Toado toado = body[length-1];
            gotoxy(toado.x, toado.y);
            cout<<"x"<<endl;
    }
    void show_over(){
        gotoxy(10,10);
        cout<<"Game over!!!\n Your score is "<<mark<<endl;
    }
    void show_mark(){
        gotoxy(70,27);
        cout<<"Score: "<<mark;
        gotoxy(70,28);
        cout<<"Stack:"<<stack;
    }
    void show_specialFoodTime(){
        gotoxy(70,29);
        cout<<"Gift:           ";
        gotoxy(70,29);
        cout<<"Gift: "<<food.age;
    }
    void eat(){
        if(food.isSpecial){
            gotoxy(70,29);
            cout<<"               ";
            mark += food.mark;
            generate_food();
            return;
        }
        length++;
        mark += food.mark;
        stack++;
        generate_food();
    }
    void run(){
        generate_food();
        while(1){
            if(check()){
                show();
                Sleep(_time);
                update();
                gotoxy(body[0].x,body[0].y);
                cout<<" "<<endl;
                move();
            }
            else{
                show();
                show_over();
                break;
                show();
            }
        }
    }
};

int main(){
    draw_frame();
    Snake s = Snake();
    s.run();
}
