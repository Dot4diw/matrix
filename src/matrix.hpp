#ifndef __MATRIX_HPP_INCLUDED
#define __MATRIX_HPP_INCLUDED

#include <vector>

template <typename T>
class matrix
{
private:
    unsigned int m_rows { 0 };
    unsigned int m_cols { 0 };
    std::vector<T> m_matrix;

public:
    matrix(unsigned int  m, unsigned int n, T& init);
    matrix(unsigned int m, unsigned int n, std::vector<T>& vector);
    matrix(const matrix& other);

    matrix();
    ~matrix();

    T& operator()(unsigned int row, unsigned int col);

    inline unsigned int get_row();
    inline unsigned int get_col();
    inline unsigned int size();

    matrix& operator=(const matrix& other);
    matrix& operator+(const matrix& other);

    matrix& operator-(const matrix& other);
    matrix operator*(matrix& other);
    unsigned int rank();

    inline bool is_invertible();

    inline matrix& inverse();


    matrix transpose();
    std::vector<T> operator*(const std::vector<T> vector);
    matrix& operator+(const T& number);
    matrix& operator-(const T& number);
    matrix& operator*(const T& number);
    matrix& operator/(const T& number);
    void content() const;
};

#endif // __MATRIX_HPP_INCLUDED
