#include "matrix.hpp"

template <typename T>
matrix<T>::matrix(unsigned int  m, unsigned int n, T& init)
{
    m_rows = m;
    m_cols = n;
    m_matrix.resize(m_rows*m_cols, init);
}

template <typename T>
matrix<T>::matrix(unsigned int m, unsigned int n, std::vector<T>& vector)
{
    m_rows = m;
    m_cols = n;
    m_matrix.resize(m_rows*m_cols);
    for ( unsigned int index { 0 }; index < m_rows*m_cols; ++index)
    {
            m_matrix[index] = vector[index];
    }
}

template <typename T>
matrix<T>::matrix(const matrix& other)
{
    if(m_rows == other.m_rows && m_cols == other.m_cols)
    {
        for ( unsigned int index { 0 }; index < m_matrix.size(); ++index)
        {
            m_matrix[index] = other.m_matrix[index];
        }
    }
    else
    {
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_matrix.resize(m_rows*m_cols);
        for ( unsigned int index { 0 }; index < m_matrix.size(); ++index)
        {
            m_matrix[index] = other.m_matrix[index];
        }
    }
}

template <typename T>
matrix<T>::matrix() = default;

template <typename T>
matrix<T>::~matrix(){};

template <typename T>
T& matrix<T>::operator()(unsigned int row, unsigned int col)
{
    return m_matrix[row*m_cols + col];
}

template <typename T>
inline unsigned int matrix<T>::get_row()
{
    return m_rows;
}

template <typename T>
inline unsigned int matrix<T>::get_col()
{
    return m_cols;
}

template <typename T>
inline unsigned int matrix<T>::size()
{
    return m_rows * m_cols;
}

template <typename T>
matrix<T>& matrix<T>::operator=(const matrix& other)
{
    if(m_rows == other.m_rows && m_cols == other.m_cols)
    {
        for ( unsigned int index { 0 }; index < m_matrix.size(); ++index)
        {
            m_matrix[index] = other.m_matrix[index];
        }
        return *this;
    }
    else
    {
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_matrix.resize(m_rows*m_cols);

        for ( unsigned int index { 0 }; index < m_rows*m_cols; ++index)
        {
            m_matrix[index] = other.m_matrix[index];
        }
        return *this;
    }
}

template <typename T>
matrix<T>& matrix<T>::operator+(const matrix& other)
{
    if ( m_rows == other.m_rows && m_cols == other.m_cols )
    {
        for (unsigned int index { 0 }; index < m_matrix.size(); ++index)
        {
            m_matrix[index] += other.m_matrix[index];
        }
        return *this;
    }
    else
    {
        std::cout << "[Error]:  Left and right matrices have different shapes!\n";
        exit(-1);
    }
}

template <typename T>
matrix<T>& matrix<T>::operator-(const matrix& other)
{
    if ( m_rows == other.m_rows && m_cols == other.m_cols )
    {
        for (unsigned int index { 0 }; index < m_matrix.size(); ++index)
        {
            m_matrix[index] -= other.m_matrix[index];
        }
        return *this;
    }
    else
    {
        std::cout << "[Error]:  Left and right matrices have different shapes!\n";
        exit(-1);
    }
}

template <typename T>
matrix<T> matrix<T>::operator*(matrix& other)
{
    if ( m_cols == other.m_rows )
    {
        matrix result(m_rows, other.m_cols, 0.0);
        for (unsigned int row { 0 }; row < result.m_rows; ++row)
        {
            for (unsigned int col { 0 }; col < result.m_cols; ++col)
            {
                for (unsigned int inner { 0 }; inner < (m_cols); ++inner)
                {
                    result.m_matrix[row*result.m_rows + col] += (*this)(row,inner) * other(inner, col);
                }
            }
        }
        return result;
    }
    else
    {
        std::cout << "[Error: The columns of the right matrix are not equal to the rows of the left matrix.\n";
        exit(-1);
    }
}


