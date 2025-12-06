#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <cstdlib>


template <typename T>
class Matrix {
private:
    int m_rows;
    int m_columns;
    T** m_matrix;

    void allocateMemory();

public:
    Matrix();
    Matrix(int rows, int columns);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;

    ~Matrix();

    int getRows() const;
    int getColumns() const;

    T get(int row, int col) const;
    void set(int row, int col, T value);

    void init();
    void print() const;

    T** getPointer();
    T** getPointer() const;


    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);
};


template <typename T>
Matrix<T>::Matrix() : m_rows(5), m_columns(5) {
    allocateMemory();
}

template <typename T>
Matrix<T>::Matrix(int rows, int columns)
    : m_rows(rows), m_columns(columns) {
    allocateMemory();
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other)
    : m_rows(other.m_rows), m_columns(other.m_columns) {
    allocateMemory();
    for (int i = 0; i < m_rows; i++)
        for (int j = 0; j < m_columns; j++)
            m_matrix[i][j] = other.m_matrix[i][j];
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept
    : m_rows(other.m_rows), m_columns(other.m_columns), m_matrix(other.m_matrix) 
{
    other.m_rows = 0;
    other.m_columns = 0;
    other.m_matrix = nullptr;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
    if (this != &other) {
        for (int i = 0; i < m_rows; i++)
            delete[] m_matrix[i];
        delete[] m_matrix;

        m_rows = other.m_rows;
        m_columns = other.m_columns;

        allocateMemory();
        for (int i = 0; i < m_rows; i++)
            for (int j = 0; j < m_columns; j++)
                m_matrix[i][j] = other.m_matrix[i][j];
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < m_rows; i++)
            delete[] m_matrix[i];
        delete[] m_matrix;

        m_rows = other.m_rows;
        m_columns = other.m_columns;
        m_matrix = other.m_matrix;

        other.m_rows = 0;
        other.m_columns = 0;
        other.m_matrix = nullptr;
    }
    return *this;
}

template <typename T>
Matrix<T>::~Matrix() {
    if (m_matrix) {
        for (int i = 0; i < m_rows; i++)
            delete[] m_matrix[i];
        delete[] m_matrix;
    }
}

template <typename T>
void Matrix<T>::allocateMemory() {
    m_matrix = new T*[m_rows];
    for (int i = 0; i < m_rows; i++)
        m_matrix[i] = new T[m_columns];
}

template <typename T>
void Matrix<T>::init() {
    srand(time(nullptr));
    for (int i = 0; i < m_rows; i++)
        for (int j = 0; j < m_columns; j++)
            m_matrix[i][j] = T{};
}

template <typename T>
void Matrix<T>::print() const {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_columns; j++)
            std::cout << m_matrix[i][j] << " ";
        std::cout << "\n";
    }
}

template <typename T>
T Matrix<T>::get(int row, int col) const {
    return m_matrix[row][col];
}

template <typename T>
void Matrix<T>::set(int row, int col, T value) {
    m_matrix[row][col] = value;
}

template <typename T>
T** Matrix<T>::getPointer() {
    return m_matrix;
}

template <typename T>
T** Matrix<T>::getPointer() const {
    return m_matrix;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    for (int i = 0; i < matrix.m_rows; i++) {
        for (int j = 0; j < matrix.m_columns; j++)
            os << matrix.m_matrix[i][j] << " ";
        os << "\n";
    }
    return os;
}


#endif
