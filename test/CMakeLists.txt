CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
project(test VERSION 0.1 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

enable_testing()




#message(STATUS "MMSG=${head_fils}")

#test serialport
add_executable(serialtest
               serialtest.cc
               ${head_fils}
               ${source_files}
               )
target_link_libraries(serialtest
                      GTest::gtest
                      GTest::gtest_main
                      ${libs}
                      )
                      
#test modbusRTU
add_executable(modbusRTUtest
               modbusRTUtest.cc
               ${head_fils}
               ${source_files}
               )
target_link_libraries(modbusRTUtest
                      GTest::gtest
                      GTest::gtest_main
                      ${libs}
                      )


#test md_plc
add_executable(md_plctest
               md_plctest.cc
               ${head_fils}
               ${source_files}
               )
target_link_libraries(md_plctest
                      GTest::gtest
                      GTest::gtest_main
                      ${libs}
                      )
