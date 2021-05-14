



#pragma once

#include <iostream>
using namespace std;

class TMonomial
{
protected:
    int* power;      
    int n;           
    double coeff;    
    TMonomial* next; 
public:
    TMonomial(int _n = 10);
    TMonomial(int _n, int* _power, double _coeff);
    TMonomial(const TMonomial& A);
    ~TMonomial();

    void SetPower(int* _power);
    void SetN(int _n);
    void SetCoeff(double _coeff);
    void SetNext(TMonomial* _next);

    int* GetPower();
    int GetN() const;
    double GetCoeff() const;
    TMonomial* GetNext();

    bool ComparePowers(const TMonomial& A);

    TMonomial& operator = (const TMonomial& A);
    TMonomial operator + (TMonomial& A);
    TMonomial& operator += (const TMonomial& A);
    TMonomial operator - (TMonomial& A);
    TMonomial& operator -= (const TMonomial& A);
    TMonomial operator * (TMonomial& A);
    TMonomial& operator *= (TMonomial& A);

    bool operator == (TMonomial& A);
    bool operator < (TMonomial& A);
    bool operator > (TMonomial& A);

    friend istream& operator>>(istream& istr, TMonomial& m);
    friend ostream& operator<<(ostream& ostr, TMonomial& m);
};

TMonomial::TMonomial(int _n)
{
    if (_n < 0)
        throw logic_error("negative size");
    else if (_n == 0)
    {
        n = 0;
        next = nullptr;
        power = 0;
        coeff = 0;
    }
    else if (_n > 0)
    {
        n = _n;
        next = nullptr;
        power = new int[n];
        coeff = 0;
    }
}

TMonomial::TMonomial(int _n, int* _power, double _coeff)
{
    if (_n < 0)
        throw logic_error("negative size");
    else if (_n == 0)
    {
        power = 0;
        next = nullptr;
        coeff = _coeff;
        n = _n;
    }
    else
    {
        n = _n;
        coeff = _coeff;
        next = 0;
        power = new int[_n];
        for (int i = 0; i < _n; i++)
        {
            if (_power[i] >= 0)
                power[i] = _power[i];
        }
    }
}

TMonomial::TMonomial(const TMonomial& A)
{
    if (A.n < 0)
        throw logic_error("negative size");
    n = A.n;
    coeff = A.coeff;
    next = A.next;
    if (n != 0) {
        power = new int[n];
        for (int i = 0; i < n; i++)
        {
            power[i] = A.power[i];
        }
    }
    else
        power = 0;
}

TMonomial::~TMonomial()
{
    if (power)
        delete[]power;
    n = 0;
    coeff = 0;
    next = 0;
}

void TMonomial::SetPower(int* _power)
{
    for (int i = 0; i < n; i++)
    {
        if (_power[i] >= 0)
            power[i] = _power[i];
       
    }
}

void TMonomial::SetN(int _n)
{
    if (_n <= 0)
        throw logic_error("negative or null size");
    else if (_n == 0)
    {
        if (power != 0)
            delete[] power;
        power = NULL;
    }
    else if (_n != n)
    {
        int* tmp = power;
        power = new int[_n];

        int count = n < _n ? n : _n;
        for (int i = 0; i < count; i++) {
            power[i] = tmp[i];
        }
        delete[] tmp;
    }
    n = _n;
}

void TMonomial::SetCoeff(double _coeff)
{
    coeff = _coeff;
}

void TMonomial::SetNext(TMonomial* _next)
{
    next = _next;
}

int* TMonomial::GetPower()
{
    return power;
}

int TMonomial::GetN() const
{
    return n;
}

double TMonomial::GetCoeff() const
{
    return coeff;
}

TMonomial* TMonomial::GetNext()
{
    return next;
}

bool TMonomial::ComparePowers(const TMonomial& A)
{
    if (n != A.n)
        return false;
    for (int i = 0; i < n; i++)
        if (power[i] != A.power[i])
            return false;
    return true;
};

TMonomial& TMonomial::operator = (const TMonomial& A)
{
    coeff = A.coeff;
    n = A.n;
    next = A.next;
    delete[] power;
    power = new int[n];
    for (int i = 0; i < n; i++)
        power[i] = A.power[i];
    return *this;
}

TMonomial TMonomial::operator + (TMonomial& A)
{
    TMonomial tmp(*this);
    tmp += A;
    return tmp;
}

