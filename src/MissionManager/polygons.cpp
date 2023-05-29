#include "polygons.h"
#include <QDebug>
#include "src/MissionManager/missioncontroller.h"

QList<MavMission*>* Polygons::readMissionItem = nullptr;

int Polygons::planScreenW = 0;
int Polygons::planScreenH = 0;

Polygons::Polygons(QObject *parent) : QObject(parent)
{
    connect(this,&Polygons::addItem,this,&Polygons::addmissionitem);
    connect(this,&Polygons::insertItem,this,&Polygons::insertmissionitem);
}

int Polygons::Getx()
{
    return getx;
}

int Polygons::Gety()
{
    return gety;
}

int Polygons::getIndex()
{
    return index;
}

int Polygons::getMissionitemfocus()
{
    return missionitemfocus;

}

void Polygons::setPlanScreenW(int W)
{
    planScreenW = W;
    emit PlanScreenWChanged();
}

void Polygons::setPlanScreenH(int H)
{
    planScreenH = H;
    emit PlanScreenHChanged();
}

void Polygons::setGetx(int x)
{
    getx = x;
    emit getxChanged();
}

void Polygons::setGety(int x)
{
    gety = x;
    if(isInsert)
        emit insertItem();
    else
        emit addItem();
}

void Polygons::setIndex(int x)
{
    index = x;
}

void Polygons::setisInsert(bool T)
{
    isInsert = T;

}

bool Polygons::getisInsert()
{
    return isInsert;
}

void Polygons::senddata()
{
    //my_vehivle.sendToVehicle();
}


void Polygons::setMissionitemfocus(int x)
{
    int curCount=0;
    missionitemfocus = x;
    //currentEditItemIndex = missionitemfocus;
    if(missionitemfocus != _polygons.count()){
        isInsert = true;
    }
    else{
        curCount = _lineModel.count();
        precoordinatex = ((missionitem*)_lineModel.get(curCount-1))->number_x ;
        precoordinatey = ((missionitem*)_lineModel.get(curCount-1))->number_y ;
        isInsert = false;
    }
    //qDebug() << missionitemfocus;
    ((missionitem*)_polygons.get(missionitemfocus-1))->setfocus(true);
    for(count=1;count<=_polygons.count();count++)
    {
        if(count==missionitemfocus)
            continue;
        //qDebug() << ((missionitem*)_polygons.get(count));
        ((missionitem*)_polygons.get(count-1))->setfocus(false);
    }
}
void Polygons::setprecoordinate(int x, int y)
{
    precoordinatex = x ;      //画线操作的前一点数据
    precoordinatey = y ;
}

void Polygons::clearmissionlist()
{
    _polygons.clear();
    _lineModel.clear();
    isInsert = false;
}

void Polygons::userDefinemission_s()
{
    int x = 100;
    int y = 50;
    int prex = x;
    int prey = y;
    bool isup = false;
    bool isorienta_x = false;
    missionitem* mission = new missionitem;
    mission->setNumber_x(x);
    mission->setNumber_y(y);
    mission->setPrenumber_x(prex);
    mission->setPrenumber_y(prey);
    mission->setMissionindex(1);
    mission->setfocus(false);
    _polygons.append(mission);
    _lineModel.append(mission);
    for(int i=2;i<=39;i++)
    {
        if(isorienta_x){
            x += 65;
            isorienta_x = false;
        }
        else if(isup){
            y -= 205;
        }
        else{
            y += 205;
        }
        if(i%3 == 0)
        {
            isorienta_x = true;
            isup = !isup;
        }
        missionitem* mission = new missionitem;
        mission->setNumber_x(x);
        mission->setNumber_y(y);
        mission->setPrenumber_x(prex);
        mission->setPrenumber_y(prey);
        mission->setMissionindex(i);
        mission->setfocus(false);
        _polygons.append(mission);
        _lineModel.append(mission);
        prex = x;
        prey = y;
    }

    //绕一圈
    y = y + 30;
    missionitem* mission_1 = new missionitem;
    mission_1->setNumber_x(x);
    mission_1->setNumber_y(y);
    mission_1->setPrenumber_x(prex);
    mission_1->setPrenumber_y(prey);
    mission_1->setMissionindex(40);
    mission_1->setfocus(false);
    _polygons.append(mission_1);
    _lineModel.append(mission_1);
    bool up = false;
    bool left = true;
    bool right = false;
    prex = x;
    prey = y;
    for(int j=1;j<=8;j++)
    {
        if(left){
            x = x - 410;
            if(j%2 == 0){
                up = true;
                left = false;
            }
        }
        else if(up){
            y = y - 235;
            if(j%2 == 0){

                right = true;
                up = false;
            }
        }
        else if(right){
            x = x + 430;
            if(j%2 == 0){
                right = false;
            }
        }
        else{
            y = y +240;
        }
        missionitem* mission_2 = new missionitem;
        mission_2->setNumber_x(x);
        mission_2->setNumber_y(y);
        mission_2->setPrenumber_x(prex);
        mission_2->setPrenumber_y(prey);
        mission_2->setMissionindex(40+j);
        if(j == 8)
            mission_2->setfocus(true);
        else
            mission_2->setfocus(false);
        _polygons.append(mission_2);
        _lineModel.append(mission_2);
        prex = x;
        prey = y;
    }
    precoordinatex = x;
    precoordinatey = y;
    missionitemfocus = 48;
}

