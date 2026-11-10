
#include "tensor.hpp"

Tensor::Tensor(vector<double> values, vector<size_t> dimensions) {
    size_t product = 1;

    for (size_t dimension : dimensions) {
        if (dimension == 0) {
            throw invalid_argument("Dimension cannot be Zero!");
        }

        if (product > numeric_limits<size_t>::max() / dimension) {
            throw invalid_argument("Dimension product overflow!");
        }

        product *= dimension;
    }

    if (product != values.size()) {
        throw invalid_argument("Data sizes do not match Tensor shape!");
    }

    this->data = std::move(values);
    this->shape = std::move(dimensions);
}

void Tensor::display() const {
    cout << "Shape: ";

    for (size_t i = 0; i < shape.size(); i++) {
        cout << shape[i];

        if (i != shape.size() - 1) {
            cout << "x";
        }
    }

    cout << "\nData: ";

    for (size_t i = 0; i < data.size(); i++) {
        cout << data[i] << " ";
    }

    cout << endl;
}

double Tensor::get(vector<size_t> indices) const {
    if (indices.size() != shape.size()) {
        throw invalid_argument("Incorrect number of indices!");
    }

    for (size_t i = 0; i < shape.size(); i++) {
        if (indices[i] >= shape[i]) {
            throw out_of_range("Index is out of bound!");
        }
    }

    size_t flatIndex = 0;

    for (size_t i = 0; i < indices.size(); i++) {
        flatIndex = flatIndex * shape[i] + indices[i];
    }

    return data[flatIndex];
}

void Tensor::set(vector<size_t> indices, double value) {
    if (indices.size() != shape.size()) {
        throw invalid_argument("Incorrect number of indices!");
    }

    for (size_t i = 0; i < shape.size(); i++) {
        if (indices[i] >= shape[i]) {
            throw out_of_range("Index is out of bound!");
        }
    }

    size_t flatIndex = 0;

    for (size_t i = 0; i < indices.size(); i++) {
        flatIndex = flatIndex * shape[i] + indices[i];
    }

    data[flatIndex] = value;
}

Tensor Tensor::operator+(const Tensor& other) const {
    if (shape != other.shape) {
        throw invalid_argument(
            "Tensor shapes should match for addition operation.");
    }

    vector<double> result;
    result.reserve(data.size());

    for (size_t i = 0; i < data.size(); i++) {
        result.push_back(data[i] + other.data[i]);
    }

    return Tensor(result, shape);
}

Tensor Tensor::operator-(const Tensor& other) const {
    if (shape != other.shape) {
        throw invalid_argument(
            "Tensor shapes should match for subtraction operation.");
    }

    vector<double> result;
    result.reserve(data.size());

    for (size_t i = 0; i < data.size(); i++) {
        result.push_back(data[i] - other.data[i]);
    }

    return Tensor(result, shape);
}

Tensor Tensor::operator*(const Tensor& other) const {
    if (shape != other.shape) {
        throw invalid_argument(
            "Tensor shapes should match for Element-wise "
            "multiplication operation.");
    }

    vector<double> result;
    result.reserve(data.size());

    for (size_t i = 0; i < data.size(); i++) {
        result.push_back(data[i] * other.data[i]);
    }

    return Tensor(result, shape);
}

Tensor Tensor::matmul(const Tensor& other) const {
    if (shape.size() != 2 || other.shape.size() != 2) {
        throw invalid_argument("Both tensors must be 2D.");
    }

    if (shape[1] != other.shape[0]) {
        throw invalid_argument(
            "Tensor shapes are not right for matrix multiplication.");
    }

    vector<size_t> resultShape = {shape[0], other.shape[1]};
    vector<double> result(shape[0] * other.shape[1], 0.0);

    for (size_t i = 0; i < shape[0]; i++) {
        for (size_t j = 0; j < other.shape[1]; j++) {
            for (size_t k = 0; k < shape[1]; k++) {
                result[i * other.shape[1] + j] +=
                    data[i * shape[1] + k] *
                    other.data[k * other.shape[1] + j];
            }
        }
    }

    return Tensor(result, resultShape);
}

Tensor Tensor::reshape(vector<size_t> newShape) const {
    size_t total = 1;

    for (size_t dim : newShape) {
        if (dim == 0) {
            throw invalid_argument("Shape dimensions cannot be zero!");
        }

        if (total > numeric_limits<size_t>::max() / dim) {
            throw invalid_argument("Dimension product overflow!");
        }

        total *= dim;
    }

    if (data.size() != total) {
        throw invalid_argument(
            "New shape must contain the same number of elements");
    }

    return Tensor(data, newShape);
}

vector<size_t> Tensor::getShape() const {
    return shape;
}
