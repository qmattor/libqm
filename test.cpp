// Quincy Mattor
// Copyright 2023

#include <climits>
#include <thread>

#include "libqm.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

#include <boost/test/unit_test.hpp>
using namespace libqm;

BOOST_AUTO_TEST_CASE(TEST_FRACTIONS) {
  init_log("TEST_FRACTIONS.log");
  try {
    Frac f1;
    Frac f2(3);
    Frac f3(3, 4);
    log(verbosity::NORMAL, "beginning initalization checks\n");
    BOOST_CHECK_EQUAL(f1.get_numerator(), 0);
    BOOST_CHECK_EQUAL(f1.get_denominator(), 1);
    BOOST_CHECK_EQUAL(f2.get_denominator(), 1);
    BOOST_CHECK_EQUAL(f2.get_numerator(), 3);
    BOOST_CHECK_EQUAL(f3.get_denominator(), 4);
    BOOST_CHECK_EQUAL(f3.get_numerator(), 3);
    Frac f4(LONG_MAX, LONG_MAX);
    BOOST_CHECK_EQUAL(f4, 1);
    log(verbosity::NORMAL,
        "finished init tests\nBeginning comparison tests:\n");
    BOOST_CHECK_EQUAL(Frac(0, 1), Frac(0, 1));
    BOOST_CHECK_EQUAL(Frac(1, 1), Frac(1, 1));
    BOOST_CHECK_EQUAL(Frac(1, 1), Frac(2, 2));
    BOOST_CHECK_EQUAL(Frac(36, 36), Frac(1, 1));
    BOOST_CHECK_EQUAL(Frac(256, 256), Frac(31, 31));
    BOOST_CHECK_EQUAL(Frac(-3), Frac(-9, 3));

    BOOST_CHECK_NE(Frac(3), Frac(4));
    BOOST_CHECK_NE(Frac(0), Frac(1));
    BOOST_CHECK_NE(Frac(1), Frac(0));
    BOOST_CHECK_NE(Frac(LONG_MIN), Frac(LONG_MAX));
    BOOST_CHECK_NE(Frac(-3, 2), Frac(3, 2));

    BOOST_CHECK_GE(Frac(3, 2), Frac(2, 3));
    BOOST_CHECK_GE(Frac(3, 2), Frac(-2, 3));
    BOOST_CHECK_GE(Frac(2, 3), Frac(3, -2));
    BOOST_CHECK_GE(Frac(2, 3), Frac(2, 3));
    BOOST_CHECK_GE(Frac(0, 2), Frac(0, 3));

    log(verbosity::NORMAL,
        "idc to write more tests than that, this is "
        "stupid\nChecking binary ops:\n");

    Frac ans(9, 4);
    ans += ans;
    BOOST_CHECK_EQUAL(ans, Frac(9, 2));
    ans -= Frac(9, 4);
    BOOST_CHECK_EQUAL(f2 - f3, ans);
    ans.set_numerator(-ans.get_numerator());
    BOOST_CHECK_EQUAL(f3 - f2, ans);

    log(verbosity::NORMAL, "cheking throw\n");
    BOOST_CHECK_THROW(Frac(0, 0), std::runtime_error);
    log(verbosity::NORMAL, "done\n");

  } catch (...) {
  }
  close_log();
}

BOOST_AUTO_TEST_CASE(TEST_COMPLEX) {}

