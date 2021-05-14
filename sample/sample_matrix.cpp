// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "polinom.h"
//---------------------------------------------------------------------------


#include <iostream>
#include <locale.h>


    using namespace std;

 int main()
{
  int a[] = { 1, 2, 3 };
  int b[] = { 4, 5, 6 };
  TMonomial A(3, a, 1);
  TMonomial B(3, b, 2);
  TMonomial D(3, b, 2);
 cout << "Monom A: " << A << endl;
 cout << "Monom B: " << B << endl;
            cout <<( A == B) << endl;
            cout << (B == D) << endl;

            int n;
            cin >> n;
            int* c = new int[n];
            for (int i = 0; i < 3; i++)
                c[i] = i * (i - 1);
           
        
            TMonomial C(3, c, 3.5);
            cout << "Monom C: " << C << endl;

            TPolynomial P(3);
            TPolynomial P1(3);
            P += A;
            P1 += A;
            cout << (P == P1) << endl;

            P += B;
            cout << (P1 == P) << endl;
            cout << "\nPolynom P = A + B: " << P << endl;

            TPolynomial P2(P);
            cout << "Polynom P2(P): " << P2 << endl;

            TPolynomial P3(3);
            P3 = P + P2;
            cout << "\nPolynom P3 = P + P2 : " << P3 << endl;
            
            cout << "ffff" << endl;

            TPolynomial P4(3);
            TPolynomial P5(3);
            TPolynomial P6(3);
            P4 += A;
            P5 += B;
            P6 += A;
            cout << P4 << endl;
            cout << P5 << endl;
            cout << (P4 == P5) << endl;
            cout << (P4 == P6) << endl;
            cout << (P4 + P5) << endl;
        
        
   
        return 0;
    
}

