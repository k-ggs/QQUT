#include<gtest/gtest.h>
#include"md_plc.h"
#include<fmt/format.h>
#include<QDebug>
TEST(md_plcTest,testfunc){


  MD_PLC md_PLC;
  md_PLC.mdbustcpinit("127.0.0.1",502);
  bool connected=md_PLC.mD_connect();
  fmt::print("connected: {0}",connected);
  EXPECT_EQ(connected,true);
  EXPECT_EQ(md_PLC.mD_debug(false),0);
//  EXPECT_EQ(md_PLC.MD_recover_mod(MODBUS_ERROR_RECOVERY_LINK),0);
  md_PLC.mD_set_response_timeout(50);
  md_PLC.asyncServoRun(MD_PLC::kServoFunc::SERVO1,1000,2*60*1000);

  md_PLC.Getdata();

  //md_PLC.getcmdcylinder1nagativelimit(1,0,1);
}
