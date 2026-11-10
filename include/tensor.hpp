#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>

using namespace std;

class Tensor {
private:
    vector<double> data;
    vector<size_t> shape;

public:
    Tensor(vector<double> values, vector<size_t> dimensions);

    void display() const;

    double get(vector<size_t> indices) const;

    void set(vector<size_t> indices, double value);

    Tensor operator+(const Tensor& other) const;

    Tensor operator-(const Tensor& other) const;

    Tensor operator*(const Tensor& other) const;

    Tensor matmul(const Tensor& other) const;

    Tensor reshape(vector<size_t> newShape) const;

    vector<size_t> getShape() const;
};

#endif