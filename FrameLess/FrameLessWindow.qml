import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.settings
import QtQuick.Window
Window{
    property string fontbrands: fontBrands.font
    property string fonttegular: fontRegular.font
    property string fontsolid: fontSolid.font
    FontLoader{
        id:fontBrands
    source: "qrc:/asset/fontawesome/otfs/Font Awesome 6 Brands-Regular-400.otf"
    }
    FontLoader{
        id:fontRegular
    source: "qrc:/asset/fontawesome/otfs/Font Awesome 6 Free-Regular-400.otf"
    }
    FontLoader{
        id:fontSolid
    source: "qrc:/asset/fontawesome/otfs/Font Awesome 6 Free-Solid-900.otf"
    }
flags: Qt.FramelessWindowHint
FrameLessTitleBar{
width: parent.width
height: 20
}

}
