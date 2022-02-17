#ifndef DATAMAP_H
#define DATAMAP_H

#include <QObject>
#include<QMap>
#include<initializer_list>
#include<QTime>
#include<Singleton.h>
#include"Utilities.h"
#include<QFile>
#include<QDir>
#include<QTimer>
#include<atomic>
/*
数据中心：保存csv,不提供截取功能 保存过后自动清除数据和图表
1.存储PLC中的轴向压力和侧向压力
2.存储PLC中的温度1，温度2，温度3
3.存储串口中的真空计压力和红外测温仪压力
*/
class datamap:public QObject,public My::Singleton<datamap>
{
 Q_OBJECT
  //t1 axisforce sideforce t1 t2 t4
 Q_PROPERTY(QVariantList plcUidata READ plcUidata WRITE setPlcUidata NOTIFY plcUidataChanged)
 //t2 p1  t1
 Q_PROPERTY(QVariantList serialUidata READ serialUidata WRITE setSerialUidata NOTIFY serialUidataChanged)


 public:
 datamap(token t);
 datamap(const datamap&)=delete;
 datamap&operator=(const datamap&)=delete;
 ~datamap();
 enum KPSDataType{
    axisforce=0,
    sideforce,
    temp1,
    temp2,
    temp3,
    vacuum_gauge,
    infrared_temp
  };
 Q_ENUM(KPSDataType);

 ///保存数据到CSV
 Q_INVOKABLE void DataSave();
 //界面更新
 Q_INVOKABLE void uiUpdate();

 const QVariantList &plcUidata() const;
 const QVariantList &serialUidata() const;
public Q_SLOTS:
 // cout 5
 void plcappend   (   qreal axisforce,   qreal side_force,
                      qreal temp1,       qreal temp2,qreal temp3);
 void serialappend(   qreal vacuum_gauge,qreal infrared_temp);
 void setSerialUidata(const QVariantList &newSerialUidata);
 void setPlcUidata(const QVariantList &newPlcUidata);
 Q_SIGNALS:
 void cleared();//清除数据时触发信号 清除图表内容




 void plcUidataChanged();

 void serialUidataChanged();

private:
 ///plc时间 ms
  QList<int> plct;
  ///串口时间 ms
  QList<int> serialt;
 ///侧向加载力    力pa
 QList<float> side_data_;
 ///轴向加载力    力pa
 QList<float> axis_data_;

 QList<float> temp1_;//℃
 QList<float> temp2_;//℃
 QList<float> temp3_;//℃

 ///真空计    pa
 QList<qreal> vacuum_gauge_data_;
 ///红外测温仪 ℃
 QList<qreal> infrared_temp_data_;

 QTimer Uitimer;
 std::atomic<int> count=0;;

private:
 void clearMap();


 QVariantList m_uidata;
 QVariantList m_plcUidata;
 QVariantList m_serialUidata;
};
#endif // DATAMAP_H