void Polygons::userDefineMissionSimple()
{
    //考虑屏幕大小，在屏幕上显示的位置为:(x,y)*(W,H)/100
    //在发送给地面站的时候做归一化
    int x = 13;
    int y = 80;
    int prex = x;
    int prey = y;
    bool flag = false;
    //定义第一个点
    missionitem* mission = new missionitem;
    mission->setNumber_x(x*planScreenW/100);
    mission->setNumber_y(y*planScreenH/100);
    mission->setPrenumber_x(prex*planScreenW/100);
    mission->setPrenumber_y(prey*planScreenH/100);
    mission->setMissionindex(1);
    mission->setfocus(false);
    _polygons.append(mission);
    _lineModel.append(mission);
    for(int index = 2; index <= 8; index++)
    {
        //y坐标变化
        if(index % 2 == 1)
        {
            y -= 20;
        }
        //x坐标变化
        if(index % 2 == 0 && flag)
        {
            x = 13;
            flag = false;
        }
        else if(index % 2 == 0 && !flag)
        {
            x = 85;
            flag = true;
        }
        //存航点
        missionitem* mission = new missionitem;
        if(index != 8)
            mission->setNumber_x(x*planScreenW/100);
        else
            mission->setNumber_x((x-5)*planScreenW/100);
        mission->setNumber_y(y*planScreenH/100);
        mission->setPrenumber_x(prex*planScreenW/100);
        mission->setPrenumber_y(prey*planScreenH/100);
        mission->setMissionindex(index);
        mission->setfocus(false);
        _polygons.append(mission);
        _lineModel.append(mission);
        if(index != 8)
            prex = x;
        else
            prex = 8;
        prey = y;
    }

    //绕一圈
    x = 8;
    y = 85;
    missionitem* mission_1 = new missionitem;
    mission_1->setNumber_x(x*planScreenW/100);
    mission_1->setNumber_y(y*planScreenH/100);
    mission_1->setPrenumber_x(prex*planScreenW/100);
    mission_1->setPrenumber_y(prey*planScreenH/100);
    mission_1->setMissionindex(9);
    mission_1->setfocus(false);
    _polygons.append(mission_1);
    _lineModel.append(mission_1);
    prex = x;
    prey = y;

    x = 90;
    y = 85;
    missionitem* mission_2 = new missionitem;
    mission_2->setNumber_x(x*planScreenW/100);
    mission_2->setNumber_y(y*planScreenH/100);
    mission_2->setPrenumber_x(prex*planScreenW/100);
    mission_2->setPrenumber_y(prey*planScreenH/100);
    mission_2->setMissionindex(10);
    mission_2->setfocus(false);
    _polygons.append(mission_2);
    _lineModel.append(mission_2);
    prex = x;
    prey = y;

    x = 90;
    y = 15;
    missionitem* mission_3 = new missionitem;
    mission_3->setNumber_x(x*planScreenW/100);
    mission_3->setNumber_y(y*planScreenH/100);
    mission_3->setPrenumber_x(prex*planScreenW/100);
    mission_3->setPrenumber_y(prey*planScreenH/100);
    mission_3->setMissionindex(11);
    mission_3->setfocus(false);
    _polygons.append(mission_3);
    _lineModel.append(mission_3);
    prex = x;
    prey = y;

    x = 8;
    y = 15;
    missionitem* mission_4 = new missionitem;
    mission_4->setNumber_x(x*planScreenW/100);
    mission_4->setNumber_y(y*planScreenH/100);
    mission_4->setPrenumber_x(prex*planScreenW/100);
    mission_4->setPrenumber_y(prey*planScreenH/100);
    mission_4->setMissionindex(12);
    mission_4->setfocus(true);
    _polygons.append(mission_4);
    _lineModel.append(mission_4);

    precoordinatex = x*planScreenW/100;
    precoordinatey = y*planScreenH/100;
    missionitemfocus = 12;
}

