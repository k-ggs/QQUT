import QtQuick
import QtQuick.Controls
import Qt.labs.platform 1.1
import QtQuick.Dialogs
import QtQuick.Layouts
import QtCharts
import "../../Widgets" as Widgets
/*
轴向力采集
  */
Item {
    id: root
    Widgets.Window {
        id: window
        anchors.fill: parent
        title: qsTr("轴向力曲线")
        //icon.source: "qrc:/assets/icons/led.svg"
        borderColor: Cpp_ThemeManager.widgetWindowBorder
        showIcon: false
        headerDoubleClickEnabled:false
        ChartView{
            anchors.fill: parent
            legend.visible: false
            ValuesAxis{
            id:vlues

            }
            LineSeries{
                useOpenGL: true
            }
        }        
    }
}