/* function for finding rank of matrix
   ref: https://cp-algorithms.com/linear_algebra/rank-matrix.html
*/
template <typename T>
unsigned int matrix<T>::rank()
{
    matrix row_echelon_matrix = *this;
    std::vector<bool> row_selected(m_rows, false);

    unsigned int rank { 0 };

    for (unsigned int i = 0; i < m_cols; ++i)
    {
        unsigned int j { 0 };
        for (j; j < m_rows; ++j)
        {
            if (!row_selected[j] && (row_echelon_matrix(j, i) != 0)) break;
        }

        if (j != m_rows)
        {
            ++rank;
            row_selected[j] = true;

            for (unsigned int p = i + 1; p < m_cols; ++p)
            {
                row_echelon_matrix(j, p) /= row_echelon_matrix(j, i);
            }

            for (unsigned int k = 0; k < m_rows; ++k)
            {
                if (k != j && (row_echelon_matrix(k, i) != 0))
                {
                    for (unsigned int p = i + 1; p < m_cols; ++p)
                    {
                        row_echelon_matrix(k, p) -= row_echelon_matrix(j, p) * row_echelon_matrix(k, i);
                    }
                }
            }
        }
    }
    return rank;
}

template <typename T>
bool matrix<T>::is_invertible()
{
    if(m_rows == m_cols && (this -> rank()) == m_rows)
    {
        return true;
    }else
    {
        return false;
    }
}

template <typename T>
matrix<T>& matrix<T>::inverse()
{
    return *this;
}

/*
matrix operator/(const matrix& other)
{
    if ( this -> is_invertible() )
    {
    }
}*/

template <typename T>
matrix<T> matrix<T>::transpose()
{
    matrix result(m_cols, m_rows, 0.0);

    for ( unsigned int row { 0 }; row < m_rows; ++row )
    {
        for ( unsigned int col { 0 }; col < m_cols; ++col)
        {
            result(col, row) = (*this)(row, col); // resutl(col*m_cols, row)
        }
    }
    return result;
}

template <typename T>
std::vector<T> matrix<T>::operator*(const std::vector<T> vector)
{
    if( m_cols == vector.size())
    {
        std::vector<T> result;
        result.resize(m_rows, 0.0);

        for ( unsigned int row { 0 }; row < m_rows; ++row)
        {
            for ( unsigned int col { 0 }; col < m_cols; ++col)
            {
                result[row] += m_matrix[row*m_rows + col] * vector[col];
            }
        }
        return result;
    }else
    {
        std::cout << "[Error]: The columns of matrix is not equal the size of vector.\n";
        exit(-1);
    }
}

template <typename T>
matrix<T>& matrix<T>::operator+(const T& number)
{
    for ( unsigned int index { 0 }; index < m_matrix.size(); ++index )
    {
        m_matrix[index] += number;
    }
    return *this;
}


template <typename T>
matrix<T>& matrix<T>::operator-(const T& number)
{
    for ( unsigned int index { 0 }; index < m_matrix.size(); ++index )
    {
        m_matrix[index] -= number;
    }
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator*(const T& number)
{
    for ( unsigned int index { 0 }; index < m_matrix.size(); ++index )
    {
        m_matrix[index] *= number;
    }
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator/(const T& number)
{
    if (number)
    {
        for ( unsigned int index { 0 }; index < m_matrix.size(); ++index )
        {
            m_matrix[index] -= number;
        }
        return *this;
    }else
    {
        std::cout << "[Error]: Divisor is 0\n";
        exit(-1);
    }
}

template <typename T>
void matrix<T>::content() const
{
    unsigned int count { 1 };
    for ( unsigned int index {0}; index < m_matrix.size(); ++index )
    {
        std::cout <<  m_matrix[index];
        if (count < m_cols)
        {
            std::cout << " ";
            ++count;
        }
        else
        {
            std::cout << "\n";
            count = 1;
        }
    }
}
