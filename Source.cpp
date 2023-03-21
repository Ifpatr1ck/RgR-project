#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

using namespace std;

double e = 2.71828182845904523536;
double Pi = 3.1415926535;

HWND hwnd = GetConsoleWindow(); //Descripter of Window
HDC dc = GetDC(hwnd);//Device context - for drawing
void gotoxy(int xpos, int ypos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
} // No Lags with moving between menu numbers
void setcur(int x, int y)//��������� ������� �� �������  x y 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};
double f(double x)
{
    return pow(e, (-x)) * log(x + 1);
} // Function of Integral
double trapezoidalIntegral(double a, double b, int n) {
    const double width = (b - a) / n;

    double trapezoidal_integral = 0;
    for (int i = 0; i < n; i++) {
        const double x1 = a + i * width;
        const double x2 = a + (i + 1) * width;

        trapezoidal_integral += 0.5 * (x2 - x1) * (f(x1) + f(x2));
    }

    return trapezoidal_integral;
} //Solving the Integral by the trapezoid method    
double rectangelIntegral(double a, double b, int n)
{
    double INTGRL = 0.0;
    double h = double((b - a) / n);
    for (double x = a; x <= b; x += h)
        INTGRL += f(x - h / 2);
    INTGRL *= h;
    return INTGRL;
} //Solving the Integral by the rectangel method
double Equation(int x)
{
    return tan(x) - pow(e,x+1);
} // Equation
double HalfDivEquation(double A, double B)
{
    double C, epsilon = 0.001;
    C = (A + B) / 2;
    while (abs(Equation(C) > epsilon))
    {
        C = (A + B) / 2;
        if ((Equation(A) * Equation(C)) < 0) B = C;
        else if ((Equation(A) * Equation(C)) > 0) A = C;
    }
    return C; 
}//Solving the Equation by the Half-devision Method
double chordmethod(double A, double B)
{
    double epsilon = 0.001;
    while (abs(B - A) > epsilon)
    {
        A = A - (B - A) * Equation(A) / (Equation(B) - Equation(A));
        B = B - (A - B) * Equation(B) / (Equation(A) - Equation(B));
    }
    return B;
}
double HordEquation(double a, double b, double c)
{
    while (fabs(Equation(b)) > c)
    {
        a = b - ((b - a) * Equation(b)) / (Equation(b) - Equation(a));
        b = a - ((a - b) * Equation(a)) / (Equation(a) - Equation(b));
    }
    return b;
} //Solving the Equation by the chord Method #1
void BackGround()
{
    SelectObject(dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(dc, RGB(150, 205, 80)); // - ���� �����������
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
                //�������� �������������
                SelectObject(dc, GetStockObject(DC_BRUSH));
                SetDCBrushColor(dc, RGB(R, G, B)); // - ���� �����������
                Rectangle(dc, PointWidth1 + j, PointHigh1, PointWidth2 + j, PointHigh2);
                Sleep(10);
            }
            y++;
        } // �������� ����������� ����� ������� ������� �������
        if (x == 0 && y == 1)
        {
            for (int k = 0; k <= 400 - PointHigh2; k += Speed)
            {
                BackGround();
                //�������� �������������
                SelectObject(dc, GetStockObject(DC_BRUSH));
                SetDCBrushColor(dc, RGB(R, G, B)); // - ���� �����������
                Rectangle(dc, 800 - PointWidth2, PointHigh1 + k, 800, PointHigh2 + k);
                Sleep(10);
            }
            x++;
        }// �������� ����������� ������ ���� ������ �������
        if (x == 1 && y == 1)
        {
            for (int j = 0; j <= 800 - PointWidth2; j += Speed)
            {
                BackGround();
                //�������� �������������
                SelectObject(dc, GetStockObject(DC_BRUSH));
                SetDCBrushColor(dc, RGB(R, G, B)); // - ���� �����������
                Rectangle(dc, 800 - PointWidth2 - j, 400 - PointHigh2, 800 - j, 400);
                Sleep(10);
            }
            y--;
        } // �������� ����������� ������ ����� ������ �������
        if (x == 1 && y == 0)
        {
            int j = 0;
            for (; j < 400 + Speed - PointHigh2; j += Speed)
            {
                BackGround();
                //�������� �������������
                SelectObject(dc, GetStockObject(DC_BRUSH));
                SetDCBrushColor(dc, RGB(R, G, B)); // - ���� �����������
                Rectangle(dc, PointWidth1, 400 - PointHigh2 - j, PointWidth2, 400 - j);
                Sleep(10);
                if (j >= (400 - PointHigh2)) N += 100;
            }
            x--;
        } // �������� ����������� ����� ����� ����� �������
        if (PointWidth2 >= 800 && PointHigh2 >= 400) break;
    }
} // Animation of start the programm
void tablica()
{
    BackGround();
    //Running rectangel
    int R = 50, G = 90, B = 75;
    SelectObject(dc, GetStockObject(PS_SOLID));
    SetDCBrushColor(dc, RGB(R, G, B)); // - Color of the placeholder
    Rectangle(dc, 10, 10, 100, 100);
    Sleep(10);

    int n = 20;
    double a = 0, x = 6.28 / n;
    for (int i = 0; i < n; i++);
    {
        cout << "\n" << 5 - 3 * cos(a);
        a += x;
    }
} //Don't ready table

