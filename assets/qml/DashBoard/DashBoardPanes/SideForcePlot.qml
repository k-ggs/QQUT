import QtQuick
import QtQuick.Controls
import Qt.labs.platform 1.1
import QtQuick.Dialogs
import QtQuick.Layouts
import QtCharts
import "../../Widgets" as Widgets
/*
侧向力采集
  */
Item {
    id: root



    Widgets.Window {
        id: window
        anchors.fill: parent
        title: qsTr("侧向力曲线")
        //icon.source: "qrc:/assets/icons/led.svg"
        borderColor: Cpp_ThemeManager.widgetWindowBorder
        showIcon: false
        headerDoubleClickEnabled:false
        ChartView{
            anchors.fill: parent
            legend.visible: false
             ValueAxis{
                      id:axisx
                      max:50;
                      min:0;
                  }
                  ValueAxis{
                      id:axisy
                      max:50;
                      min:0;
                  }

            LineSeries{

                useOpenGL: true
            }
        }
    }
//Connections{
//target: Cpp_MDPLC
//function onSideforceChanged(){

//}
//}
}
