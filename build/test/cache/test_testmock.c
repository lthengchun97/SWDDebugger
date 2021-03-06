#include "build/temp/_test_testmock.c"
#include "mock_swdioHardware.h"
#include "swdio.h"
#include "unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}



void test_testmock_write_one_bit(void)

{

  setSwdioHigh_CMockExpect(16);

  setClockHigh_CMockExpect(17);

  swdDelay_CMockExpect(18);

  setClockLow_CMockExpect(19);

  swdDelay_CMockExpect(20);



  swdWriteBit(1);



  setSwdioLow_CMockExpect(24);

  setClockHigh_CMockExpect(25);

  swdDelay_CMockExpect(26);

  setClockLow_CMockExpect(27);

  swdDelay_CMockExpect(28);



  swdWriteBit(0);

}



void test_testmock_write_bits(void)

{

  setSwdioHigh_CMockExpect(35);

  setClockHigh_CMockExpect(36);

  swdDelay_CMockExpect(37);

  setClockLow_CMockExpect(38);

  swdDelay_CMockExpect(39);



  setSwdioLow_CMockExpect(41);

  setClockHigh_CMockExpect(42);

  swdDelay_CMockExpect(43);

  setClockLow_CMockExpect(44);

  swdDelay_CMockExpect(45);



  setSwdioLow_CMockExpect(47);

  setClockHigh_CMockExpect(48);

  swdDelay_CMockExpect(49);

  setClockLow_CMockExpect(50);

  swdDelay_CMockExpect(51);



  swdWriteBits(0x001,3);

}



void test_testmock_read_bit(void)

{

  setSwdioHigh_CMockExpect(58);

  setClockHigh_CMockExpect(59);

  swdDelay_CMockExpect(60);

  setClockLow_CMockExpect(61);

  swdDelay_CMockExpect(62);



  setSwdioLow_CMockExpect(64);

  setClockHigh_CMockExpect(65);

  swdDelay_CMockExpect(66);

  setClockLow_CMockExpect(67);

  swdDelay_CMockExpect(68);



  setSwdioLow_CMockExpect(70);

  setClockHigh_CMockExpect(71);

  swdDelay_CMockExpect(72);

  setClockLow_CMockExpect(73);

  swdDelay_CMockExpect(74);



  swdWriteBits(0x001,3);



  getSwdio_CMockExpectAndReturn(78, 0);

  setClockHigh_CMockExpect(79);

  swdDelay_CMockExpect(80);

  setClockLow_CMockExpect(81);

  swdDelay_CMockExpect(82);



  getSwdio_CMockExpectAndReturn(84, 0);

  setClockHigh_CMockExpect(85);

  swdDelay_CMockExpect(86);

  setClockLow_CMockExpect(87);

  swdDelay_CMockExpect(88);



  getSwdio_CMockExpectAndReturn(90, 1);

  setClockHigh_CMockExpect(91);

  swdDelay_CMockExpect(92);

  setClockLow_CMockExpect(93);

  swdDelay_CMockExpect(94);



  uint32_t data = swdReadBits(2);

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((data)), (

 ((void *)0)

 ), (UNITY_UINT)(97), UNITY_DISPLAY_STYLE_INT);

}
