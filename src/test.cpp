#include <iostream>
#include "matrix.hpp"

int main()
{
    std::vector<double> vec { 2, -3, 8, 2, 2, 12, -2, 12, 1, 3, 1, 4 };

    matrix<double> mat(3, 4, vec);
    std::vector<double> v { 1,2,3,4};
    matrix<double> mmat = mat;
    mmat.content();

    std::cout << "\n++++++++++++++++\nThe rank of matrix is : " << mat.rank() << "\n++++++++++++++++\n";
    return 0;
}
