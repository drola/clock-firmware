#include "catch.hpp"

#include "ring_buffer.h"

TEST_CASE("Ring Buffer") {
  RingBuffer<4> rb4;
  REQUIRE(rb4.canRead() == false);
  rb4.write(37);
  REQUIRE(rb4.canRead() == true);
  REQUIRE(rb4.read() == 37);
  REQUIRE(rb4.canRead() == false);

  //Overflow test
  REQUIRE(rb4.write(1) == true);
  REQUIRE(rb4.canRead() == true);
  REQUIRE(rb4.write(2) == true);
  REQUIRE(rb4.canRead() == true);
  REQUIRE(rb4.write(3) == true);
  REQUIRE(rb4.canRead() == true);
  REQUIRE(rb4.write(4) == false);
  REQUIRE(rb4.canRead() == true);

  //Read in correct order
  REQUIRE(rb4.canRead() == true);
  REQUIRE(rb4.read() == 1);
  REQUIRE(rb4.canRead() == true);
  REQUIRE(rb4.read() == 2);
  REQUIRE(rb4.canRead() == true);
  REQUIRE(rb4.read() == 3);
  REQUIRE(rb4.canRead() == false);

  //Make sure nothing is lost when wrapping around
  REQUIRE(rb4.write(5) == true);
  REQUIRE(rb4.canRead() == true);
  REQUIRE(rb4.read() == 5);
  REQUIRE(rb4.canRead() == false);
  REQUIRE(rb4.write(6) == true);
  REQUIRE(rb4.canRead() == true);
  REQUIRE(rb4.read() == 6);
  REQUIRE(rb4.canRead() == false);
  REQUIRE(rb4.write(7) == true);
  REQUIRE(rb4.canRead() == true);
  REQUIRE(rb4.read() == 7);
  REQUIRE(rb4.canRead() == false);
  REQUIRE(rb4.write(8) == true);
  REQUIRE(rb4.canRead() == true);
  REQUIRE(rb4.read() == 8);
  REQUIRE(rb4.canRead() == false);
}
