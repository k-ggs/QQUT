#include<gtest/gtest.h>
#include"serial.h"
TEST(serialTest,testfunc){


  Serial serial;

  EXPECT_EQ(serial.serial_open("COM3"),true);
  EXPECT_EQ(serial.serial_write("0102030405",500),10);
  for(int i=0;i<100;i++)
  {
    EXPECT_STREQ(serial.serial_read("666",5,500).toHex(' '),"01 02 03 04 05");
  }
  EXPECT_EQ(serial.serial_close(),true);
}
