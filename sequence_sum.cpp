#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;
int attempts = 1,
max_attempts = 3;
unsigned n = 1;
bool attempt_right;
float x,
x_max = 5.0,
x_min = 1.0,
sum,
ai,
q = 0,
eps,
eps_max = 1.1e+5,
eps_min = 8e-1;
unsigned rows = 2,
columns;

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "-----------------------------------------------------------------------------\n"
        << "| Формулировка задания: найти сумму последовательности слагаемых по формуле |\n"
        << "| U(n)=((2n^2 + n - 1)/(3n^3 + 2))x^n                                       |\n"
        << "| Эта версия работы использует динамические массивы и указатели             |\n"
        << "| Дата начала: 18.01.2024                                                   |\n"
        << "| Дата окончания: 23.01.2024                                                |\n"
        << "| Версия: 2.2.7                                                             |\n"
        << "-----------------------------------------------------------------------------\n\n" << endl;
    do {
        cout << "\nВведите значение x, при условии что x принадлежит [" << x_min << " , " << x_max << "]"
            << "\nПопытка: " << attempts << "\\" << max_attempts << endl;
        if (!(cin >> x) || (x_min > x || x > x_max))
        {
            cin.clear();
            while (cin.get() != '\n');
            cout << "\nВведеный x не соответствует требуемым значениям!\n";
            attempt_right = false;
            attempts++;
        }
        else attempt_right = true;
    } while (attempt_right == false && attempts <= max_attempts);
    if (attempts > max_attempts) {
        cout << "\n\nПревышен лимит попыток ввода!\nПрограмма звершается...\n";
        return 0;
    }
    attempts = 1;
    do {
        cout << "\nВведите значение E, при условии что E принадлежит [" << setprecision(1) << setiosflags(ios::scientific) << eps_min << " , " << eps_max << "]"
            << "\nПопытка: " << attempts << "\\" << max_attempts << endl;
        if (!(cin >> eps) || (eps_min > eps || eps > eps_max)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "\nВведеная E не соответствует требуемым значениям!\n";
            attempt_right = false;
            attempts++;
        }
        else attempt_right = true;
    } while (attempt_right == false && attempts <= max_attempts);
    if (attempts > max_attempts) {
        cout << "\n\nПревышен лимит попыток ввода!\nПрограмма звершается...\n";
        return 0;
    }
    cout << resetiosflags(ios::scientific) << setprecision(3)
        << "\nx = " << x << "\n"
        << setprecision(2)
        << "E = " << eps << "\n" << endl;
    ai = (2 * pow(n, 2) + n - 1) * pow(x, n)
        /
        (3 * pow(n, 3) + 2);
    for (int i = 1; n <= 1000 && ai <= eps; i++) {
        n++;
        q = ((2 * (n * n) + 5 * n + 2) * (3 * (n * n * n) + 2) * x)
            /
            ((3 * (n * n * n) + 9 * (n * n) + 9 * n + 5) * (2 * (n * n) + n - 1));
        ai *= q;
    };
    columns = n;
    n = 1;
    float** data{ new float* [rows]() };
    for (unsigned i = 0; i < rows; i++)
        *(data + i) = new float[columns]();
    ai = (2 * pow(n, 2) + n - 1) * pow(x, n)
        /
        (3 * pow(n, 3) + 2);
    sum = ai;
    *(*(data)) = ai;
    *(*(data + 1)) = sum;
    for (; n <= 1000 && ai <= eps; n++) {
        q = (((2 * (n * n) + 5 * n + 2) * (3 * (n * n * n) + 2)) * x)
            /
            ((3 * (n * n * n) + 9 * (n * n) + 9 * n + 5) * (2 * (n * n) + n - 1));
        ai *= q;
        sum += ai;
        if (ai <= eps) {
            *(*(data)+n) = ai;
            *(*(data + 1) + n) = sum;
        }
    }; cout << "| " << setw(2) << "n" << setw(4) << " | " << setw(6) << "ai" << setw(6) << " | " << setw(5) << "S" << setw(6) << " |"
        << "\n-------------------------------" << endl;
    for (unsigned i = 0; i < n - 1; i++)
    {
        cout << "| " << resetiosflags(ios::showpos) << setw(3) << i + 1 << " | " << setiosflags(ios::scientific) << setiosflags(ios::showpos) << setprecision(2) << setw(5) << *(*(data)+i) << " | " << setw(5) << *(*(data + 1) + i) << " |"
            << "\n-------------------------------" << endl;
    }
    for (unsigned i = 0; i < rows; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}
