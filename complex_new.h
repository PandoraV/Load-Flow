//
//  Complex_new.h
//  潮流计算
//
//  Created by 张頔 on 2019/5/9.
//  Edition on 2020/6/9
//  Copyright © 2019年 CIEE. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;
class Complex
{
public:
    void input(double, double);
    void display_rmPart() const;
    void display_adPart() const;
    Complex(double l = 0.0, double a = 0.0) : len(l), deg(a)
    {
        this->update();
    }
    Complex operator+ (const Complex &c) const;
    Complex operator- (const Complex &c) const;
    Complex operator* (const Complex &c) const;
    Complex operator/ (const Complex &c) const;
    Complex conjugate() const;
    void getNum(double, double, double, double);
    void update();
    ~Complex(){}

private:
    double im;
    double re;
    double len; // length
    double ang; // angle (rad)
    double deg; // angle (degree)
};

void Complex::input(double length, double angle)
{
    len = length;
    deg = angle;
    this->update();
}

Complex Complex::operator+ (const Complex &c) const
{
    double r = re + c.re;
    double i = im + c.im;
    double l = sqrt(r*r + i*i);
    double a = 0;
    if (r == 0)
    {
        if (i > 0)
        {
            a = M_PI/2;
        }
        else if (i < 0)
        {
            a = -M_PI/2;
        }
    }
    else
    {
        a = atan(im/re);
    }
    a = a/M_PI*180;    
    return Complex(l, a);
}

Complex Complex::operator- (const Complex &c) const
{
    double r = re - c.re;
    double i = im - c.im;
    double l = sqrt(r*r + i*i);
    double a = 0;
    if (r == 0)
    {
        if (i > 0)
        {
            a = M_PI/2;
        }
        else if (i < 0)
        {
            a = -M_PI/2;
        }
    }
    else
    {
        a = atan(im/re);
    }
    
    a = a/M_PI*180;
    
    return Complex(l, a);
}

Complex Complex::operator* (const Complex &c) const
{
    return Complex(len * c.len, deg + c.deg);
}

Complex Complex::operator/ (const Complex &c) const
{
    return Complex(len / c.len, deg - c.deg);
}

void Complex::display_rmPart() const // display thereal part and imaginary part of complex numbers.
{
    char c;
    if (im < 0) 
        c = '\0';
    else
    {
        c = '+';
    }
    
    cout << re << c << im << "j" << endl;
}

void Complex::display_adPart() const
{
    cout << len << "∠" << deg << "°" << endl;
}

Complex Complex::conjugate() const
{
    return Complex(len, -ang);
}

void Complex::getNum(double t1, double t2, double t3, double t4)
{
    t1 = len;
    t2 = deg;
    t3 = re;
    t4 = im;
}

void Complex::update()
{
    // if (ang == M_PI / 2)
    // {
    //     re = 0;
    //     im = len;
    // }
    // else if (ang == M_PI / 2)
    // {
    //     re = 0;
    //     im = -len;
    // }
    // else
    // {
    //     re = len*cos(ang);
    //     im = len*sin(ang);
    // }
    if (deg == 90)
    {
        re = 0;
        im = len;
    }
    else if (deg == -90)
    {
        re = 0;
        im = -len;
    }
    else
    {
        re = re*cos(deg/180*M_PI);
        im = len*sin(deg/180*M_PI);
    }
    
    // deg = ang*180 / M_PI;
    ang = deg/180*M_PI;
}

