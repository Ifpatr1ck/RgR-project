#include <iostream>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <cmath>
using namespace std;
//#define UP 72;
//#define DOWN 80;
//#define ESC 27;
//#define ENTER 13;
double e = 2.71828182845904523536;
double Pi = 3.1415926535;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
HPEN CreatePen(int fnPenStyle,int nWidth,COLORREF crColor);
void gotoxy(int xpos, int ypos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
} // No Lags with moving between menu numbers
void setcur(int x, int y)//установка курсора на позицию  x y 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};
void ConsoleCursorVisible(bool show, short size)
{
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show;
    structCursorInfo.dwSize = size;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}
HWND hwnd = GetConsoleWindow(); //Descripter of Window
HDC dc = GetDC(hwnd);//Device context - for drawing
void tablica()
{
    int n = 20,x2 = 5, y2 = 0;;
    double F1[20], F2[20], x, dx, x1[20], a = 0, b = 2*Pi, minF1 = INT_MAX, maxF1 = INT_MIN, minF2 = INT_MAX, maxF2 = INT_MIN;
    dx = fabs(b - a) / (n - 1);
    x = x1[0] = a;
    gotoxy(x2, y2);
    printf(" ______________________________\n");
    gotoxy(x2, y2 + 1);
    printf("| I |    X   |   F1   |   F2   | \n");
    gotoxy(x2, y2 + 2);
    printf("|___|________|________|________|\n");
    for (int i = 0; i < n; i++) {
        F1[i] = 5 - 3*cos(x);
        F2[i] = sqrt(pow(e,x)-1);
        x1[i] = x;
        x += dx;
    }
    for (int i = 0; i < n; i++) {
        minF1 = min(F1[i], minF1);
        maxF1 = max(F1[i], maxF1);
        if (F2[i] != -INFINITY) minF2 = min(F2[i], minF2);
        maxF2 = max(F2[i], maxF2);
    }
    for (int i = 1; i <= n; i++) {
        gotoxy(x2, y2 + 2 + i);
        SetConsoleTextAttribute(hStdOut, 11);
        printf("|%3d|%8.3f|", i, x1[i - 1]);
        if (F1[i - 1] == minF1) {
            SetConsoleTextAttribute(hStdOut, 4);
            printf("%8.4f", F1[i - 1]);
        }
        else if (F1[i - 1] == maxF1) {
            SetConsoleTextAttribute(hStdOut, 2);
            printf("%8.4f", F1[i - 1]);
        }
        else
        {
            SetConsoleTextAttribute(hStdOut, 11);
            printf("%8.4f", F1[i - 1]);
        }
        SetConsoleTextAttribute(hStdOut, 11);
        printf("|");
        if (F2[i - 1] == minF2) {
            SetConsoleTextAttribute(hStdOut, 4);
            printf("%8.4f", F2[i - 1]);
        }
        else if (F2[i - 1] == maxF2) {
            SetConsoleTextAttribute(hStdOut, 2);
            printf("%8.4f", F2[i - 1]);
        }
        else
        {
            if (F2[i - 1] == -INFINITY) {
                SetConsoleTextAttribute(hStdOut, 11);
                printf("%8s", "ERROR");
            }
            else {
                SetConsoleTextAttribute(hStdOut, 11);
                printf("%8.4f", F2[i - 1]);
            }
        }
        SetConsoleTextAttribute(hStdOut, 11);
        printf("|\n");
    }
    gotoxy(x2, y2 + 3 + n);
    cout << "|___|________|________|________| \n";
}
void Charts() {
    HWND hwn = GetConsoleWindow();
    COLORREF lineColor = RGB(0, 0, 0);
    HDC hdc = GetDC(hwn);
    const int d = 270, k = 100, x0 = 50, y0 = 270, c = 50;
    SelectObject(hdc, CreatePen(0, 1, RGB(255, 255, 255)));
    MoveToEx(hdc, 0, d, NULL);
    LineTo(hdc, c * k, d);
    MoveToEx(hdc, c, 0, NULL);
    LineTo(hdc, c, 3 * d);
    for (int i = 0; i < 30; i++) {
        MoveToEx(hdc, x0 - 10, y0 - k * i, NULL);
        LineTo(hdc, x0 + 10, y0 - k * i);
        MoveToEx(hdc, x0 - 10, y0 + k * i, NULL);
        LineTo(hdc, x0 + 10, y0 + k * i);
        MoveToEx(hdc, x0 + k * i, y0 - 10, NULL);
        LineTo(hdc, x0 + k * i, y0 + 10);
        MoveToEx(hdc, x0 - k * i, y0 - 10, NULL);
        LineTo(hdc, x0 - k * i, y0 + 10);
        string s = to_string(i);
        LPCWSTR w;
        wstring ste = wstring(s.begin(), s.end());
        w = ste.c_str();
        if (i < 10) {
            TextOut(hdc, x0 - 10, y0 - k * i, w, 1);
            TextOut(hdc, x0 + k * i, y0 + 10, w, 1);
        }
        else {
            TextOut(hdc, x0 - 10, y0 - k * i, w, 2);
            TextOut(hdc, x0 + k * i, y0 + 10, w, 2);
        }
        LPCWSTR w1 = L"3^(-x) / 50";
        LPCWSTR w2 = L"x * e^(-x) + ln(x)";
        TextOut(hdc, 460, 80, w1, 11);
        TextOut(hdc, 360, 240, w2, 18);
    }
    int n = 20000;
    double F1[20000], F2[20000], x1[20000], x, dx, a = 0, b = 5, minF1 = 10000, maxF1 = -10000, minF2 = 10000, maxF2 = -10000;
    dx = fabs(b - a) / (n - 1);
    x = a;
    for (int i = 0; i < n; i++) {
        F1[i] = pow(3, -x) / 50;
        F2[i] = x * exp(-x) + log(x);
        x1[i] = x;
        x += dx;
    }
    for (int i = 0; i < n; i++) {
        SetPixel(hdc, c + k * x1[i], d - k * F2[i], RGB(64, 224, 208));
        MoveToEx(hdc, c + k * x1[i], d - k * F2[i], NULL);
        SetPixel(hdc, c + k * x1[i], d - k * F1[i], RGB(0, 255, 127));
        MoveToEx(hdc, c + k * x1[i], d - k * F1[i], NULL);
    }
}
double FunctionEquation(double x) {
    return tan(x) - pow(e, x + 1);
}
double HalfDivEquation(double a, double b, double e) {
    double c;
    do {
        c = (a + b) / 2;
        if (FunctionEquation(c) * FunctionEquation(a) < 0)  b = c;
        else if (c == 0) return 0;
        else a = c;
    } while (fabs(a - b) >= e);
    return c;
}//Solving the Equation by the Half-devision Method
void AboutME() {
    gotoxy(30, 1);
    cout << "  Расчётно-графическую работу" << endl;
    gotoxy(30, 2);
    cout << "выполнил студент группы ПИН-221" << endl;
    gotoxy(30, 3);
    cout << "    Кит Денис Владимирович" << endl;
} //Function, which can talking about author
double FunctionIntegral(double x) {
    return pow(e, (-x)) * log(x + 1);
}// Function of Integral
double trapezoidalIntegral(double a, double b, int n) {
    const double width = (b - a) / n;
    double trapezoidal_integral = 0;
    for (int i = 0; i < n; i++) {
        const double x1 = a + i * width;
        const double x2 = a + (i + 1) * width;

        trapezoidal_integral += 0.5 * (x2 - x1) * (FunctionIntegral(x1) + FunctionIntegral(x2));
    }
    return trapezoidal_integral;
} //Solving the Integral by the trapezoid method    
double rectangelIntegral(double a, double b, int n)
{
    double INTGRL = 0.0;
    double h = double((b - a) / n);
    for (double x = a; x <= b; x += h)
        INTGRL += FunctionIntegral(x - h / 2);
    INTGRL *= h;
    return INTGRL;
} //Solving the Integral by the rectangel method
double Equation(int x)
{
    return tan(x) - pow(e,x+1);
} // Equation
double HordEquation(double a, double b, double c)
{
    while (fabs(Equation(b)) > c)
    {
        a = b - ((b - a) * Equation(b)) / (Equation(b) - Equation(a));
        b = a - ((a - b) * Equation(a)) / (Equation(a) - Equation(b));
    }
    return b;
} //Solving the Equation by the chord Method #1
double Trapeze(double a, double b, double n) {
    double h = (b - a) / n;
    double sum = FunctionIntegral(a) + FunctionIntegral(b);
    for (int i = 1; i <= n - 1; i++) {
        sum += 2 * FunctionIntegral(a + i * h);
    }
    sum *= h / 2;
    return sum;
} //Trapezoidal method
double Sympson(double a, double b, double n) {
    double h = (b - a) / n;
    double sum = FunctionIntegral(a) + FunctionIntegral(b);
    int k;
    for (int i = 1; i <= n - 1; i++) {
        k = 2 + 2 * (i % 2);
        sum += k * FunctionIntegral(a + i * h);
    }
    sum *= h / 3;
    return sum;
} // Sympson's method // not need
void BackGround()
{
    SelectObject(dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(dc, RGB(150, 205, 80)); // - цвет заполнителя
    Rectangle(dc, 0, 0, 800, 400);
} // Background of Animation 
void Animation()
{
    system("mode con cols=100 lines=25");
    int x = 0, y = 0, N = 0, R = 0, G = 133, B = 0;
    for (int i = 0; GetKeyState(VK_ESCAPE) >= 0; i++)
    {
        int PointWidth1 = 0, PointHigh1 = 0, PointWidth2 = 100 + N, PointHigh2 = 100 + N / 4,
            Speed = 20;
        if (x == 0 && y == 0)
        {
            for (int j = 0; j <= 800 - PointWidth2; j += Speed)
            {
                BackGround();
                //running rectangle
                SelectObject(dc, GetStockObject(DC_BRUSH));
                SetDCBrushColor(dc, RGB(R, G, B)); // - Color of placeholder
                Rectangle(dc, PointWidth1 + j, PointHigh1, PointWidth2 + j, PointHigh2);
                Sleep(10);
            }
            y++;
        } // Animation of moving left to right
        if (x == 0 && y == 1)
        {
            for (int k = 0; k <= 400 - PointHigh2; k += Speed)
            {
                BackGround();
                //running rectangle
                SelectObject(dc, GetStockObject(DC_BRUSH));
                SetDCBrushColor(dc, RGB(R, G, B)); // - Color of placeholder
                Rectangle(dc, 800 - PointWidth2, PointHigh1 + k, 800, PointHigh2 + k);
                Sleep(10);
            }
            x++;
        }// Animation of moving upper to bottom
        if (x == 1 && y == 1)
        {
            for (int j = 0; j <= 800 - PointWidth2; j += Speed)
            {
                BackGround();
                //running rectangle
                SelectObject(dc, GetStockObject(DC_BRUSH));
                SetDCBrushColor(dc, RGB(R, G, B)); // - Color of placeholder
                Rectangle(dc, 800 - PointWidth2 - j, 400 - PointHigh2, 800 - j, 400);
                Sleep(10);
            }
            y--;
        } // Animation of moving right to left
        if (x == 1 && y == 0)
        {
            int j = 0;
            for (; j < 400 + Speed - PointHigh2; j += Speed)
            {
                BackGround();
                //running rectangle
                SelectObject(dc, GetStockObject(DC_BRUSH));
                SetDCBrushColor(dc, RGB(R, G, B)); // - Color of placeholder
                Rectangle(dc, PointWidth1, 400 - PointHigh2 - j, PointWidth2, 400 - j);
                Sleep(10);
                if (j >= (400 - PointHigh2)) N += 100;
            }
            x--;
        } // Animation of moving bottom to upper
        if (PointWidth2 >= 800 && PointHigh2 >= 400) break;
    }
} // Animation of start the programm
class Menu
{
public:
    int Num = 0; // номер нажатой клавиши 
    int Punckt = 0; // пункты 1-5
    void draw(int num)
    {
        switch (num)
        {
        case 80: // стрелка вниз
            if (Punckt >= 5) Punckt = 1;
            else Punckt++;
            break;
        case 72: // стрелка вверх
            if (Punckt <= 1) Punckt = 5;
            else Punckt--;
            break;
        default:
            break;
        }
        // drawing menu
        setcur(0, 0);
        system("cls");
        system("COLOR 35");
        cout << "\t\t\tРасчетно-графическая работа";
        if (Punckt == 1) printf("\t\n\t\n  --> Таблица\n");
        else             printf("\t\n\t\n   Таблица\n");
        if (Punckt == 2) printf("\t\n\t\n  --> График\n");
        else             printf("\t\n\t\n   График\n");
        if (Punckt == 3) printf("\t\n\t\n  --> Уравнение\n");
        else             printf("\t\n\t\n   Уравнение\n");
        if (Punckt == 4) printf("\t\n\t\n  --> Интеграл\n");
        else             printf("\t\n\t\n   Интеграл\n");
        if (Punckt == 5) printf("\t\n\t\n  --> Об авторе\n");
        else             printf("\t\n\t\n   Об авторе\n");

    }
};
class Table  // таблица 1
{
private:
    // other variable
public:
    //Main fuction
    void draw()
    {
        system("cls");
        tablica();
        gotoxy(47, 2);
        cout << "Таблица иттераций";
    }
};
class Graf //график 2
{
private:
    // other variable
public:
    //Main fuction
    void draw()
    {
        system("cls");
        Charts();
    }
};
class Yravn //уравнение 3
{
private:
    // other variable
public:
    //Main fuction
    void draw()
    {
        system("cls");
        cout << "\n\tКорень уравнения, решенное методом половинного деления равен: " << HalfDivEquation(1.4, Pi / 2, 0.001);
        //cout << "\n\tКорень уравнения, решенное методом хорд равен: " << chordmethod(0,Pi/2); //Right answer = 1.48790267

    }
};
class Integral
{
private:
    // other variable
public:
    //Main fuction
    void draw()
    {
        system("cls");
        cout << "\n\tИнтеграл, решенный методом трапеций равен: " << trapezoidalIntegral(2.0, 5.0, 200);
        cout << "\n\tИнтеграл, решенный методом прямоугольников равен: " << rectangelIntegral(2.0, 5.0, 200);

        cout << "\n\tИнтеграл, решенный методом трапеций #2 равен: " << Trapeze(2.0, 5.0, 200);
        cout << "\n\tИнтеграл, решенный методом прямоугольников #2 равен: " << Sympson(2.0, 5.0, 200);
    }
};
class Author // автор 5
{
private:
    // other variable
public: 
    //Main fuction
    void draw()
    {
        system("cls");
        AboutME();
     }
};
int main()
{
    Animation();
    setlocale(LC_ALL, "rus");
    ShowCursor(FALSE);
    Menu menu;
    menu.draw(menu.Num);
    while (true)
    {
        menu.Num = _getch();
        menu.draw(menu.Num);
        if (menu.Num == 13) // нажатие энтера
        {
            switch (menu.Punckt)
            {
            case 1:
                // функция таблицы после нажатия энтер и остальное так же
                //printf("1");
                Table tabl;
                tabl.draw();
                break;
            case 2:
                //printf("2");
                // функция графикa
                Graf graf;
                graf.draw();
                break;
            case 3:
                //printf("3");
                // функция уравнения
                Yravn yravn;
                yravn.draw();
                break;
            case 4:
                //printf("4");
                // функция интеграла
                Integral integ;
                integ.draw();
                break;
            case 5:
                //printf("5");
                // функция автора
                Author author;
                author.draw();
                break;
            default:
                break;
            }
        }
        else if (menu.Num == 27) menu.draw(menu.Num); // нажатие ескейпа возвращает к менюшке


    }
}
