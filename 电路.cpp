# include "complex.h"

int main()
{
    Complex i1(2, 0);
    Complex z11(10, 10);
    Complex z22(110, 10);
    Complex z2 = Complex(25, 0)/z22;
    Complex u1 = i1*(z2+z11);
    // u1 = u1 + Complex(10, 0);
    u1.display_rmPart();
    u1.display_adPart();
    Complex us = Complex(0, 5)*u1/z11;
    Complex i2 = us/(Complex(25, 0)/z11 + z22);
    Complex u2 = i2*Complex(100, 0);
    u2.display_rmPart();
    u2.display_adPart();
    return 0;
}