TMonomial& TMonomial::operator+=(const TMonomial& A)
{
    if (n != A.n)
        throw logic_error("differnet size");
    for (int i = 0; i < n; i++)
        if (power[i] != A.power[i])
            throw logic_error("different powers");
    coeff += A.coeff;
    return *this;
}

TMonomial TMonomial::operator - (TMonomial& A)
{
    TMonomial tmp(*this);
    tmp -= A;
    return tmp;
}

TMonomial& TMonomial::operator-=(const TMonomial& A)
{
    if (n != A.n)
        throw logic_error("Error");
    for (int i = 0; i < n; i++)
        if (power[i] != A.power[i])
            throw logic_error("different power");
    coeff -= A.coeff;
    return *this;
}

TMonomial TMonomial::operator * (TMonomial& A)
{
    TMonomial tmp(*this);
    tmp *= A;
    return tmp;
}

TMonomial& TMonomial::operator *= (TMonomial& A)
{
    if (n != A.n)
        throw logic_error("different size");
    coeff *= A.coeff;
    for (int i = 0; i < n; i++)
        power[i] += A.power[i];
    return *this;
}

bool TMonomial::operator == (TMonomial& A)
{
    if (n != A.n)
        throw logic_error("differnet size");
    if (coeff != A.coeff)
        return false;
    for (int i = 0; i < n; i++)
        if (power[i] != A.power[i])
            return false;

    return true;
}

bool TMonomial::operator > (TMonomial& A)
{
    if (n != A.n)
        throw logic_error("differnet size");
    for (int i = 0; i < n; i++)
    {
        if (power[i] == A.power[i])
            continue;
        else
            return power[i] > A.power[i] ? true : false;
    }
    return coeff > A.coeff ? true : false;
}

bool TMonomial::operator < (TMonomial& A)
{
    if (n != A.n)
        throw logic_error("different size");
    for (int i = 0; i < n; i++)
    {
        if (power[i] == A.power[i])
            continue;
        else
            return power[i] < A.power[i] ? true : false;
    }
    return coeff < A.coeff ? true : false;
}

istream& operator>>(istream& istr, TMonomial& m)
{
    istr >> m.coeff;
    istr >> m.n;
    for (int i = 0; i < m.n; i++)
        istr >> m.power[i];
    return istr;
}

ostream& operator<<(ostream& ostr, TMonomial& m)
{
    ostr << m.GetCoeff();
    for (int i = 0; i < m.GetN(); i++)
        ostr << "*" << "x" << i << "^" << m.GetPower()[i];

    return ostr;
}


class TPolynomial
{
protected:
    TMonomial* start;
    int n;          
    int k;          
public:
    TPolynomial();
    TPolynomial(int _n);
    TPolynomial(const TPolynomial& A);
    ~TPolynomial();

    int GetN();
    int GetSize();
    TMonomial* GetStart();
    TPolynomial operator-(TPolynomial& A);
    TPolynomial operator+(TPolynomial& A);
    TPolynomial& operator=(const TPolynomial& A);
    bool operator==(const TPolynomial& A);
    bool operator!=(const TPolynomial& A);
    TPolynomial& operator+=(const TMonomial& m);
    TPolynomial& operator-=(const TMonomial& m);
    friend std::ostream& operator<<(std::ostream& ostr, TPolynomial& Tm);
};

TPolynomial::TPolynomial()
{
    n = 0;
    k = 0;
    start = nullptr;
}

TPolynomial::TPolynomial(int _n)
{
    if (_n <= 0)
        throw logic_error("negative size");
    n = _n;
    k = 0;
    start = nullptr;
}

TPolynomial::TPolynomial(const TPolynomial& A)
{
    n = A.n;
    k = A.k;
    if (A.start == nullptr)
        start = nullptr;
    else
    {
        start = new TMonomial(*A.start);
        for (TMonomial* it = A.start->GetNext(); it != NULL; it = it->GetNext())
        {
            start->SetNext(new TMonomial(*it));
        }
    }
}

TPolynomial::~TPolynomial()
{
    if (start == nullptr)
        return;
    TMonomial* next_el;
    for (TMonomial* it = start; it != NULL; )
    {
        next_el = it->GetNext();
        it->~TMonomial();
        it = next_el;
    }
}

