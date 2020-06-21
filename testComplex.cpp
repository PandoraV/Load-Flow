#include "complex_new.h"

int main()
{
    Complex Zd(6, 0.314);
    Complex Zy(6, 0.349);
    Complex result;
    result = (Zd*Zy)/(Zd+Zy);
    result.display_adPart();
    return 0;
}