void Polygons::getPlanScreenWH(int W, int H)
{
    setPlanScreenH(H);
    setPlanScreenW(W);
}

void Polygons::missiondrag(int index,int coordx,int coordy)
{
    int dragindex = index;
    ((missionitem*)_polygons.get(dragindex-1))->setNumber_x(coordx);
    ((missionitem*)_polygons.get(dragindex-1))->setNumber_y(coordy);

    int preX=0,preY=0;


    //存下编辑点的后一点的坐标值，方便后面修改
    if(dragindex==1){
        preX = ((missionitem*)_lineModel.get(dragindex-1))->number_x;
        preY = ((missionitem*)_lineModel.get(dragindex-1))->number_y;
    }
    else{
        preX = ((missionitem*)_lineModel.get(dragindex-2))->number_x;
        preY = ((missionitem*)_lineModel.get(dragindex-2))->number_y;
    }


    _lineModel.removeAt(dragindex-1);
    //插入点的linemodel，在后面补上前一点的坐标
    missionitem* myobject_1 = new missionitem;
    myobject_1->setNumber_x(coordx);
    myobject_1->setNumber_y(coordy);
    myobject_1->setPrenumber_x(preX);
    myobject_1->setPrenumber_y(preY);
    _lineModel.insert(dragindex-1,myobject_1);

    if(_polygons.count()!=dragindex){
        int nextX=0,nextY=0;
        nextX = ((missionitem*)_lineModel.get(dragindex))->number_x;
        nextY = ((missionitem*)_lineModel.get(dragindex))->number_y;
        _lineModel.removeAt(dragindex);
        //插入点的后一点的linemodel，在后面补上前一点的坐标
        missionitem* myobject_2 = new missionitem;
        myobject_2->setNumber_x(nextX);
        myobject_2->setNumber_y(nextY);
        myobject_2->setPrenumber_x(coordx);
        myobject_2->setPrenumber_y(coordy);
        _lineModel.insert(dragindex,myobject_2);
        emit _polygons.dataChanged(_lineModel.index(index), _lineModel.index(index));
    }


    emit _polygons.dataChanged(_polygons.index(index-1), _polygons.index(index-1));

    emit _polygons.dataChanged(_lineModel.index(index-1), _lineModel.index(index-1));
    precoordinatex = coordx;
    precoordinatey = coordy;


}


