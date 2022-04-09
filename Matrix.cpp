#include "Matrix.h"
#include <cassert>

Matrix::Matrix(int rows, int columns) : rows{rows}, columns{columns}, data{nullptr} {
    assert(rows >= 1);
    assert(columns >= 1);
    // Enkeltpeker
    data = new double[rows*columns]; // et langt array med plass til rows*columns double-elementer
    for (int i = 0; i < rows*columns; i++) {
        data[i] = 0.0;
    }

    // Dobbeltpeker
    /*data = new double*[rows]; // array med plass til rows arrays (pekere)
    for (int i = 0; i < rows; i++) {
        data[i] = new double[columns]; // Hver rad er et array med plass til columns elementer
        for (int j = 0; i < columns; j++) {
            data[i][j] = 0.0;
        }
    }*/
} 

Matrix::Matrix(int N) : Matrix{N, N} {
    assert(N >= 1);
    for (int i = 0; i < N; ++i) {
        //data[i][i] = 1.0; // Dobbeltpeker
         data[(N + 1) * i] = 1.0; // Enkeltpeker 
    }
}

Matrix::~Matrix() {
    // Enkeltpeker
    delete[] data;
    data = nullptr;

    //Dobbeltpeker
    /*for (int i  = 0; i < rows; i++) {
        delete[] data[i];
        data[i] = nullptr;
    }
    delete[] data;
    data = nullptr;

    rows = 0;
    columns = 0;*/
}

void Matrix::set(int row, int column, double value) {
	assert(0 <= row && row < rows);
	assert(0 <= column && column < columns);
	//data[row][column] = value;
    data[row*columns + column] = value;
}

double Matrix::get(int row, int column) const{
    //return data[row][column]; // Dobbeltpeker
    return data[row * columns + column]; // Enkeltpeker, tegn matrise, tenk som langt array
}

double* Matrix::operator[](int row) {
    return &data[row * columns];
    assert(0 <= row && row < rows);
    //return data[row];
}

int Matrix::getRows() const {
    return rows;
}

int Matrix::getColumns() const {
    return columns;
}

std::ostream &operator<<(std::ostream &out, const Matrix &elem) {
    for (int row = 0; row < elem.getRows(); ++row) {
        out << "| ";
        for (int column = 0; column < elem.getColumns(); ++column) {
            out << elem.get(row, column) << ' ';
        }
        out << "|\n";
    }
    return out;
}

Matrix::Matrix(const Matrix & rhs)
	: rows{ rhs.rows }, columns{ rhs.columns }, data{ nullptr }
{
	// Enkeltpeker
	data = new double[rows*columns];
	for ( int i = 0; i < rows*columns; ++i) {
		data[i] = rhs.data[i];
	}

	// Dobbeltpeker
	/*data = new double*[rows];
	for (int i = 0; i < rows; i++) {
		data[i] = new double[columns];
		for (int j = 0; j < columns; j++) {
			data[i][j] = rhs.data[i][j];
		}
	}*/
}

Matrix& Matrix::operator=(Matrix rhs) {
    std::swap(this->data, rhs.data);
    std::swap(this->rows, rhs.rows);
    std::swap(this->columns, rhs.columns);
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& rhs) {
    assert(this->rows == rhs.rows && this->columns == rhs.columns);
    
    for (int row = 0; row < rows; ++row) { 
        for (int column = 0; column < columns; ++column) {
            this->data[row*columns + column] += rhs.data[rows*columns + column];
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix & rhs) const {
    assert(this->rows == rhs.rows && this->columns == rhs.columns);
    return Matrix{*this} += rhs;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {
    assert(this->rows == rhs.rows && this->columns == rhs.columns);
    return *this -= rhs;
}

 Matrix Matrix::operator-(const Matrix& rhs) {
    assert(this->rows == rhs.rows && this->columns == rhs.columns);
    return Matrix{*this};
}

Matrix Matrix::operator*(const Matrix& rhs) const {
    assert(this->columns == rhs.rows);

    Matrix temp{this->rows, rhs.columns};
    for (int row = 0; row < this->rows; ++row) {
        for (int column = 0; column < rhs.columns; ++column) {
            temp.data[row*columns + column] = 0.0;
            for (int i = 0; i < this->columns; ++i) {
                temp.data[row*columns + column] += this->data[i*columns + column];
            }
        }
    }
    return temp;
} 

Matrix Matrix::operator*(double rhs) const {
    return Matrix{*this} *= rhs;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
    // auto temp = *this * rhs;
    // return *this = temp;
    return *this = *this * rhs;
}

Matrix& Matrix::operator*=(double rhs) {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            this->data[i*columns + j] *= rhs;
        }
    }
    return *this;
}

Matrix Matrix::operator-() const {
    return *this * -1.0;
}


