#pragma once
#include <ostream>

class Matrix {
private:
    int rows, columns;
    double *data; // Enkeltpeker: Langt array
    //double **data; // Dobbeltpeker: Array av array
public:
    Matrix(int nRows, int nColumns);
    explicit Matrix(int N);
    ~Matrix();

    void set(int row, int column, double value);
    double get(int row, int column) const;
    double *operator[](int row);

    int getRows() const;
    int getColumns() const;

    Matrix& operator=(Matrix rhs);
    Matrix& operator+=(const Matrix& rhs);
    Matrix operator+(const Matrix & rhs) const;

    Matrix(const Matrix & rhs);

    Matrix& operator-=(const Matrix& rhs);
    Matrix operator-(const Matrix& rhs);
    Matrix operator*(const Matrix& rhs) const;
    Matrix operator*(double rhs) const;
    Matrix& operator*=(const Matrix& rhs);
    Matrix& operator*=(double rhs);
    Matrix operator-() const;

};

std::ostream &operator<<(std::ostream &out, const Matrix &elem);