//中间点一般化，起点和终点特殊化
void Polygons::missiondel()
{
    if(missionitemfocus!=_polygons.count())
    {
        int prex,prey;
        int nextx,nexty;
        qDebug()<<missionitemfocus;
        prex = ((missionitem*)_lineModel.get(missionitemfocus-1))->prenumber_x;
        prey = ((missionitem*)_lineModel.get(missionitemfocus-1))->prenumber_y;
        nextx = ((missionitem*)_lineModel.get(missionitemfocus))->number_x;
        nexty = ((missionitem*)_lineModel.get(missionitemfocus))->number_y;

        //保存删除任务点的前一个点坐标，方便后续添加任务点
        precoordinatex = ((missionitem*)_polygons.get(missionitemfocus-1))->prenumber_x;
        precoordinatey = ((missionitem*)_polygons.get(missionitemfocus-1))->prenumber_y;

        _lineModel.removeAt(missionitemfocus-1);
        _lineModel.removeAt(missionitemfocus-1); //list变短所以索引一样

        missionitem* object = new missionitem;
        if(missionitemfocus==1){
            object->setNumber_x(nextx);
            object->setNumber_y(nexty);
            object->setPrenumber_x(nextx);
            object->setPrenumber_y(nexty);
        }
        else{
            object->setNumber_x(nextx);
            object->setNumber_y(nexty);
            object->setPrenumber_x(prex);
            object->setPrenumber_y(prey);
        }


        _lineModel.insert(missionitemfocus-1,object);

        _polygons.removeAt(missionitemfocus-1);
        ((missionitem*)_polygons.get(missionitemfocus-1))->setPrenumber_x(prex);
        ((missionitem*)_polygons.get(missionitemfocus-1))->setPrenumber_y(prey);

        if(missionitemfocus==1){
            ((missionitem*)_polygons.get(missionitemfocus-1))->setfocus(true);
        }
        else{
            ((missionitem*)_polygons.get(missionitemfocus-2))->setfocus(true);
            missionitemfocus--;
        }

        qDebug()<<missionitemfocus;

        for(int i = missionitemfocus;i<=_polygons.count();i++)
        {
            ((missionitem*)_polygons.get(i-1))->setMissionindex(i);
            emit _polygons.dataChanged(_polygons.index(i-1), _polygons.index(i-1));
        }
    }
    else if(missionitemfocus==_polygons.count()&&missionitemfocus!=1){
        //保存删除任务点的前一个点坐标，方便后续添加任务点
        precoordinatex = ((missionitem*)_polygons.get(missionitemfocus-1))->prenumber_x;
        precoordinatey = ((missionitem*)_polygons.get(missionitemfocus-1))->prenumber_y;

        _polygons.removeAt(missionitemfocus-1);
        _lineModel.removeAt(missionitemfocus-1);
        missionitemfocus--;
        ((missionitem*)_polygons.get(missionitemfocus-1))->setfocus(true);

        qDebug()<<missionitemfocus;
    }
    else{
        clearmissionlist();

    }

}


void Polygons::addmissionitem()
{
    //在这里面new
    missionitemfocus++;
    missionitem* myobject = new missionitem;
    myobject->setMissionindex(index);
    myobject->setNumber_x(getx);
    myobject->setNumber_y(gety);
    myobject->setfocus(true);
    if(_polygons.count()==0)
    {
        myobject->setPrenumber_x(getx);
        myobject->setPrenumber_y(gety);
    }
    else
    {
        myobject->setPrenumber_x(precoordinatex);
        myobject->setPrenumber_y(precoordinatey);
    }


    //qDebug() << myobject->missionindex << "//" << myobject->number_x << "//" << myobject->number_y;

    //将任务点存进list
    _polygons.append(myobject);
    _lineModel.append(myobject);

    //每点一次将前面的项的focus属性置为false
    for(count=1;count<_polygons.count();count++)
    {
        //qDebug() << ((missionitem*)_polygons.get(count));
        ((missionitem*)_polygons.get(count-1))->setfocus(false);      //list里面从第0行开始
    }
}

void Polygons::delObjct(int index)
{
    _polygons.removeAt(index);
}

