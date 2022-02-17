import QtQuick 2.0
import QtQuick.Controls
SpinBox {
    id: spinbox
    property real rfrom: 0.0
    property real rto: 16.6
    property int decimals: 1
    property real realValue: value /  Math.pow(10,decimals)
    from: rfrom* Math.pow(10,decimals)

    to: rto * Math.pow(10,decimals)
    stepSize: 2

    editable:true

    validator: DoubleValidator {
        bottom: Math.min(spinbox.from, spinbox.to)
        top:  Math.max(spinbox.from, spinbox.to)
    }

    textFromValue: function(value, locale) {
        return Number(value /  Math.pow(10,decimals)).toLocaleString(locale, 'f', spinbox.decimals)
    }

    valueFromText: function(text, locale) {
        return Number.fromLocaleString(locale, text) *  Math.pow(10,decimals)
    }
}

