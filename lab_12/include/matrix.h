#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <cstdio>
#include <cstddef>
#include <stdexcept>

class Matrix {
public:
    Matrix(std::size_t r, std::size_t c);
    Matrix(const Matrix& oth);
    Matrix(std::size_t r, std::size_t c, int** arr);

    bool check_sizes(const Matrix& m1, const Matrix& m2);

    void swap(Matrix& oth);

    std::size_t get_rows() const;
    std::size_t get_cols() const;
    void set(std::size_t i, std::size_t j, int val);
    int get(std::size_t i, std::size_t j) const;

    friend std::ostream& operator<<(std::ostream &out, const Matrix &m);


    void read(const char* path);

    int** multiply_array(const Matrix& m1, const Matrix& m2);

    Matrix& operator=(const Matrix& m);

    Matrix operator+(const Matrix& m);
    Matrix operator-(const Matrix& m);
    Matrix operator*(const Matrix& m);

    Matrix& operator+=(const Matrix& m);
    Matrix& operator-=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);

    bool operator==(const Matrix& m);
    bool operator!=(const Matrix& m);

    ~Matrix() {
        if(_rows > 0) {
            delete[] _data[0];
        }
        delete[] _data;
    }
private:
    std::size_t _rows;
    std::size_t _cols;
    int** _data;
};

class MatrixException : public std::logic_error {
public:
    MatrixException(const std::string& what_arg ) : std::logic_error(what_arg) {

    }
};

#endif
