

import QtQuick
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import Qt.labs.settings
import "../../Widgets"
Control {
id: root
implicitHeight: layout.implicitHeight + app.spacing * 2
/// 0轴向 1侧向
property int   selectedservo: selectservo.currentIndex
Settings{
    property alias currentservo: selectservo.currentIndex
    /// @undo 添加其它的属性
}
ListModel{
id:grdmodel
ListElement{
name:"轴向伺服"

}
ListElement{
name:"侧向伺服"

}
}
ColumnLayout{
  anchors.fill: parent
  anchors.margins: app.spacing

 GridLayout {
  id: layout
  columns: 3 //name text  unit
  rowSpacing: app.spacing+4
  columnSpacing: app.spacing
  Label{text:"伺服:"}
  ComboBox{
      id:selectservo
      model: grdmodel
  }
  Label{}

  Label{text: "伺服使能:"}
  Button{
  text: "使能开"
  onClicked: {
  Cpp_MDPLC.servoEnable(selectedservo,true)
  }
  }
  Button{
  text: "使能关"
  onClicked: {
  Cpp_MDPLC.servoEnable(selectedservo,false)
  }
  }


  //方向状态显示
  Label{
  text:qsTr("伺服方向")+ ":"
  }
  Label{text: "正转";}
  Label{text: "反转";}

  Label{
      text:qsTr("运行速度")+ ":"
  }
  FloatSpinbox{
  id:runspeed
  rfrom:0.1
  rto:16.6
  }  
  Label{
  text:"mm/s"
  }

  Label{
  text:qsTr("加速时间")+ ":"
  }  
  TextField{
  id:ac_time
  validator: RegularExpressionValidator { regularExpression: /^\d+$/ }
  }
  Label{
  text:"ms"
  }

  Label{
      text:qsTr("减速时间")+ ":"
  }
  TextField{
  id:dc_time
  validator: RegularExpressionValidator { regularExpression: /^\d+$/ }
  }
  Label{
  text:"ms"
  }

  Label{
  text:qsTr("点动速度")+ ":"
  }
  FloatSpinbox{
  id:inching_speed
  rfrom:0.1
  rto:16.6
  }
  Label{
  text:"mm/s"
  }

  Label{
  text:qsTr("点动增量")+ ":"
  }
  FloatSpinbox{
  id:inching_increment
  rfrom:0.1
  rto:16.6
  }
  Label{
  text:"mm"
  }

  Label{text: "参数配置确认:"}
  Button{text: "确认"
  onClicked: {

  parameter_configur(runspeed.realValue,parseFloat(ac_time.text),parseFloat(dc_time.text)
                     ,inching_speed.realValue,inching_increment.realValue)
  }
  }
  Label{}

  Label{
  text:qsTr("点动控制")+ ":"
  }
  Button{
      text: qsTr("正转")
      onClicked: {
Cpp_MDPLC.inchingRun(selectedservo,true)
      }
 }
  Button{
      text: qsTr("正传停止")
       onClicked: {
Cpp_MDPLC.stopinchingRun(selectedservo,true)
       }
}

 Label{
   }
 Button{
      text: qsTr("反转")
       onClicked: {
Cpp_MDPLC.inchingRun(selectedservo,false)
       }
 }
 Button{
      text: qsTr("反传停止")
       onClicked: {
Cpp_MDPLC.stopinchingRun(selectedservo,false)
       }
}

 Label{
      text:qsTr("加载力控制")+ ":"
  }
 SpinBox{
id:force_control
   from:selectedservo==0?-2000:-1000
   to:selectedservo==0? 2000:1000
 editable: true
 }
 Button{
     text: qsTr("运行")
     onClicked: {
Cpp_MDPLC.asyncServoRun(selectedservo,force_control.value)
     }
 }

///疲劳测试 往返周期运动
Label{
    id:period
    text:qsTr("周期控制")+ ":"
 }
SpinBox{
    id:loop_times
    from:0
    to:10000
    editable: true
}
Button{
 text: qsTr("运行")
 onClicked: {
 Cpp_MDPLC.loopRun(selectedservo,force_control.value,loop_times.value)
 }
 }
///故障复位键
Label{text: "故障复位:"}
Button{text:"复位"
onClicked: {
Cpp_MDPLC.error_reset(selectedservo)
}
}
Button{text: "停止运动"
onClicked: {
 Cpp_MDPLC.stop(selectedservo)
}
}
  //
  // Spacer
  //
  Item {
      Layout.minimumHeight: app.spacing / 2
      Layout.maximumHeight: app.spacing / 2
  }
  Item {
      Layout.minimumHeight: app.spacing / 2
      Layout.maximumHeight: app.spacing / 2
  }
}
  Item {
  Layout.fillHeight: true
      }
}
///基础参数配置
function parameter_configur(R_speed,AC_T,DC_T,I_speed,I_increment)
{
Cpp_MDPLC.parameter_configur(selectedservo,R_speed,AC_T,DC_T,I_speed,I_increment)
}
}


