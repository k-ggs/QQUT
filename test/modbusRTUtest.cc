
#include<gtest/gtest.h>
#include"modbusrtu.h"
#include<fmt/format.h>
#include<QDebug>
TEST(modbusrtuTest,testfunc){


  modbusRTU modbusrtu;

  EXPECT_EQ(modbusrtu.mD_connect(),true);
  EXPECT_EQ(modbusrtu.mD_debug(true),0);
  int slave=1;
  int nb=5;
  int start=0;
  uint8_t *dest=(uint8_t*)malloc(sizeof(uint8_t)*nb);

//test read bits
  modbusrtu.mD_read_bits(slave,start,nb,dest);
  for(int i=0;i<nb;i++){
    qDebug()<<"read bits: "<<dest[i];
}
free(dest);
//test write read bits
  start=1;
  dest=(uint8_t*)malloc(sizeof(uint8_t)*1);
  modbusrtu.mD_write_bit(slave,start,0);
  modbusrtu.mD_read_bits(slave,start,1,dest);
  qDebug()<<"MD_write_bit: "<<dest[0];


  free(dest);
//test write resg bits
   slave=1;
   nb=5;
   start=0;
   uint16_t *dest16=(uint16_t*)malloc(sizeof(uint16_t)*nb);
   memset(dest16,0,nb);

  int size= modbusrtu.mD_read_registers(slave,start,nb,dest16);
   qDebug()<<"read_registers size: "<<size;
   for(int i=0;i<nb;i++){

     qDebug()<<"read_registers: "<<dest16[i];

   }

   free(dest16);


    ASSERT_NO_THROW(modbusrtu.mD_close());
}
