#ifndef POLYGONS_H
#define POLYGONS_H
#include "qmlobjectlistmodel.h"
#include <QObject>
#include "missionitem.h"
#include <src/vehicle/vehicle.h>

class Polygons :public QObject
{
    Q_OBJECT
public:
    explicit Polygons(QObject *parent = nullptr);
    Q_PROPERTY(QmlObjectListModel* polygons READ polygons CONSTANT)
    Q_PROPERTY(QmlObjectListModel* lineModel READ lineModel CONSTANT)
    Q_PROPERTY(int getx READ Getx WRITE setGetx NOTIFY getxChanged)
    Q_PROPERTY(int gety READ Gety WRITE setGety NOTIFY getyChanged)
    Q_PROPERTY(int index READ getIndex WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(int missionitemfocus READ getMissionitemfocus WRITE setMissionitemfocus NOTIFY missionitemfocusChanged)
    Q_PROPERTY(bool isInsert READ getisInsert WRITE setisInsert NOTIFY isInsertChanged)


    int Getx(void);
    int Gety(void);
    int getIndex(void);
    int getMissionitemfocus();



    Q_INVOKABLE void delObjct(int index);
    Q_INVOKABLE void setGetx(int x);
    Q_INVOKABLE void setGety(int x);
    Q_INVOKABLE void setIndex(int x);
    Q_INVOKABLE void setMissionitemfocus(int x);      //设置当前的聚焦任务点
    Q_INVOKABLE void setprecoordinate(int x,int y);   //存入前一点的坐标 note:前一点坐标实现由滞后设置实现
    Q_INVOKABLE void clearmissionlist();              //清除任务点
    Q_INVOKABLE void userDefinemission_s();           //自定义任务1--s型
    Q_INVOKABLE void missiondrag(int index,int coordx,int coordy);                   //任务点拖动
    Q_INVOKABLE void missiondel();                     //删除某一任务点
    Q_INVOKABLE void setisInsert(bool T);
    Q_INVOKABLE bool getisInsert();

    Q_INVOKABLE void senddata();


    QmlObjectListModel* polygons(void)  { return &_polygons;  }
    QmlObjectListModel* lineModel(void) { return &_lineModel; }
    bool isInsert = false;             //下一步是否为插入点
    bool exist_a_path = false;         //页面是否已有路径

signals:
    void getxChanged();
    void getyChanged();
    void indexChanged();
    void missionitemfocusChanged();
    void addItem();            //顺序加节点
    void insertItem();         //插入节点
    void isInsertChanged();



public slots:
    void addmissionitem();
    void insertmissionitem();

private:
    int count;
    int getx;
    int gety;
    int index;
    int missionitemfocus;
    int precoordinatex;      //画线操作的前一点数据
    int precoordinatey;
    int currentEditItemIndex = 0;     //记录当前编辑的是哪一项

    QmlObjectListModel  _polygons;
    QmlObjectListModel  _lineModel;

};

#endif // POLYGONS_H
