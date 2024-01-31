// Quincy Mattor
// Copyright 2023

#include "libqm.hpp"
#include <thread>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

#include <boost/test/unit_test.hpp>
using namespace libqm;

// void timeout_thread() { QM_exception(std::runtime_error("timeout")); }

// BOOST_AUTO_TEST_CASE(TEST_TIMER) {
//   init_log("TEST_TIMER.txt");
//   try {
//   } catch (...) {
//   }
//   close_log();
// }

BOOST_AUTO_TEST_CASE(TEST_MATRIX) {
  init_log("TEST_MATRIX.log");
  log_setverbosity(verbosity::DEBUG);
  try {
    log("BEGIN MATRIX\n");
    log("beigning signal alarm for 5 seconds\n");
    matrix<int8_t> m(2, 3, 3);
    log("matrix is initialized\nconfirming matrix is initalized to the correct "
        "values ... ");
    BOOST_CHECK_EQUAL(m(1, 2), 3);
    BOOST_CHECK_EQUAL(m(0, 1), 3);
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
    y.foreach ([](int8_t &x) {
      x = 5;
      return true;
    });
    BOOST_CHECK_EQUAL(y.contains(3), false);
    BOOST_CHECK_EQUAL(y.foreach ([](int8_t &x) { return x == 5; }), true);
    log("completed\nchecking matrix operations ... ");
    y = y + 2;
    BOOST_CHECK_EQUAL(y.contains(5), false);
    BOOST_CHECK_EQUAL(y.foreach ([](int8_t &x) { return x == 7; }), true);
    y = y * 2;
    BOOST_CHECK_EQUAL(y.contains(7), false);
    BOOST_CHECK_EQUAL(y.foreach ([](int8_t &x) { return x == 14; }), true);
    y = y - 2;
    BOOST_CHECK_EQUAL(y.contains(14), false);
    BOOST_CHECK_EQUAL(y.foreach ([](int8_t &x) { return x == 12; }), true);
    log("completed\nchecking scaler assignment operators ... ");
    y = m + 2;
    y += 2;
    BOOST_CHECK_EQUAL(y.contains(5), false);
    BOOST_CHECK_EQUAL(y.foreach ([](int8_t &x) { return x == 7; }), true);
    y *= 2;
    BOOST_CHECK_EQUAL(y.contains(7), false);
    BOOST_CHECK_EQUAL(y.foreach ([](int8_t &x) { return x == 14; }), true);
    y -= 2;
    BOOST_CHECK_EQUAL(y.contains(14), false);
    BOOST_CHECK_EQUAL(y.foreach ([](int8_t &x) { return x == 12; }), true);
    log("completed\nchecking matrix operations ... ");

  } catch (...) {
  }
  close_log();
}
