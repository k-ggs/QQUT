﻿/*
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
import QtQuick.Controls 2.3

MenuBar {
    id: root

    //
    // Set background color
    //
    background: Rectangle {
        color: "transparent"
    }

    //
    // Palette
    //
    palette.text: Cpp_ThemeManager.menubarText
    palette.base: Cpp_ThemeManager.toolbarGradient1
    palette.window: Cpp_ThemeManager.toolbarGradient2
    palette.highlightedText: Cpp_ThemeManager.highlightedText

    //
    // File menu
    //
    Menu {
        title: qsTr("File")

        DecentMenuItem {
            sequence: "ctrl+j"
            text: qsTr("Select JSON file") + "..."
            onTriggered: Cpp_JSON_Generator.loadJsonMap()
        }

        MenuSeparator {}

        Menu {
            title: qsTr("CSV export")

            DecentMenuItem {
                checkable: true
                text: qsTr("Enable CSV export")

            }

            DecentMenuItem {
                sequence: "ctrl+shift+o"
                enabled: Cpp_CSV_Export.isOpen

            }
        }

        DecentMenuItem {
            sequence: "ctrl+o"
            text: qsTr("Replay CSV") + "..."

        }

        MenuSeparator {}

        DecentMenuItem {
            sequence: "ctrl+p"
            text: qsTr("Print") + "..."

        }

        DecentMenuItem {
            sequence: "ctrl+s"

            text: qsTr("Export console output") + "..."
        }

        MenuSeparator {}

        DecentMenuItem {
            text: qsTr("Quit")
            onTriggered: Qt.quit()
            sequence: "ctrl+q"
        }
    }

    //
    // Edit menu
    //
    Menu {
        title: qsTr("Edit")

        DecentMenuItem {
            text: qsTr("Copy")
            sequence: "ctrl+c"
            onTriggered: mainWindow.consoleCopy()
        }

        DecentMenuItem {
            sequence: "ctrl+a"
            text: qsTr("Select all") + "..."
            onTriggered: mainWindow.consoleSelectAll()
        }

        DecentMenuItem {
            sequence: "ctrl+d"
            onTriggered: mainWindow.consoleClear()
            text: qsTr("Clear console output")
        }

        MenuSeparator{}

        Menu {
            title: qsTr("Communication mode")

            DecentMenuItem {
                checkable: true
                text: qsTr("Device sends JSON")
                checked: Cpp_JSON_Generator.operationMode === 1
                onTriggered: Cpp_JSON_Generator.operationMode = checked ? 1 : 0
            }

            DecentMenuItem {
                checkable: true
                text: qsTr("Load JSON from computer")
                checked: Cpp_JSON_Generator.operationMode === 0
                onTriggered: Cpp_JSON_Generator.operationMode = checked ? 0 : 1
            }
        }
    }

    //
    // View menu
    //
    Menu {
        title: qsTr("View")

        DecentMenuItem {
            checkable: true
            sequence: "ctrl+t"
            text: qsTr("Console")
            checked: mainWindow.consoleVisible
            onTriggered: mainWindow.showConsole()
            onCheckedChanged: {
                if (mainWindow.consoleVisible !== checked)
                    checked = mainWindow.consoleVisible
            }
        }

        DecentMenuItem {
            checkable: true
            sequence: "ctrl+d"
            text: qsTr("Dashboard")
            checked: mainWindow.dashboardVisible
            enabled: Cpp_UI_Dashboard.available
            onTriggered: mainWindow.showDashboard()
            onCheckedChanged: {
                if (mainWindow.dashboardVisible !== checked)
                    checked = mainWindow.dashboardVisible
            }
        }

        MenuSeparator {}

        DecentMenuItem {
            checkable: true
            sequence: "ctrl+,"
            checked: mainWindow.setupVisible
            text: qsTr("Show setup pane")
            onTriggered: mainWindow.showSetup()
        }

        MenuSeparator {}

        DecentMenuItem {
            sequence: "f11"
            onTriggered: mainWindow.toggleFullscreen()
            text: mainWindow.isFullscreen ? qsTr("Exit full screen") :
                                            qsTr("Enter full screen")
        }
    }


    //
    // Help menu
    //
    Menu {
        title: qsTr("Help")

        DecentMenuItem {
           //onTriggered: app.aboutDialog.show()
            text: qsTr("About %1").arg(Cpp_AppName)
        }

        DecentMenuItem {
            text: qsTr("About %1").arg("Qt")
           //onTriggered: Cpp_Misc_Utilities.aboutQt()
        }

        MenuSeparator {
            visible: Cpp_UpdaterEnabled
            enabled: Cpp_UpdaterEnabled
        }

        DecentMenuItem {
            checkable: true
            visible: Cpp_UpdaterEnabled
            enabled: Cpp_UpdaterEnabled
          //  checked: mainWindow.automaticUpdates
          //  onTriggered: mainWindow.automaticUpdates = checked
            text: qsTr("Auto-updater")
        }

        DecentMenuItem {
            visible: Cpp_UpdaterEnabled
            enabled: Cpp_UpdaterEnabled
          //  onTriggered: app.checkForUpdates()
            text: qsTr("Check for updates") + "..."
        }

        MenuSeparator{}

        DecentMenuItem {
            text: qsTr("Project website") + "..."
           // onTriggered: Qt.openUrlExternally("https://www.alex-spataru.com/serial-studio")
        }

        DecentMenuItem {
            sequence: "f1"
            text: qsTr("Documentation/wiki") + "..."
           // onTriggered: Qt.openUrlExternally("https://github.com/Serial-Studio/Serial-Studio/wiki")
        }

        MenuSeparator{}

        DecentMenuItem {
            text: qsTr("Report bug") + "..."
          //  onTriggered: Qt.openUrlExternally("https://github.com/Serial-Studio/Serial-Studio/issues")
        }
    }
}
