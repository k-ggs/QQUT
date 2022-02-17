import QtQuick
import QtQuick.Controls
Item {
    implicitWidth: 35
    implicitHeight: 35
    id:root
    property bool state_: false
    property color happend_Color: "red"
    property color unhappend_Color:"Green"
    property string hoveredTxt: "hoveredtext"
    property bool showTips: false

    Rectangle{
        id:indicator
        property int r: Math.min(root.width,root.height)
        property color cusColor: state_?happend_Color:unhappend_Color

        gradient: Gradient{

        GradientStop{position: 0.0;color: indicator.cusColor}
        GradientStop{position: 0.5;color:Qt.darker(indicator.cusColor) }
        GradientStop{position: 1;color:Qt.lighter(indicator.cusColor)  }
        }
       // color:state_?happend_Color:unhappend_Color
        width:  r
        height: r
        radius: r/2
        ToolTip.visible: hoverhandler.hovered&&showTips
        ToolTip.text: hoveredTxt
        ToolTip.delay: 200



        border.color: Qt.darker(color)
        border.width: 2


        HoverHandler{
            id:hoverhandler


        }
    }


}
