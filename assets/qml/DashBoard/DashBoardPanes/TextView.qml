import QtQuick
import QtQuick.Controls
import Qt.labs.platform 1.1
import QtQuick.Dialogs
import QtQuick.Layouts
import "../../Widgets" as Widgets
/*
  六个继电器模组状态
  1.循环泵
  2.电磁阀
  3.机械泵
  4.制冷剂
  5.
  */
Item {
    id: root
    Widgets.Window {
        id: window
        anchors.fill: parent
        title: qsTr("数据显示")
       // icon.source: "qrc:/assets/icons/led.svg"
        borderColor: Cpp_ThemeManager.widgetWindowBorder
        showIcon: false
        headerDoubleClickEnabled:false
        GridLayout{

            columns:4
            anchors{
                fill: parent
            }
            columnSpacing: 1
            rowSpacing   : app.spacing
                Label { text: " 轴向拉压力(KG):";}
                TextField{text: Cpp_MDPLC.axisforce;readOnly: true}
                Label { text: " 侧向扭力(KG):";}
                TextField{text: Cpp_MDPLC.sideforce;readOnly: true}
                Label { text: " 温度1(S型热电偶)(℃):";}
                TextField{text: Cpp_MDPLC.temperatureS1;readOnly: true}
                Label { text: " 温度2(S型热电偶)(℃):";}
                TextField{text: Cpp_MDPLC.temperatureS2;readOnly: true}
                Label { text: " 温度3(K型热电偶)(℃):";}
                TextField{text: Cpp_MDPLC.temperatureK3;readOnly: true}
                Label { text: " 真空计(Pa):";}
                TextField{readOnly: true}
                Label { text: " 红外测温仪(℃):";  }
                TextField{readOnly: true}
        }
    }
}
