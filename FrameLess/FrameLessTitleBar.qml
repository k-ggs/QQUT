import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
Rectangle {
    ///main Window
    property Window mainWindow
    property int splitline_width : 0
    property color spliterline_color: "black"
    property string iconsource: ""

RowLayout{
anchors.fill: parent
///1icon
Item{
Layout.preferredWidth:50
Layout.fillHeight: true
Image {
anchors.fill: parent
fillMode: Image.PreserveAspectFit //均匀缩放
source: iconsource
}
}
///2MenuBar
Item{
Layout.fillWidth:true
Layout.fillHeight: true
}
///splitline
Rectangle{
Layout.fillHeight: true
Layout.preferredWidth: splitline_width
border.width: splitline_width
border.color:spliterline_color
}
///3min max close
Item{

Layout.preferredWidth:150
Layout.fillHeight:true
RowLayout{
    anchors.fill: parent
    spacing: 0
Button{
    flat: true
    Layout.fillWidth:true
    Layout.fillHeight: true

}
Button{
    flat: true
    Layout.fillWidth:true
    Layout.fillHeight: true
}
Button{
     flat: true
    Layout.fillWidth:true
    Layout.fillHeight: true
}
}
}
}
}
