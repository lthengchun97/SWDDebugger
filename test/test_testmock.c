#include "unity.h"
#include "swdio.h"
#include "mock_swdioHardware.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_testmock_write_one_bit(void)
{
  setSwdioHigh_Expect();      // 1
  setClockHigh_Expect();
  swdDelay_Expect();
  setClockLow_Expect();
  swdDelay_Expect();

  swdWriteBit(1);

  setSwdioLow_Expect();       // 0
  setClockHigh_Expect();
  swdDelay_Expect();
  setClockLow_Expect();
  swdDelay_Expect();

  swdWriteBit(0);
}

void test_testmock_write_bits(void)
{
  setSwdioHigh_Expect();      // 1
  setClockHigh_Expect();
  swdDelay_Expect();
  setClockLow_Expect();
  swdDelay_Expect();

  setSwdioLow_Expect();      // 0
  setClockHigh_Expect();
  swdDelay_Expect();
  setClockLow_Expect();
  swdDelay_Expect();

  setSwdioLow_Expect();      // 0
  setClockHigh_Expect();
  swdDelay_Expect();
  setClockLow_Expect();
  swdDelay_Expect();

  swdWriteBits(0x001,3);
}

void test_testmock_read_bit(void)
{
  setSwdioHigh_Expect();      // 1
  setClockHigh_Expect();
  swdDelay_Expect();
  setClockLow_Expect();
  swdDelay_Expect();

  setSwdioLow_Expect();      // 0
  setClockHigh_Expect();
  swdDelay_Expect();
  setClockLow_Expect();
  swdDelay_Expect();

  setSwdioLow_Expect();      // 0
  setClockHigh_Expect();
  swdDelay_Expect();
  setClockLow_Expect();
  swdDelay_Expect();

  swdWriteBits(0x001,3);

  getSwdio_ExpectAndReturn(0);
  setClockHigh_Expect();
  swdDelay_Expect();
  setClockLow_Expect();
  swdDelay_Expect();
  
  getSwdio_ExpectAndReturn(0);
  setClockHigh_Expect();
  swdDelay_Expect();
  setClockLow_Expect();
  swdDelay_Expect();

  getSwdio_ExpectAndReturn(1);
  setClockHigh_Expect();
  swdDelay_Expect();
  setClockLow_Expect();
  swdDelay_Expect();

  uint32_t data = swdReadBits(2);
  TEST_ASSERT_EQUAL(1,data);
}
