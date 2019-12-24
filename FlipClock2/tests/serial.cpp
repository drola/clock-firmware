#include "catch.hpp"

#include "serial.h"

TEST_CASE("Serial") {
  Serial serial0;
  SECTION("Receiving") { REQUIRE(1 == 1); }

  SECTION("Transmitting") {
      serial0.print("Hello");
      REQUIRE(serial0.canTx() == true);
      REQUIRE(serial0.tx() == 'H');
      REQUIRE(serial0.canTx() == true);
      REQUIRE(serial0.tx() == 'e');
      REQUIRE(serial0.canTx() == true);
      REQUIRE(serial0.tx() == 'l');
      REQUIRE(serial0.canTx() == true);
      REQUIRE(serial0.tx() == 'l');
      REQUIRE(serial0.canTx() == true);
      REQUIRE(serial0.tx() == 'o');
      REQUIRE(serial0.canTx() == false);
  }
}
