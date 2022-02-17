

import QtQuick 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import Qt.labs.settings 1.0

import "../Widgets" as Widgets
import "ControlPanes" as ControlPanes

Item {
    id: root

    //
    // Custom properties
    //
    property int setupMargin: 0
    property int displayedWidth: 380 + app.spacing * 1.5
    readonly property int maxItemWidth: column.width - 2 * spacing

    //
    // Displays the setup panel
    //
    function show() {
        setupMargin = 0
    }

    //
    // Hides the setup panel
    //
    function hide() {
        setupMargin = -1 * displayedWidth
    }
    //
    // Animations
    //
    visible: setupMargin > -1 * displayedWidth
    Behavior on setupMargin {NumberAnimation{}}

    //
    // Save settings
    //
    Settings {
        //
        // Misc settings
        //
        property alias tabIndex: tab.currentIndex
        //
        // Serial settings
        //
    }
    //
    // Window
    //
    Widgets.Window {
        gradient: true
        title: qsTr("控制")
        anchors.fill: parent
        anchors.leftMargin: 0
        headerDoubleClickEnabled: false
        icon.source: "qrc:/assets/icons/settings.svg"
        anchors.margins: (app.spacing * 1.5) - 5
        backgroundColor: Cpp_ThemeManager.paneWindowBackground

        //
        // Control arrangement
        //
        ColumnLayout {
            id: column
            anchors.fill: parent
            spacing: app.spacing / 2
            anchors.margins: app.spacing * 1.5
            //
            // Spacer
            //
            Item {
                height: app.spacing / 2
            }
            //
            // Spacer
            //
            Item {
                height: app.spacing / 2
            }
            //
            // Tab bar
            //
            TabBar {
                height: 24
                id: tab
                Layout.fillWidth: true
                Layout.maximumWidth: root.maxItemWidth
                TabButton {
                    text: qsTr("电机")
                    height: tab.height + 3
                    width: implicitWidth + 2 * app.spacing
                }
                TabButton {
                    text: qsTr("伺服阀与泵")
                    height: tab.height + 3
                    width: implicitWidth + 2 * app.spacing
                }
            }
            //
            // Tab bar contents
            //
            StackLayout {
                id: stack
                clip: true
                Layout.fillWidth: true
                Layout.fillHeight: false
                currentIndex: tab.currentIndex
                Layout.topMargin: -parent.spacing - 1
                Layout.minimumHeight: implicitHeight
                Layout.maximumHeight: implicitHeight
                Layout.preferredHeight: implicitHeight
                onCurrentIndexChanged: updateHeight()
                Component.onCompleted: updateHeight()
                function updateHeight() {
                    stack.implicitHeight = 0

                    switch (currentIndex) {
                    case 0:
                        stack.implicitHeight = servo.implicitHeight
                        break
                    case 1:
                        stack.implicitHeight = fpstates.implicitHeight
                        break

                    default:
                        stack.implicitHeight = 0
                        break
                    }
                }
                ControlPanes.Servo{
                    id: servo
                    background: TextField {
                        enabled: false
                        palette.base: Cpp_ThemeManager.setupPanelBackground
                    }
                }
                ControlPanes.FPStates{

                    id: fpstates
                    background: TextField {
                        enabled: false
                        palette.base: Cpp_ThemeManager.setupPanelBackground
                    }
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
}
