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
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import Qt.labs.settings 1.0

import "../Widgets" as Widgets
import "SetupPanes" as SetupPanes

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

        property alias baudRate: serial.baudRate




        //
        // Network settings
        //
        property alias address: network.address
        property alias tcpPort: network.tcpPort





    }



    //
    // Window
    //
    Widgets.Window {
        gradient: true
        title: qsTr("设置")
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
            // Enable/disable CSV logging
            //
            RowLayout {
                Layout.fillWidth: true

                Switch {
                    id: csvLogging
                    text: qsTr("创建CSV文件")
                    Layout.alignment: Qt.AlignVCenter
                    checked: Cpp_CSV_Export.exportEnabled
                    Layout.maximumWidth: root.maxItemWidth
                    palette.highlight: Cpp_ThemeManager.csvCheckbox

                    onCheckedChanged:  {
                        if (Cpp_CSV_Export.exportEnabled !== checked)
                            Cpp_CSV_Export.exportEnabled = checked
                    }
                }

                Item {
                    Layout.fillWidth: true
                }


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
                    text: qsTr("ModbusRTU")
                    height: tab.height + 3
                    width: implicitWidth + 2 * app.spacing
                }

                TabButton {
                    text: qsTr("ModbusTCP")
                    height: tab.height + 3
                    width: implicitWidth + 2 * app.spacing
                }





                TabButton {
                    text: qsTr("Settings")
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
                        stack.implicitHeight = serial.implicitHeight
                        break
                    case 1:
                        stack.implicitHeight = network.implicitHeight
                        break
                    case 2:
                        stack.implicitHeight = settings.implicitHeight
                        break

                    default:
                        stack.implicitHeight = 0
                        break
                    }
                }

                SetupPanes.Serial {
                    id: serial
                    background: TextField {
                        enabled: false
                        palette.base: Cpp_ThemeManager.setupPanelBackground
                    }
                }

                SetupPanes.Network {
                    id: network




                    background: TextField {
                        enabled: false
                        palette.base: Cpp_ThemeManager.setupPanelBackground
                    }
                }




                SetupPanes.Settings {
                    id: settings
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
