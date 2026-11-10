
#include "tensor.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

using namespace std;

int main() {

    // ==========================================
    // TEST 1: GET AND SET
    // ==========================================

    Tensor t({1,2,3,4,5,6}, {2,3});

    assert(t.get({1,2}) == 6);

    t.set({1,2}, 99);

    assert(t.get({1,2}) == 99);


    // Test invalid index

    bool exceptionCaught = false;

    try {
        t.get({2,0});
    }
    catch (const out_of_range& e) {
        exceptionCaught = true;
    }

    assert(exceptionCaught);


    // ==========================================
    // TEST 2: ADDITION
    // ==========================================

    Tensor a({1,2,3,4,5,6}, {2,3});
    Tensor b({10,20,30,40,50,60}, {2,3});

    assert((a + b).get({0,0}) == 11);
    assert((a + b).get({0,1}) == 22);
    assert((a + b).get({0,2}) == 33);
    assert((a + b).get({1,0}) == 44);
    assert((a + b).get({1,1}) == 55);
    assert((a + b).get({1,2}) == 66);


    // ==========================================
    // TEST 3: SUBTRACTION
    // ==========================================

    assert((a - b).get({0,0}) == -9);
    assert((a - b).get({0,1}) == -18);
    assert((a - b).get({0,2}) == -27);
    assert((a - b).get({1,0}) == -36);
    assert((a - b).get({1,1}) == -45);
    assert((a - b).get({1,2}) == -54);


    // ==========================================
    // TEST 4: ELEMENT-WISE MULTIPLICATION
    // ==========================================

    assert((a * b).get({0,0}) == 10);
    assert((a * b).get({0,1}) == 40);
    assert((a * b).get({0,2}) == 90);
    assert((a * b).get({1,0}) == 160);
    assert((a * b).get({1,1}) == 250);
    assert((a * b).get({1,2}) == 360);


    // ==========================================
    // TEST 5: MATRIX MULTIPLICATION
    // ==========================================

    Tensor m1({1,2,3,4,5,6}, {2,3});
    Tensor m2({7,8,9,10,11,12}, {3,2});

    Tensor result = m1.matmul(m2);

    assert(result.get({0,0}) == 58);
    assert(result.get({0,1}) == 64);
    assert(result.get({1,0}) == 139);
    assert(result.get({1,1}) == 154);

    assert(result.getShape() == vector<size_t>({2,2}));


    // ==========================================
    // TEST 6: RESHAPE
    // ==========================================

    Tensor c({1,2,3,4,5,6}, {2,3});

    Tensor r = c.reshape({3,2});

    assert(r.getShape() == vector<size_t>({3,2}));

    assert(r.get({0,0}) == 1);
    assert(r.get({1,0}) == 3);
    assert(r.get({2,1}) == 6);


    // Verify original tensor remains unchanged

    assert(c.getShape() == vector<size_t>({2,3}));


    // Test invalid reshape

    bool exceptionCaught2 = false;

    try {
        c.reshape({4,2});
    }
    catch (const invalid_argument& e) {
        exceptionCaught2 = true;
    }

    assert(exceptionCaught2);


    // ==========================================
    // TEST 7: ADDITION WITH DIFFERENT SHAPES
    // ==========================================

    Tensor d({1,2,3,4,5,6}, {2,3});
    Tensor e({1,2,3,4,5,6}, {3,2});

    bool exceptionCaught3 = false;

    try {
        d + e;
    }
    catch (const invalid_argument& ex) {
        exceptionCaught3 = true;
    }

    assert(exceptionCaught3);


    // ==========================================
    // TEST 8: MATMUL WITH INCOMPATIBLE DIMENSIONS
    // ==========================================

    Tensor m3({1,2,3,4}, {2,2});
    Tensor m4({1,2,3,4,5,6}, {3,2});

    bool exceptionCaught4 = false;

    try {
        m3.matmul(m4);
    }
    catch (const invalid_argument& ex) {
        exceptionCaught4 = true;
    }

    assert(exceptionCaught4);


    // ==========================================
    // TEST 9: ELEMENT-WISE MULTIPLICATION
    // WITH DIFFERENT SHAPES
    // ==========================================

    bool exceptionCaught5 = false;

    try {
        d * e;
    }
    catch (const invalid_argument& ex) {
        exceptionCaught5 = true;
    }

    assert(exceptionCaught5);


    // ==========================================
    // ALL TESTS COMPLETED
    // ==========================================

    cout << "All incompatible operation tests passed!" << endl;
    cout << "All tests passed!" << endl;

    return 0;
}
