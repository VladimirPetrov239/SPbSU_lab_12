#include "matrix.h"
#include <fstream>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>


bool Matrix::check_sizes(const Matrix& m1, const Matrix& m2) {
    return (m1._rows == m2._rows) && (m1._cols == m2._cols);
}

Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    try {
        _data = new int*[_rows];
    } catch (std::bad_alloc& e) {
        throw MatrixException("Unable to allocate memory");
    }
    if(_rows > 0) {
        try {
          _data[0] = new int[_rows * _cols];
        } catch (std::bad_alloc& e) {
          delete[] _data;
          throw MatrixException("Unable to allocate memory");
        }
        for(size_t i = 1; i < _rows; i ++) {
            _data[i] = _data[0] + (_cols) * i;
        }
        memset(_data[0], 0, _cols * _rows * sizeof(int));
    }
}

Matrix::Matrix(std::size_t r, std::size_t c, int** arr) {
    _rows = r;
    _cols = c;
    _data = arr;
}

Matrix::Matrix(const Matrix& oth) {
    _rows = oth._rows;
    _cols = oth._cols;
    try {
        _data = new int*[_rows];
    } catch (std::bad_alloc& e) {
        throw MatrixException("Unable to allocate memory");
    }
    if(_rows > 0) {
        try {
          _data[0] = new int[_rows * _cols];
        } catch (std::bad_alloc& e) {
          delete[] _data;
          throw MatrixException("Unable to allocate memory");
        }
        for(size_t i = 1; i < _rows; i ++) {
            _data[i] = _data[0] + (_cols) * i;
        }
        memcpy(_data[0], oth._data[0], _cols * _rows * sizeof(int));
    }
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    if(i >= 0 && i < _rows && j >= 0 && j < _cols) {
        return _data[i][j];
    } else {
        throw MatrixException("ACCESS: bad index.");
    }
}

void Matrix::swap(Matrix& oth) {
    std::swap(_rows, oth._rows);
    std::swap(_cols, oth._cols);
    std::swap(_data, oth._data);
}

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
    size_t rows = m.get_rows();
    size_t cols = m.get_cols();
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            out << m.get(i,j);
            if (j + 1 != cols) {
                out << " ";
            }
        }
        if (i < rows - 1) {
            out << std::endl;
        }
    }
    return out;
}


void Matrix::read(const char* path) {
    std::ifstream my_file;
    my_file.open(path, std::ios::in);
    if (!my_file) {
      throw MatrixException("LOAD: unable to open file.");
    }

    size_t rows, cols;
    if (!(my_file >> rows >> cols)){
        my_file.close();
        throw MatrixException("LOAD: invalid file format.");
    }

    Matrix matrix = Matrix(rows, cols);
    int value;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            my_file >> value;
            matrix.set(i, j, value);
        }
    }
    if(!my_file) {
        my_file.close();
        throw MatrixException("LOAD: invalid file format.");
    }

    matrix.swap(*this);
    my_file.close();
}

Matrix& Matrix::operator=(const Matrix& m) {
    if (this == &m)
        return *this;

    Matrix(m).swap(*this);
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
  if(!check_sizes(*this, m)) {
    throw MatrixException("ADD: dimensions do not match.");
  }
  for(size_t i = 0; i < _rows; i ++) {
      for(size_t j = 0; j < _cols; j++) {
          _data[i][j] += m._data[i][j];
      }
  }
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
  if (_cols != m._rows) {
    throw MatrixException("MUL: #arg1.columns != #arg2.rows..");
  }
  try {
    int** res_array = multiply_array(*this, m);
    Matrix multiply = Matrix(_rows, m._cols, res_array);
    multiply.swap(*this);
    return *this;
  } catch (...) {
    throw MatrixException("Unable to allocate memory.");
  }
}

int** Matrix::multiply_array(const Matrix& m1, const Matrix& m2) {
    int** res;
    try {
        res = new int*[m1._rows];
    } catch (std::bad_alloc& e) {
        throw MatrixException("Unable to allocate memory");
    }
    if(m1._rows > 0) {
        try {
          res[0] = new int[m1._rows * m2._cols];
        } catch (std::bad_alloc& e) {
          delete[] res;
          throw MatrixException("Unable to allocate memory.");
        }
        for (size_t i = 0; i < m1._rows; i++) {
            if(i > 0) {
                res[i] = res[0] + (m2._cols) * i;
            }
            for (size_t j = 0; j < m2._cols; j++) {
                res[i][j] = 0;
                for(size_t pos = 0; pos < m1._cols; pos++) {
                    res[i][j] += m1._data[i][pos] * m2._data[pos][j];
                }
            }
        }
    }
    return res;
}
