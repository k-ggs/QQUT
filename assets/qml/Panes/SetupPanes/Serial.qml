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
    property alias port: _portCombo.currentIndex
    property alias baudRate: _baudCombo.currentIndex


    property  bool connected: false



    //
    // Control layout
    //
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: app.spacing

        //
        // Controls
        //
        GridLayout {
            id: layout
            columns: 2
            Layout.fillWidth: true
            rowSpacing: app.spacing
            columnSpacing: app.spacing

            //
            // COM port selector
            //
            Label {
                opacity: enabled ? 1 : 0.5
                text: qsTr("串口端口") + ":"
                enabled: !connected
            } ComboBox {
                id: _portCombo
                Layout.fillWidth: true
                opacity: enabled ? 1 : 0.5
                model: Cpp_IO_Serial.portList
                enabled: !connected


            }

            //
            // Baud rate selector
            //
            Label {
                opacity: enabled ? 1 : 0.5
                text: qsTr("波特率") + ":"
            } ComboBox {
                id: _baudCombo
                editable: true
                currentIndex: 4
                Layout.fillWidth: true
                //model: Cpp_IO_Serial.baudRateList

                validator: IntValidator {
                    bottom: 1
                }

                onAccepted: {
                    if (find(editText) === -1)
                        Cpp_IO_Serial.appendBaudRate(editText)
                }

                onCurrentTextChanged: {
                    var value = currentText
                    Cpp_IO_Serial.baudRate = value
                }
            }



            //
            // Spacer
            //
            Item {
                Layout.minimumHeight: app.spacing / 2
                Layout.maximumHeight: app.spacing / 2
            } Item {
                Layout.minimumHeight: app.spacing / 2
                Layout.maximumHeight: app.spacing / 2
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