BOOST_AUTO_TEST_CASE(TEST_MATRIX) {
  init_log("TEST_MATRIX.log");
  log_setverbosity(verbosity::DEBUG);
  try {
    log("BEGIN MATRIX\n");
    matrix<int8_t> m(2, 3, 3);
    log("matrix is initialized\nconfirming matrix is initalized to the "
        "correct "
        "values ... ");
    BOOST_CHECK_EQUAL(m(1, 2), 3);
    BOOST_CHECK_EQUAL(m(0, 1), 3);
    uint8_t two_d[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    matrix<uint8_t> two_dimention_pointer((uint8_t *)two_d, 3, 3);
    BOOST_CHECK_EQUAL(two_dimention_pointer(0, 0), 1);
    BOOST_CHECK_EQUAL(two_dimention_pointer(1, 0), 2);
    BOOST_CHECK_EQUAL(two_dimention_pointer(2, 0), 3);

    BOOST_CHECK_EQUAL(two_dimention_pointer(0, 1), 4);
    BOOST_CHECK_EQUAL(two_dimention_pointer(1, 1), 5);
    BOOST_CHECK_EQUAL(two_dimention_pointer(2, 1), 6);

    BOOST_CHECK_EQUAL(two_dimention_pointer(0, 2), 7);
    BOOST_CHECK_EQUAL(two_dimention_pointer(1, 2), 8);
    BOOST_CHECK_EQUAL(two_dimention_pointer(2, 2), 9);
    uint16_t two_d_2[2][3] = {{1, 2, 3}, {4, 5, 6}};

    matrix<uint16_t> two_dimention((uint16_t *)two_d_2, 3, 2);
    BOOST_CHECK_EQUAL(two_dimention(0, 0), 1);
    BOOST_CHECK_EQUAL(two_dimention(1, 0), 2);
    BOOST_CHECK_EQUAL(two_dimention(2, 0), 3);

    BOOST_CHECK_EQUAL(two_dimention(0, 1), 4);
    BOOST_CHECK_EQUAL(two_dimention(1, 1), 5);
    BOOST_CHECK_EQUAL(two_dimention(2, 1), 6);

    log("completed\nconfiriming size ... ");
    BOOST_CHECK_EQUAL(m.get_x(), (size_t)2);
    BOOST_CHECK_EQUAL(m.get_y(), (size_t)3);
    log("completed\nconfirming no throw for inbounds index ... ");
    BOOST_CHECK_NO_THROW(m.at(0, 0));
    log("completed\nconfirming throw on out of bounds ... ");
    BOOST_CHECK_THROW(m.at(3, 3), std::out_of_range);
    log("completed\nconfiriming comparison operations ... ");

    matrix<int8_t> b(2, 3, 3);
    matrix<int8_t> x(2, 3, 4);
    matrix<int8_t> y(3, 3, 3);
    BOOST_CHECK_EQUAL(b == m, true);
    BOOST_CHECK_EQUAL(b == x, false);
    BOOST_CHECK_EQUAL(b == y, false);
    BOOST_CHECK_EQUAL(b != m, false);
    BOOST_CHECK_EQUAL(b != x, true);
    BOOST_CHECK_EQUAL(b != y, true);
    log("completed\nchecking assignment opperators ... ");
    y = b;
    BOOST_CHECK_EQUAL(y.get_x(), (size_t)2);
    BOOST_CHECK_EQUAL(y.get_y(), (size_t)3);
    log("completed\nchecking contains ... ");
    BOOST_CHECK_EQUAL(y.contains(3), true);
    BOOST_CHECK_EQUAL(y.contains(5), false);
    BOOST_CHECK_EQUAL(y.contains([](int8_t x) { return x == 3; }), true);
    BOOST_CHECK_EQUAL(y.contains([](int8_t x) { return x == 5; }), false);
    log("completed\nchecking foreach ... ");
    y.foreach([](int8_t &x) {
      x = 5;
      return true;
    });
    BOOST_CHECK_EQUAL(y.contains(3), false);
    BOOST_CHECK_EQUAL(y.foreach([](int8_t &x) { return x == 5; }), true);
    log("completed\nchecking matrix operations ... ");
    y = y + 2;
    BOOST_CHECK_EQUAL(y.contains(5), false);
    BOOST_CHECK_EQUAL(y.foreach([](int8_t &x) { return x == 7; }), true);
    y = y * 2;
    BOOST_CHECK_EQUAL(y.contains(7), false);
    BOOST_CHECK_EQUAL(y.foreach([](int8_t &x) { return x == 14; }), true);
    y = y - 2;
    BOOST_CHECK_EQUAL(y.contains(14), false);
    BOOST_CHECK_EQUAL(y.foreach([](int8_t &x) { return x == 12; }), true);
    log("completed\nchecking scaler assignment operators ... ");
    y = m + 2;
    y += 2;
    BOOST_CHECK_EQUAL(y.contains(5), false);
    BOOST_CHECK_EQUAL(y.foreach([](int8_t &x) { return x == 7; }), true);
    y *= 2;
    BOOST_CHECK_EQUAL(y.contains(7), false);
    BOOST_CHECK_EQUAL(y.foreach([](int8_t &x) { return x == 14; }), true);
    y -= 2;
    BOOST_CHECK_EQUAL(y.contains(14), false);
    BOOST_CHECK_EQUAL(y.foreach([](int8_t &x) { return x == 12; }), true);
    log("completed\nchecking matrix operations ... \n");
    matrix<int> p(1, 2);
    matrix<int> r(2, 2);
    matrix<int> result(1, 2);
    p(0, 0) = 5;
    p(0, 1) = 6;

    r(0, 0) = 1;
    r(1, 0) = 2;
    r(0, 1) = 3;
    r(1, 1) = 4;

    result(0, 0) = 17;
    result(0, 1) = 39;
    BOOST_CHECK_EQUAL(result, r * p);
    log("completed small matrix mult, trying large\n");
    p.resize(6, 5);
    r.resize(4, 6);
    result.resize(4, 5);
    log("resize completed beginning setting values\n");

    p(0, 0) = 1;
    p(1, 0) = 2;
    p(2, 0) = 3;
    p(3, 0) = 4;
    p(4, 0) = 5;
    p(5, 0) = 6;

    p(0, 1) = 7;
    p(1, 1) = 8;
    p(2, 1) = 9;
    p(3, 1) = 10;
    p(4, 1) = 11;
    p(5, 1) = 12;

    p(0, 2) = 13;
    p(1, 2) = 14;
    p(2, 2) = 15;
    p(3, 2) = 16;
    p(4, 2) = 17;
    p(5, 2) = 18;

    p(0, 3) = 19;
    p(1, 3) = 20;
    p(2, 3) = 21;
    p(3, 3) = 22;
    p(4, 3) = 23;
    p(5, 3) = 24;

    p(0, 4) = 25;
    p(1, 4) = 26;
    p(2, 4) = 27;
    p(3, 4) = 28;
    p(4, 4) = 29;
    p(5, 4) = 30;

    r(0, 0) = 1;
    r(1, 0) = 2;
    r(2, 0) = 3;
    r(3, 0) = 4;

    r(0, 1) = 5;
    r(1, 1) = 6;
    r(2, 1) = 7;
    r(3, 1) = 8;

    r(0, 2) = 9;
    r(1, 2) = 10;
    r(2, 2) = 11;
    r(3, 2) = 12;

    r(0, 3) = 13;
    r(1, 3) = 14;
    r(2, 3) = 15;
    r(3, 3) = 16;

    r(0, 4) = 17;
    r(1, 4) = 18;
    r(2, 4) = 19;
    r(3, 4) = 20;

    r(0, 5) = 21;
    r(1, 5) = 22;
    r(2, 5) = 23;
    r(3, 5) = 24;

    result(0, 0) = 301;
    result(1, 0) = 322;
    result(2, 0) = 343;
    result(3, 0) = 364;

    result(0, 1) = 697;
    result(1, 1) = 754;
    result(2, 1) = 811;
    result(3, 1) = 868;

    result(0, 2) = 1093;
    result(1, 2) = 1186;
    result(2, 2) = 1279;
    result(3, 2) = 1372;

    result(0, 3) = 1489;
    result(1, 3) = 1618;
    result(2, 3) = 1747;
    result(3, 3) = 1876;

    result(0, 4) = 1885;
    result(1, 4) = 2050;
    result(2, 4) = 2215;
    result(3, 4) = 2380;
    log("values set, beginning mult op\n");

    BOOST_CHECK_EQUAL(result, p * r);

    log("totally remembered to finish this...\nchecking transpose ... \n");
    matrix<int> A(2, 2);
    matrix<int> A_prime(2, 2);
    A(0, 0) = 1;
    A(1, 0) = 3;
    A(0, 1) = 6;
    A(1, 1) = 4;
    A_prime(0, 0) = 1;
    A_prime(1, 0) = 6;
    A_prime(0, 1) = 3;
    A_prime(1, 1) = 4;
    BOOST_CHECK_EQUAL(A.Transpose(), A_prime);
    A.resize(2, 5);
    A_prime.resize(5, 2);
    A(0, 0) = 1;
    A(0, 1) = 6;
    A(0, 2) = 1;
    A(0, 3) = 6;
    A(0, 4) = 1;
    A(1, 0) = 3;
    A(1, 1) = 4;
    A(1, 2) = 3;
    A(1, 3) = 4;
    A(1, 4) = 3;
    A_prime(0, 0) = 1;
    A_prime(1, 0) = 6;
    A_prime(2, 0) = 1;
    A_prime(3, 0) = 6;
    A_prime(4, 0) = 1;
    A_prime(0, 1) = 3;
    A_prime(1, 1) = 4;
    A_prime(2, 1) = 3;
    A_prime(3, 1) = 4;
    A_prime(4, 1) = 3;
    BOOST_CHECK_EQUAL(A.Transpose(), A_prime);
    log("done\n");
  } catch (std::exception &e) {
    BOOST_FAIL(e.what());
  }
  close_log();
}
