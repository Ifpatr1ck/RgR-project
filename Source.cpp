#include <iostream>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <cmath>
using namespace std;
double e = 2.71828182845904523536; //Euler number
double Pi = 3.1415926535; // Number Pi
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
HPEN CreatePen(int fnPenStyle,int nWidth,COLORREF crColor); //Pen




void gotoxy(int xpos, int ypos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}//Moving carriage to coordinates (x,y)
void setcur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}; //Install the cursor to position(x,y)
void ConsoleCursorVisible(bool show, short size)
{
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show;
    structCursorInfo.dwSize = size;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
} //Visible of Console Cursor
HWND hwnd = GetConsoleWindow(); //Descripter of Window
HDC dc = GetDC(hwnd);//Device context - for drawing
void grid()
{
    HWND hwn = GetConsoleWindow();
    COLORREF lineColor = RGB(0, 0, 0);
    HDC hdc = GetDC(hwn);
    const int d = 500, k = 50, x0 = 50, y0 = 500, c = 50; // d = 350 - good. Grafic is upper because that better looking functions
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
        if (i < 10) { // Drawing marks
            TextOut(hdc, x0 - 10, y0 - k * i, w, 1);
            TextOut(hdc, x0 + k * i, y0 + 10, w, 1);
        }
        else {
            TextOut(hdc, x0 - 10, y0 - k * i, w, 2);
            TextOut(hdc, x0 + k * i, y0 + 10, w, 2);
        }
        LPCWSTR w1 = L"5-3cos(x)";
        LPCWSTR w2 = L"sqrt(e^x - 1)";
        TextOut(hdc, 100, 80, w1, 11);
        TextOut(hdc, 300, 60, w2, 15); // drawing eqution
    }
}
void BackGround()
{
    SelectObject(dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(dc, RGB(150, 205, 80)); // - цвет заполнителя
    Rectangle(dc, 0, 0, 800, 400);
} // Background of Animation 
void Animation()
{
    system("mode con cols=100 lines=25"); //size of console
    int x = 0, y = 0, N = 0, R = 0, G = 133, B = 0; // RGB is color, x,y - coordination
    for (int i = 0; GetKeyState(VK_ESCAPE) >= 0; i++)
    {
        int PointWidth1 = 0, PointHigh1 = 0, PointWidth2 = 100 + N, PointHigh2 = 100 + N / 4, Speed = 20; // Speed is how quickly rectangle is running
        if (x == 0 && y == 0)
        {
            for (int j = 0; j <= 800 - PointWidth2; j += Speed)
            {
                BackGround(); //Function of background color
                //running rectangle
                SelectObject(dc, GetStockObject(DC_BRUSH));
                SetDCBrushColor(dc, RGB(R, G, B)); // - Color of placeholder
                Rectangle(dc, PointWidth1 + j, PointHigh1, PointWidth2 + j, PointHigh2);
                Sleep(10);
            }
            y++; //move to the next step
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
void tablica()
{
    system("color 4"); //Color of text
    int n = 20,x2 = 5, y2 = 0; //n - count of iteration, x2,y2 - coordinates of position the table
    double F1[20], F2[20], x, dx, x1[20], a = 0, b = 2*Pi, minF1 = INT_MAX, maxF1 = INT_MIN, minF2 = INT_MAX, maxF2 = INT_MIN;
    dx = fabs(b - a) / (n - 1); //Increment of function, a,b - function interval
    x = x1[0] = a;
    gotoxy(x2, y2);
    printf(" ______________________________\n");
    gotoxy(x2, y2 + 1);
    printf("| I |    X   |   F1   |   F2   | \n"); //drawing the table
    gotoxy(x2, y2 + 2);
    printf("|___|________|________|________|\n");
    for (int i = 0; i < n; i++) {
        F1[i] = 5 - 3*cos(x); //Funtion #1
        F2[i] = sqrt(pow(e,x)-1); //Function #2
        x1[i] = x;
        x += dx;
    }
    for (int i = 0; i < n; i++) { //seeking min and max of functions
        minF1 = min(F1[i], minF1);
        maxF1 = max(F1[i], maxF1);
        if (F2[i] != -INFINITY) {
            minF2 = min(F2[i], minF2);
        }
        maxF2 = max(F2[i], maxF2);
    }

    for (int i = 1; i <= n; i++) {
        gotoxy(x2, y2 + 2 + i);
        SetConsoleTextAttribute(hStdOut, 4);
        printf("|%3d|%8.3f|", i, x1[i - 1]);
        if (F1[i - 1] == minF1) {
            SetConsoleTextAttribute(hStdOut, 1);
            printf("%8.4f", F1[i - 1]);
        }
        else if (F1[i - 1] == maxF1) {
            SetConsoleTextAttribute(hStdOut, 2);
            printf("%8.4f", F1[i - 1]);
        }
        else
        {
            SetConsoleTextAttribute(hStdOut, 4);
            printf("%8.4f", F1[i - 1]);
        }
        SetConsoleTextAttribute(hStdOut, 4);
        printf("|");
        if (F2[i - 1] == minF2) {
            SetConsoleTextAttribute(hStdOut, 1);
            printf("%8.4f", F2[i - 1]);
        }
        else if (F2[i - 1] == maxF2) {
            SetConsoleTextAttribute(hStdOut, 2);
            printf("%8.4f", F2[i - 1]);
        }
        else
        {
            if (F2[i - 1] == -INFINITY) {
                SetConsoleTextAttribute(hStdOut, 4);
                printf("%8s", "ERROR");
            }
            else {
                SetConsoleTextAttribute(hStdOut, 4);
                printf("%8.4f", F2[i - 1]);
            }
        }
        SetConsoleTextAttribute(hStdOut, 4);
        printf("|\n");
    }
    gotoxy(x2, y2 + 3 + n);
    cout << "|___|________|________|________| \n";
}
void Grafic() {
    system("color 2"); //Color of text
    HWND hwn = GetConsoleWindow();
    COLORREF lineColor = RGB(0, 0, 0);
    HDC hdc = GetDC(hwn);
    const int d = 500, k = 50, x0 = 50, y0 = 500, c = 50; // d = 350 - good. Grafic is upper because that better looking functions
    
    int n = 40000;
    double F1[40000], F2[40000], x1[40000], x, dx, a = 0, b = 6.28, minF1 = 20000, maxF1 = -20000, minF2 = 20000, maxF2 = -20000;
    dx = fabs(b - a) / (n - 1);//Increment of function, a,b - function interval
    x = a;
    //drawing both funtion
    grid();
    for (int i = 0; i < n; i++) {
        F1[i] = 5 - 3 * cos(x); //Function of Grafic #1
        F2[i] = sqrt(pow(e, x) - 1);//Function of Grafic #2
        x1[i] = x;
        x += dx;
    }
    grid();
    for (int i = 0; i < n; i++) {
        SetPixel(hdc, c + k * x1[i], d - k * F2[i], RGB(64, 224, 208));
        MoveToEx(hdc, c + k * x1[i], d - k * F2[i], NULL);
        SetPixel(hdc, c + k * x1[i], d - k * F1[i], RGB(0, 255, 127));
        MoveToEx(hdc, c + k * x1[i], d - k * F1[i], NULL);
    }
    grid();
}
double FunctionEquation(double x) {
    return tan(x) - pow(e, x + 1); // Function of Equation
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
double Equation(int x)
{
    return tan(x) - pow(e, x + 1);
} // Equation
void AboutME() {
    gotoxy(8, 2);
    cout << "Информация об авторе программы:";
    gotoxy(5, 4);
    cout << "Тип работы: расчетно-графическая работа";
    gotoxy(5, 5);
    cout << "название дисциплины: программирование";
    gotoxy(8, 7);
    cout << "выполнил работу:";
    gotoxy(5, 9);
    cout << "Студент Омского Государственного Технического Университета";
    gotoxy(5, 10);
    cout << "факультета информационных технологий и компьютерных систем";
    gotoxy(5, 11);
    cout << "Кит Денис Владимирович, группы ПИН-221";
    gotoxy(5, 12);
    cout << "по направлению \"Программная инженерия\", код направления: 09.03.04 ";
    gotoxy(8, 14);
    cout << "Год выполнения: 2023";
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
double HordEquation(double a, double b, double c)
{
    while (fabs(Equation(b)) > c)
    {
        a = b - ((b - a) * Equation(b)) / (Equation(b) - Equation(a));
        b = a - ((a - b) * Equation(a)) / (Equation(a) - Equation(b));
    }
    return b;
} //Solving the Equation by the chord Method #1
double rectangelIntegral(double a, double b, double n) {
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
class Menu //Menu
{
public:
    int Num = 0; // number of selected button
    int Punckt = 0; // point of menu
    void draw(int num)
    {
        system("color 35");
        switch (num)
        {
        case 80: // down
            if (Punckt >= 6) Punckt = 1;
            else Punckt++;
            break;
        case 72: // up
            if (Punckt <= 1) Punckt = 6;
            else Punckt--;
            break;
        default:
            break;
        }
        // drawing menu
        setcur(0, 0);
        system("cls");
        cout << "\n\n\t\t\t\tРасчетно-графическая работа"; //Name of work
        if (Punckt == 1) //animation of choice
        {
            gotoxy(40,6);
            printf("  --> Таблица\n");
            gotoxy(0, 0);
        }
        else //animation of choice
        {
            gotoxy(40, 6);
            printf("  Таблица\n");
            gotoxy(0, 0);
        }
        if (Punckt == 2) //animation of choice
        {
            gotoxy(40, 8);
            printf("  --> График\n");
            gotoxy(0, 0);
        }
        else //animation of choice
        {
            gotoxy(40, 8);
            printf("  График\n");
            gotoxy(0, 0);
        }
        if (Punckt == 3) //animation of choice
        {
            gotoxy(40, 10);
            printf("  --> Уравнение\n");
            gotoxy(0, 0);
        }
        else //animation of choice
        {
            gotoxy(40, 10);
            printf("  Уравнение\n");
            gotoxy(0, 0);
        }
        if (Punckt == 4) //animation of choice
        {
            gotoxy(40, 12);
            printf("  --> Интеграл\n");
            gotoxy(0, 0);
        }
        else //animation of choice
        {
            gotoxy(40, 12);
            printf("  Интеграл\n");
            gotoxy(0, 0);
        }
        if (Punckt == 5) //animation of choice
        {
            gotoxy(40, 14);
            printf("  --> Об авторе\n");
            gotoxy(0, 0);
        }
        else //animation of choice
        {
            gotoxy(40, 14);
            printf("  Об авторе\n");
            gotoxy(0, 0);
        }
        if (Punckt == 6) //animation of choice
        {
            gotoxy(40, 16);
            printf("  --> Выход\n");
            gotoxy(0, 0);
        }
        else //animation of choice
        {
            gotoxy(40, 16);
            printf("  Выход\n");
            gotoxy(0, 0);
        }
    }
};
class Table //Table of function
{
public:
    void draw()
    {
        system("cls");
        tablica();
        gotoxy(48, 6);
        cout << "Таблица иттераций:";
        gotoxy(44, 8);
        cout << "В таблице представлены значений иттераций следующих";
        gotoxy(44, 9);
        cout << "функций:";
        gotoxy(44, 11);
        cout << "Функция 1: 5 - 3cos(x)";
        gotoxy(44, 12);
        cout << "Функция 2: sqrt(e^x - 1)";
        gotoxy(44, 13);
        cout << "Интервал функций: [0,2Пи]";
        gotoxy(44, 15);
        cout << "Синим цветом отмечены минимальные значения функций";
        gotoxy(44, 16);
        cout << "Зеленым цветом отмечены максимальные значения функций";
    }
};
class Graf
{
public:
    void draw()
    {
        system("cls");
        Grafic();
    }
};
class Yravn
{
public:
    void draw()
    {
        system("cls");
        gotoxy(6, 1);
        cout << "Решение уравнения";
        gotoxy(4, 3);
        cout << "Уравнение: tg(x) - e^(x+1)";
        gotoxy(4, 4);
        cout << "Предлогаемое решение: метод половинного деления";
        gotoxy(4, 5);
        cout << "Интервал решения уравнения: [1,Пи/2]";
        gotoxy(4, 6);
        cout << "Результат: корень уравнения равен " << HalfDivEquation(1, Pi / 2, 0.001);
    }
};
class Integral
{
public:
    void draw()
    {
        system("cls");
        gotoxy(6,1);
        cout << "Решение определенного интеграла";
        gotoxy(4, 3);
        cout << "Предложенный интеграл: e^(-x) * ln(x+1)";
        gotoxy(4, 4);
        cout << "Верхний предел интеграла: 5.0";
        gotoxy(4, 5);
        cout << "Нижний предел интеграла: 2.0";
        gotoxy(4, 6);
        cout << "Цена приращения: 3/200";
        gotoxy(4, 7);
        cout << "Точность определения: 0.001";
        gotoxy(4, 8);
        cout << "Результат, полученный методом трапеций равен: " << trapezoidalIntegral(2.0, 5.0, 200);
        gotoxy(4, 9);
        cout << "Результат, полученный методом прямоугольников равен: " << rectangelIntegral(2.0, 5.0, 200);
    }
};
class Author
{
public: 
    void draw()
    {
        system("cls");
        AboutME(); //Function with information about author
     }
};
class quit
{
public:
    void draw()
    {
        exit(0); //exit
    }
};
int main()
{
    Animation(); //Animation of Loading
    setlocale(LC_ALL, "rus");
    ShowCursor(FALSE); //Visible of Cursor if false
    Menu menu;
    menu.draw(menu.Num);
    while (true)
    {
        menu.Num = _getch(); //waiting click
        menu.draw(menu.Num);
        if (menu.Num == 13)
        {
            switch (menu.Punckt)
            {
            case 1: //Case of table
                Table tabl;
                tabl.draw();
                break;
            case 2: //Case of Grafic
                Graf graf;
                graf.draw();
                break;
            case 3: //Case of Equation
                Yravn yravn;
                yravn.draw();
                break;
            case 4: //Case of Integral
                Integral integ;
                integ.draw();
                break;
            case 5: //Case about author
                Author author;
                author.draw();
                break;
            case 6: //Case to exit
                quit exit;
                exit.draw();
                break;
            default:
                break;
            }
        }
        else if (menu.Num == 27) menu.draw(menu.Num); 
    }
}
