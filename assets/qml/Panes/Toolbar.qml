/*
 * Copyright (c) 2020-2021 Alex Spataru <https://github.com/alex-spataru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

import QtQuick 2.3
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import "../Widgets" as Widgets

Control {
    id: root

    //
    // Reference to parent window to be able to drag it with the toolbar
    //
    property Window window

    //
    // Dummy string to increase width of buttons
    //
    readonly property string _btSpacer: "  "

    //
    // Custom signals
    //
    signal setupClicked()
    signal controlClicked()
    signal dashboardClicked()


    //
    // Aliases to button check status
    //
    property alias setupChecked: setupBt.checked
    property alias controlChecked: controlBt.checked





    //
    // Toolbar shadow
    //
    Widgets.Shadow {
        anchors.fill: bg
    }

    //
    // Background gradient + border
    //
    Rectangle {
        id: bg
        anchors.fill: parent

        gradient: Gradient {
            GradientStop { position: 0; color: Cpp_ThemeManager.toolbarGradient1 }
            GradientStop { position: 1; color: Cpp_ThemeManager.toolbarGradient2 }
        }

        Rectangle {
            border.width: 1
            anchors.fill: parent
            color: "transparent"
            visible: Cpp_ThemeManager.titlebarSeparator
            border.color: Qt.darker(Cpp_ThemeManager.toolbarGradient2, 1.5)
        }

        Rectangle {
            height: 1
            visible: Cpp_ThemeManager.titlebarSeparator
            color: Qt.darker(Cpp_ThemeManager.toolbarGradient1, 1.5)

            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
        }
    }

    //
    // Toolbar icons
    //
    RowLayout {
        spacing: app.spacing
        anchors.fill: parent
        anchors.margins: app.spacing

        Button {
            id: setupBt

            flat: true
            icon.width: 24
            icon.height: 24
            Layout.fillHeight: true
            onClicked: root.setupClicked()
            text: qsTr("设置") + _btSpacer
            icon.source: "qrc:/assets/icons/settings.svg"
            icon.color: Cpp_ThemeManager.menubarText
            palette.buttonText: Cpp_ThemeManager.menubarText
            palette.button: Cpp_ThemeManager.toolbarGradient1
            palette.window: Cpp_ThemeManager.toolbarGradient1
           // onCheckedChanged: Cpp_Misc_MacExtras.setSetupChecked(checked)

            background: Rectangle {
                radius: 3
                border.width: 1
                color: "transparent"
                border.color: "#040600"
                opacity: parent.checked ? 0.2 : 0.0

                Rectangle {
                    border.width: 1
                    color: "#626262"
                    anchors.fill: parent
                    border.color: "#c2c2c2"
                    radius: parent.radius - 1
                    anchors.margins: parent.border.width
                }
            }
        }

        Button {
            id: controlBt

            flat: true
            icon.width: 24
            icon.height: 24
            Layout.fillHeight: true

            onClicked: root.controlClicked()
            icon.source: "qrc:/assets/icons/code.svg"
            text: qsTr("控制") + _btSpacer
            icon.color: Cpp_ThemeManager.menubarText
            palette.buttonText: Cpp_ThemeManager.menubarText
            palette.button: Cpp_ThemeManager.toolbarGradient1
            palette.window: Cpp_ThemeManager.toolbarGradient1


            background: Rectangle {
                radius: 3
                border.width: 1
                color: "transparent"
                border.color: "#040600"
                opacity: parent.checked ? 0.2 : 0.0

                Rectangle {
                    border.width: 1
                    color: "#626262"
                    anchors.fill: parent
                    border.color: "#c2c2c2"
                    radius: parent.radius - 1
                    anchors.margins: parent.border.width
                }
            }
        }


        //
        // Window drag handler
        //
        Item {
            height: parent.height
            Layout.fillWidth: true

            MouseArea {
                anchors.fill: parent
                onPressedChanged: {
                    if (pressed)
                        window.startSystemMove()
                }
            }
        }





    }
}