void Polygons::insertmissionitem()
{
    int tempX=0,tempY=0;

    //存下编辑点的后一点的坐标值，方便后面修改
    tempX = ((missionitem*)_lineModel.get(missionitemfocus))->number_x;
    tempY = ((missionitem*)_lineModel.get(missionitemfocus))->number_y;

    _lineModel.removeAt(missionitemfocus);

    //插入点的linemodel，在后面补上前一点的坐标
    missionitem* myobject_1 = new missionitem;
    myobject_1->setNumber_x(getx);
    myobject_1->setNumber_y(gety);
    _lineModel.insert(missionitemfocus,myobject_1);

    //插入点的后一点的linemodel，在后面补上前一点的坐标
    missionitem* myobject_2 = new missionitem;
    myobject_2->setNumber_x(tempX);
    myobject_2->setNumber_y(tempY);
    _lineModel.insert(missionitemfocus+1,myobject_2);

    //插入点的missionmodel
    missionitemfocus++;
    qDebug() << "missionitemfocus:" << missionitemfocus;
    missionitem* myobject = new missionitem;
    myobject->setMissionindex(missionitemfocus);
    myobject->setNumber_x(getx);
    myobject->setNumber_y(gety);
    myobject->setfocus(true);
    //存入前一点的坐标值，也可不用，但还是保证missionitem'的完整性
    myobject->setPrenumber_x(((missionitem*)_polygons.get(missionitemfocus-2))->number_x);
    myobject->setPrenumber_y(((missionitem*)_polygons.get(missionitemfocus-2))->number_y);

    _polygons.insert(missionitemfocus-1,myobject);

    //后一项存入当前点的坐标值，上面说的补全坐标点在这里
    ((missionitem*)_lineModel.get(missionitemfocus-1))->setPrenumber_x(((missionitem*)_polygons.get(missionitemfocus-2))->number_x);
    ((missionitem*)_lineModel.get(missionitemfocus-1))->setPrenumber_y(((missionitem*)_polygons.get(missionitemfocus-2))->number_y);
    ((missionitem*)_lineModel.get(missionitemfocus))->setPrenumber_x(getx);
    ((missionitem*)_lineModel.get(missionitemfocus))->setPrenumber_y(gety);

    ((missionitem*)_polygons.get(missionitemfocus-2))->setfocus(false);  //前一项的取消聚焦

    //需要将后面的项的index加一
    for(int i = missionitemfocus;i<_polygons.count();i++)
    {
        ((missionitem*)_polygons.get(i))->setMissionindex(i+1);
        //qDebug()<<  ((missionitem*)_polygons.get(i))->missionindex;
        emit _polygons.dataChanged(_polygons.index(i), _polygons.index(i));
    }

    //
    emit _lineModel.dataChanged(_lineModel.index(missionitemfocus-1), _lineModel.index(missionitemfocus-1));
    emit _lineModel.dataChanged(_lineModel.index(missionitemfocus), _lineModel.index(missionitemfocus));

}

void Polygons::convertToMissonitem()
{
    qDebug()<<"convert to missionitem: "<<readMissionItem->count();
    //清除原有的任务点
    _polygons.clear();
    _lineModel.clear();
    isInsert = false;
    //还没写好，在重新规划行航点时会崩溃
    //需要再看一下行航点显示逻辑

    int prenumber_x = 0;
    int prenumber_y = 0;
    for(int index = 0; index < readMissionItem->count(); index++)
    {
        MavMission* mavItem = (*readMissionItem)[index];
        missionitem* missionItem = new missionitem;
        missionItem->setMissionindex(mavItem->sequenceNumber()+1);
        missionItem->setNumber_x(mavItem->param5());
        missionItem->setNumber_y(mavItem->param6());
        qDebug()<<"x:"<<mavItem->param5();
        qDebug()<<"y:"<<mavItem->param6();

        //第一个点的pre xy等于自己的xy
        if(index == 0){
            missionItem->setPrenumber_x(mavItem->param5());
            missionItem->setPrenumber_y(mavItem->param6());
        }
        else{
            missionItem->setPrenumber_x(prenumber_x);
            missionItem->setPrenumber_y(prenumber_y);
        }

        prenumber_x = mavItem->param5();    //记录前一个点的xy坐标
        prenumber_y = mavItem->param6();

        //最后一个点聚焦
        if(index == readMissionItem->count()-1)
            missionItem->setfocus(true);
        else
            missionItem->setfocus(false);
        //加入航点
        _polygons.append(missionItem);
        _lineModel.append(missionItem);
    }

    //读完之后更新index，foucus等
    missionitemfocus = readMissionItem->count();
    index = readMissionItem->count();
    currentEditItemIndex = readMissionItem->count();
    setprecoordinate(prenumber_x,prenumber_y);

}



