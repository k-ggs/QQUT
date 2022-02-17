

import QtQuick 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
/*
  伺服阀和泵开关
  1.电磁阀
  2.循环泵
  3.机械泵
  4.制冷机
  */
Control {
    id: root
    implicitHeight: layout.implicitHeight + app.spacing * 2
    //
    // Control layout
    //
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: app.spacing

        //
        // Controls
        //
        //
        GridLayout {
            id: layout
            columns: 2 //name text  unit

            rowSpacing: app.spacing+4
            columnSpacing: app.spacing

            Label{
                text:qsTr("电磁阀")+ ":"
            }
            Button{
                  text:Cpp_MDPLC.electromagnetic_valve_s?"关":"开"
                  checkable: true
                  checked: Cpp_MDPLC.electromagnetic_valve_s
                  onClicked: {
                      if(Cpp_MDPLC.electromagnetic_valve_s)
                      {
                  Cpp_MDPLC.relaySwitch(65-1,0)
                      }else{
                  Cpp_MDPLC.relaySwitch(65-1,1)
                      }

                  }


            }

            Label{
                text:qsTr("调功器")+ ":"
            }
            Button{
                text:Cpp_MDPLC.power_regulator_s?"关":"开"
                checkable: true
                checked: Cpp_MDPLC.power_regulator_s
                onClicked: {
                    if(Cpp_MDPLC.power_regulator_s)
                    {
                Cpp_MDPLC.relaySwitch(66-1,0)
                    }else{
                Cpp_MDPLC.relaySwitch(66-1,1)
                    }

                }
            }

            Label{
                text:qsTr("制冷机")+ ":"
            }
            Button{
                text:Cpp_MDPLC.refrigerator_s?"关":"开"
                checkable: true
                checked: Cpp_MDPLC.refrigerator_s
                onClicked: {
                    if(Cpp_MDPLC.refrigerator_s)
                    {
                Cpp_MDPLC.relaySwitch(67-1,0)
                    }else{
                Cpp_MDPLC.relaySwitch(67-1,1)
                    }

                }
            }

            Label{
                text:qsTr("机械泵")+ ":"
            }
            Button{
                text:Cpp_MDPLC.mechanical_pump_s?"关":"开"
                checkable: true
                checked: Cpp_MDPLC.mechanical_pump_s
                onClicked: {
                    if(Cpp_MDPLC.mechanical_pump_s)
                    {
                Cpp_MDPLC.relaySwitch(68-1,0)
                    }else{
                Cpp_MDPLC.relaySwitch(68-1,1)
                    }

                }
            }


            Label{
                text:qsTr("循环泵")+ ":"
            }
            Button{
                text:Cpp_MDPLC.cycle_pump_s?"关":"开"
                checkable: true
                checked: Cpp_MDPLC.cycle_pump_s
                onClicked: {
                    if(Cpp_MDPLC.cycle_pump_s)
                    {
                Cpp_MDPLC.relaySwitch(69-1,0)
                    }else{
                Cpp_MDPLC.relaySwitch(69-1,1)
                    }

                }
            }














            //
            // Spacer
            //
            Item {
                Layout.minimumHeight: app.spacing / 2
                Layout.maximumHeight: app.spacing / 2
            } Item {
                Layout.minimumHeight: app.spacing / 2
                Layout.maximumHeight: app.spacing / 2
            }



        }

        //
        // Vertical spacer
        //
        Item {
            Layout.fillHeight: true
        }
    }
}


