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

Control {
    id: root
    implicitHeight: layout.implicitHeight + app.spacing * 2
    //
    // Access to properties
    //
    property alias address: _address.text
    property alias tcpPort: _tcpPort.text
    //
    // Signals
    //
    signal uiChanged()
    //
    // Layout
    //

    ColumnLayout {
        id: layout
        anchors.fill: parent
        anchors.margins: app.spacing


        GridLayout {
            columns: 2
            Layout.fillWidth: true
            rowSpacing: app.spacing
            columnSpacing: app.spacing
            //
            // Address
            //
            Label {
                opacity: enabled ? 1 : 0.5
                enabled: !Cpp_MDPLC.connected
                text: qsTr("IP地址") + ":"
            } TextField {
                id: _address
                Layout.fillWidth: true
                enabled: !Cpp_MDPLC.connected
                opacity: enabled ? 1 : 0.5
            }
            //
            // TCP port
            //
            Label {
                text: qsTr("Port") + ":"
                opacity: enabled ? 1 : 0.5
                enabled: !Cpp_MDPLC.connected
            } TextField {
                id: _tcpPort
                opacity: enabled ? 1 : 0.5
                enabled: !Cpp_MDPLC.connected
                Layout.fillWidth: true               
                validator: IntValidator {
                    bottom: 0
                    top: 65535
                }
            }        
        Button{text:!Cpp_MDPLC.connected?"连接":"断开"
        onClicked: {
        if(!Cpp_MDPLC.connected){
            Cpp_MDPLC.mdbustcpinit(_address.text,_tcpPort.text)
            Cpp_MDPLC.mD_connect()

        }
        else{
             Cpp_MDPLC.mD_close()
        }
        }
        }
        }
        //
        // Spacer
        //
        Item {
            Layout.fillHeight: true
            Layout.minimumHeight: app.spacing
        }
        //
        // Spacer
        //
        Item {
            Layout.fillHeight: true
        }
    }
}