int TPolynomial::GetN()
{
    return n;
}

int TPolynomial::GetSize()
{
    return k;
}

TMonomial* TPolynomial::GetStart()
{
    return start;
}

TPolynomial& TPolynomial::operator=(const TPolynomial& A)
{
    if (*this != A)
    {
        if (start != NULL)
        {
            TMonomial* next_el;
            for (TMonomial* it = start; it != NULL; )
            {
                next_el = it->GetNext();
                it->~TMonomial();
                it = next_el;
            }
        }

        start = new TMonomial(*A.start);
        TMonomial* src_el = start;
        for (TMonomial* it = A.start->GetNext(); it != NULL; it = it->GetNext())
        {
            src_el->SetNext(new TMonomial(*it));
            src_el = src_el->GetNext();
        }

        n = A.n;
        k = A.k;
    }
    return *this;
}

TPolynomial& TPolynomial::operator+=(const TMonomial& m)
{
    if (n != m.GetN())
        throw logic_error("different size");
    if (m.GetCoeff() == 0)
        return *this;
    if (start == NULL)
    {
        start = new TMonomial(m);
        k++;
    }
    else
    {
        TMonomial* last_el = nullptr;
        for (TMonomial* ptr = start; ptr != NULL; ptr = ptr->GetNext())
        {
            if (ptr->ComparePowers(m))
            {
                *ptr += m;
                break;
            }
            else if (ptr->GetNext() == nullptr)
            {
                last_el = ptr;
            }
        }

        if (last_el != nullptr)
        {
            last_el->SetNext(new TMonomial(m));
            k++;
        }
    }
    return *this;
}

TPolynomial& TPolynomial::operator-=(const TMonomial& m)
{
    if (n != m.GetN())
        throw logic_error("different size");
    if (m.GetCoeff() == 0)
        return *this;
    if (start == NULL)
    {
        start = new TMonomial(m);
        start->SetCoeff(start->GetCoeff() * (-1));
        k++;
    }
    else
    {
        TMonomial* last_el = NULL;
        for (TMonomial* ptr = start; ptr != NULL; ptr = ptr->GetNext())
        {
            if (ptr->ComparePowers(m))
            {
                *ptr -= m;
                break;
            }
            else if (ptr->GetNext() == NULL)
            {
                last_el = ptr;
            }
        }

        if (last_el != NULL)
        {
            last_el->SetNext(new TMonomial(m));
            last_el->SetCoeff(last_el->GetCoeff() * (-1));
            k++;
        }
    }
    return *this;
}

bool TPolynomial::operator==(const TPolynomial& A)
{
    if (this->n != A.n)
        throw logic_error("different size");
    if (this->k != A.k)
        return false;

    for (TMonomial* src_ptr = start; src_ptr != NULL; src_ptr = src_ptr->GetNext())
        for (TMonomial* p_ptr = A.start; p_ptr != NULL; p_ptr = p_ptr->GetNext())
        {
            if (*src_ptr == *p_ptr)
            {
                break;
            }
            else if (p_ptr->GetNext() == NULL)
            {
                return false;
            }
        }
    return true;
}

bool TPolynomial::operator!=(const TPolynomial& A)
{
    return !(*this == A);
}


TPolynomial TPolynomial::operator+(TPolynomial& A)
{
    if (n != A.n)
        throw logic_error("different size");
    TPolynomial tmp(A);

    for (TMonomial* p_ptr = start; p_ptr != NULL; p_ptr = p_ptr->GetNext())
    {
        tmp += *p_ptr;
    }

    return tmp;
}

TPolynomial TPolynomial::operator-(TPolynomial& A)
{
    if (n != A.n)
        throw logic_error("different size");
    TPolynomial tmp(A);

    for (TMonomial* p_ptr = start; p_ptr != NULL; p_ptr = p_ptr->GetNext())
    {
        tmp -= *p_ptr;
    }

    return tmp;
}

ostream& operator<<(ostream& ostr, TPolynomial& Tm)
{
    if (Tm.start == nullptr)
        ostr << "Empty";
    else
    {
        for (TMonomial* ptr = Tm.start; ptr != NULL; ptr = ptr->GetNext())
        {
            ostr << *ptr;
            if (ptr->GetNext() != NULL)
                ostr << "+";
        }
    }
    return ostr;
}


