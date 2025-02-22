#include <iostream>
#include <type_traits>

using namespace std;

template <bool B>
struct test_struct {};



template <typename T, typename std::enable_if_t<
    is_arithmetic_v<T> &&
    !is_same_v<T, char> &&
    !is_same_v<T, bool>, int> = 0>
class Matrix
{
private:
    size_t n;
    size_t m;
    T** matr;

    void clear_matr()
    {
        for(int i = 0; i < n; i++)
        {
            delete[] matr[i];
        }
        delete[] matr;
    }

    // Matrix Get_Minor(Matrix& Matr, unsigned int row, unsigned int col)
    // {
    //     Matrix<t> result(Matr.n - 1, Matr.m - 1, 0);

    //     for(int i = 0; i < )
    // }



//********* */



public:

    // Base Constuctor
    Matrix(unsigned int rows, unsigned int cols, T value)
    {
        if(rows > 3 || cols > 3)
        {
            throw runtime_error("Matrix sizes are not supposed to be bigger than 3!");
        }

        n = rows;
        m = cols;
        matr = new T*[n];
        for(int i = 0; i < n; i++)
        {
            matr[i] = new T[m];
            for(int j = 0; j < m; j++)
            {
                matr[i][j] = value;
            }
        }
    }

    // Copying Constructor
    Matrix(Matrix& other)
    {
        n = other.n;
        m = other.m;
        matr = new T*[n];
        for(int i = 0; i < n; i++)
        {
            matr[i] = new T[m];
            for(int j = 0; j < m; j++)
            {
                matr[i][j] = other.matr[i][j];
            }
        }
    }


    // ?????????????????????????????????????????????????????? void
    void operator=(Matrix& other)
    {

        clear_matr();

        n = other.n;
        m = other.m;
        matr = new T*[n];
        for(int i = 0; i < n; i++)
        {
            matr[i] = new T[m];
            for(int j = 0; j < m; j++)
            {
                matr[i][j] = other.matr[i][j];
            }
        }
    }

    void SetValues()
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                std::cout << "Matrix[" << i << "][" << j << "]: "; std::cin >> matr[i][j];
            }
        }
    }

    ~Matrix()
    {
        clear_matr();
    }

    T* operator[](int i)
    {
        return matr[i];
    }


    void print()
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                std::cout << matr[i][j] << " ";
            }
            std::cout << '\n';
        }
    }

    Matrix operator+(Matrix& other)
    {
        if(n != other.n || m != other.m)
        {
            throw std::invalid_argument("Matrices should have same dimensions!");
        }

        Matrix<T> result(n, m, 0);

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                result[i][j] = matr[i][j] + other.matr[i][j];
            }
        }

        return result;
    }

    void operator+=(Matrix& other)
    {

        if(n != other.n || m != other.m)
        {
            throw std::invalid_argument("Matrices should have same dimensions!");
        }


        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                matr[i][j] += other.matr[i][j];
            }
        }
    }

    Matrix operator*(Matrix& other)
    {
        if(m != other.n)
        {
            throw std::runtime_error("Number of the first Matrix's columns should be equal to the number of the second matrix's rows!");
        }

        Matrix<T> result(n, other.m, 0);

        for(int i = 0; i < result.n; i++)
        {
            for(int j = 0; j < result.m; j++)
            {
                for(int k = 0; k < m; k++)
                {
                    result.matr[i][j] += matr[i][k] * other.matr[k][j];
                }
            }
        }

        return result;
    }

    void operator*=(Matrix& other)
    {
        if(m != other.n)
        {
            throw std::runtime_error("Number of the first Matrix's columns should be equal to the number of the second matrix's rows!");
        }

        Matrix<T> new_m = *this * other;
        
        *this = new_m;
    }

    Matrix& operator++()
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                matr[i][j] += 1;
            }
        }

        return *this;
    }

    Matrix operator++(T)
    {
        Matrix<T> temp = (*this);
        ++(*this);
        return temp;
    }


    T Get_Determinant()
    {
        if(n != m)
        {
            throw runtime_error("Only square matrices have determinants");
        }

        switch(n)
        {
        case 1:
            return matr[0][0];
            break;
        case 2:
            return (matr[0][0]*matr[1][1] - matr[0][1]*matr[1][0]);
            break;
        case 3:
            return (matr[0][0] * (matr[1][1]*matr[2][2] - matr[1][2]*matr[2][1]) -\
                    matr[0][1] * (matr[1][0]*matr[2][2] - matr[1][2]*matr[2][0]) +\
                    matr[0][2] * (matr[1][0]*matr[2][1] - matr[1][1]*matr[2][0]));
            break;
        }
    }
};





int main()
{
    std::cout << '\n';
    Matrix<int> m1(2, 3, 0);
    Matrix<int> m2(2, 3, 0);
    Matrix<int> m3(3, 2, 0);

    std::cout<<"m1:" << '\n';
    m1.SetValues();
    std::cout<<"m2:" << '\n';
    m2.SetValues();
    std::cout<<"m3:" << '\n';
    m3.SetValues();

    (m1 + m2).print();
    std::cout <<'\n';
    (m1*m3).print();
    std::cout <<'\n';


    std::cout<<"m4:" << '\n';
    Matrix<int> m4(3, 3, 0);
    m4.SetValues();
    std::cout << m4.Get_Determinant();

    return 0;
}