class Menu
{
public:
    int Num = 0; // ����� ������� ������� 
    int Punckt = 0; // ������ 1-5
    void draw(int num)
    {
        switch (num)
        {
        case 80: // ������� ����
            if (Punckt >= 5) Punckt = 1;
            else Punckt++;
            break;
        case 72: // ������� �����
            if (Punckt <= 1) Punckt = 5;
            else Punckt--;
            break;
        default:
            break;
        }
        // ������ �������
        //gotoxy(0, 0);
        setcur(0, 0);
        system("cls");
        system("COLOR 35");
        cout << "\t\t\t��������-����������� ������";
        if (Punckt == 1) printf("\t\n\t\n  --> �������\n");
        else             printf("\t\n\t\n   �������\n");
        if (Punckt == 2) printf("\t\n\t\n  --> ������\n");
        else             printf("\t\n\t\n   ������\n");
        if (Punckt == 3) printf("\t\n\t\n  --> ���������\n");
        else             printf("\t\n\t\n   ���������\n");
        if (Punckt == 4) printf("\t\n\t\n  --> ��������\n");
        else             printf("\t\n\t\n   ��������\n");
        if (Punckt == 5) printf("\t\n\t\n  --> �� ������\n");
        else             printf("\t\n\t\n   �� ������\n");

    }
};
class Table  // ������� 1
{
private:
    // other variable
public:
    //Main fuction
    void draw()
    {
        tablica();
        system("cls");
        printf("��� ����� ���� ���� �������");
    }
};
class Graf //������ 2
{
private:
    // other variable
public:
    //Main fuction
    void draw()
    {
        system("cls");
        printf("��� ��� ���� ��� ������");
    }
};
class Yravn //��������� 3
{
private:
    // other variable
public:
    //Main fuction
    void draw()
    {
        system("cls");
        cout << "\n\t������ ���������, �������� ������� ����������� ������� �����: " << HalfDivEquation(1.4, Pi/2);
        //cout << "\n\t������ ���������, �������� ������� ���� �����: " << chordmethod(0,Pi/2); //Right answer = 1.48790267

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
        cout << "\n\t��������, �������� ������� �������� �����: " << trapezoidalIntegral(2.0, 5.0, 200);
        cout << "\n\t��������, �������� ������� ��������������� �����: " << rectangelIntegral(2.0, 5.0, 200);
    }
};
class Author // ����� 5
{
private:
    // other variable
public: 
    //Main fuction
    void draw()
    {
        system("cls");
        cout << "\t\t��������-����������� ������ ��������� �� ���������� \"����������������\" \n\t\t��������� ������ ���-221 ��� ������� ��������������\n\t\t������� ������: �11";
    }
};
int main()
{
    Animation();
    system("color 2");
    setlocale(LC_ALL, "rus");
    ShowCursor(FALSE);
    Menu menu;
    menu.draw(menu.Num);
    while (true)
    {
        menu.Num = _getch();
        menu.draw(menu.Num);
        if (menu.Num == 13) // ������� ������
        {
            switch (menu.Punckt)
            {
            case 1:
                // ������� ������� ����� ������� ����� � ��������� ��� ��
                //printf("1");
                Table tabl;
                tabl.draw();
                break;
            case 2:
                //printf("2");
                // ������� ������a
                Graf graf;
                graf.draw();
                break;
            case 3:
                //printf("3");
                // ������� ���������
                Yravn yravn;
                yravn.draw();
                break;
            case 4:
                //printf("4");
                // ������� ���������
                Integral integ;
                integ.draw();
                break;
            case 5:
                //printf("5");
                // ������� ������
                Author author;
                author.draw();
                break;
            default:
                break;
            }
        }
        else if (menu.Num == 27) menu.draw(menu.Num); // ������� ������� ���������� � �������


    }
}
