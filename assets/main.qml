import QtQuick
import "../assets/qml/Windows" as Windows
import QtQuick.Controls

Item{
    id: app

    //
    // Global propeties
    //
    readonly property int spacing: 8
    readonly property string monoFont: "Roboto Mono"
     property Windows.MainWindow mainWindow: null

    property int plot_xrange: 1000*60 //1分钟
//
// MainWindow
//
Loader {
    asynchronous: true
    sourceComponent: Windows.MainWindow {
        Component.onCompleted: {

            app.forceActiveFocus()
            app.mainWindow = this
        }
    }
}
}
