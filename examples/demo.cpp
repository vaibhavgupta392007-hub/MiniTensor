#include "tensor.hpp"

int main() {

    Tensor a({1,2,3,4,5,6}, {2,3});
    Tensor b({7,8,9,10,11,12}, {3,2});

    cout << "Tensor A:" << endl;
    a.display();

    cout << "\nTensor B:" << endl;
    b.display();

    cout << "\nMatrix Multiplication:" << endl;

    Tensor result = a.matmul(b);
    result.display();

    cout << "\nReshaped Tensor A:" << endl;

    Tensor reshaped = a.reshape({3,2});
    reshaped.display();

    return 0;
}