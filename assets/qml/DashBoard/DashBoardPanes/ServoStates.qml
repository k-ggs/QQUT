import QtQuick
import QtQuick.Controls
import Qt.labs.platform 1.1
import QtQuick.Dialogs
import QtQuick.Layouts
import "../../Widgets" as Widgets
/*
  电机状态
  1. 电机1正限位
  2. 电机1负限位
  3. 电机2正限位
  4. 电机2负限位

  5. 急停
  */
Item {
    id: root
    Widgets.Window {
        id: window
        anchors.fill: parent
        title: qsTr("状态信息")
       // icon.source: "qrc:/assets/icons/led.svg"
        borderColor: Cpp_ThemeManager.widgetWindowBorder
        showIcon: false
        headerDoubleClickEnabled:false
        GridLayout{
            rows: 2
            columns:4
            anchors{
                fill: parent
            }
            columnSpacing: app.spacing
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:Cpp_MDPLC.axisforwardlimit ; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "轴向正限位"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:Cpp_MDPLC.axisnegativelimit ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "轴向负限位"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:Cpp_MDPLC.sideforwardlimit ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "侧向正限位"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_: Cpp_MDPLC.sidenegativelimit ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "侧向负限位"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:Cpp_MDPLC.stepforwardlimit ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "步进正限位"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:Cpp_MDPLC.stepnegativelimit ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "步进负限位"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:Cpp_MDPLC.axisservobreakdown ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "轴向伺服驱动器故障"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_: Cpp_MDPLC.sideservobreakdown ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "侧向伺服驱动器故障"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:Cpp_MDPLC.phaseorderprotection ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "相序保护"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:Cpp_MDPLC.emergencyStop ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "紧急急停按钮"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:!Cpp_MDPLC.electromagnetic_valve_s ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "电磁阀"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:!Cpp_MDPLC.power_regulator_s ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "调功阀"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:!Cpp_MDPLC.refrigerator_s ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "制冷剂"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:!Cpp_MDPLC.mechanical_pump_s ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "机械泵"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:!Cpp_MDPLC.cycle_pump_s ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "循环泵"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:!Cpp_MDPLC.mechanical_pump_s ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "串口连接状态"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:!Cpp_MDPLC.connected ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "PLC连接状态"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:!Cpp_MDPLC.axisservoenable ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "轴向伺服使能"; anchors.horizontalCenter: parent.horizontalCenter }
                }
                Column {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.spacing
                    Widgets.StatusIndicator { state_:!Cpp_MDPLC.sideservoenable ;hoveredTxt:hoverdtxt; anchors.horizontalCenter: parent.horizontalCenter }
                    Label { text: "侧向伺服使能"; anchors.horizontalCenter: parent.horizontalCenter }
                }
        }
    }
}
