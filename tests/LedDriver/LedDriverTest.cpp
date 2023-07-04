extern "C"
{
#include "LedDriver.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LedDriver)
{
    void setup()
    {
      LedDriver_Create();
    }

    void teardown()
    {
       LedDriver_Destroy();
    }
};

// LED Driver Test list:
// 1. All LEDs are off after the driver is initialized.
// 2. A single LED can be turned on.
// 3. A single LED can be turned off.
// 4. Check boundary conditions.
// 5. Check out-of-boundary conditions.

TEST(LedDriver, LedsOffAfterCreate)
{
  uint8_t virtualLeds = 0xff;
  LedDriver_Create(); //&virtualLeds
  LONGS_EQUAL(0, virtualLeds);
  FAIL("Start here");
}

