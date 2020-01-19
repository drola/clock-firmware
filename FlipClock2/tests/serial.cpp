#include "catch.hpp"

#include "serial.h"

TEST_CASE("Serial") {
  Serial serial0;
  SECTION("Receiving") {
    REQUIRE(serial0.hasAnythingToRead() == false);
    serial0.rx('a');
    serial0.rx('b');
    serial0.rx('c');
    REQUIRE(serial0.read() == 'a');
    REQUIRE(serial0.read() == 'b');
    REQUIRE(serial0.read() == 'c');
  }

  SECTION("Transmitting") {
    serial0.print("Hello");
    REQUIRE(serial0.hasAnythingToTx() == true);
    REQUIRE(serial0.tx() == 'H');
    REQUIRE(serial0.hasAnythingToTx() == true);
    REQUIRE(serial0.tx() == 'e');
    REQUIRE(serial0.hasAnythingToTx() == true);
    REQUIRE(serial0.tx() == 'l');
    REQUIRE(serial0.hasAnythingToTx() == true);
    REQUIRE(serial0.tx() == 'l');
    REQUIRE(serial0.hasAnythingToTx() == true);
    REQUIRE(serial0.tx() == 'o');
    REQUIRE(serial0.hasAnythingToTx() == false);
  }
}
