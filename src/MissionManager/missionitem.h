#ifndef MISSIONITEM_H
#define MISSIONITEM_H

#include <QObject>

class missionitem: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int number_x READ getNumber_x WRITE setNumber_x NOTIFY number_xChanged)
    Q_PROPERTY(int number_y READ getNumber_y WRITE setNumber_y NOTIFY number_yChanged)
    Q_PROPERTY(int missionindex READ getMissionindex WRITE setMissionindex NOTIFY missionindexChanged)
    Q_PROPERTY(bool focus READ getfocus WRITE setfocus NOTIFY focusChanged)
    Q_PROPERTY(int prenumber_x READ getPrenumber_x WRITE setPrenumber_x NOTIFY prenumber_xChanged)
    Q_PROPERTY(int prenumber_y READ getPrenumber_y WRITE setPrenumber_y NOTIFY prenumber_yChanged)

public:
    missionitem();
    int getNumber_x() const;
    Q_INVOKABLE void setNumber_x(int i);
    int getNumber_y() const;
    Q_INVOKABLE void setNumber_y(int i);
    int getMissionindex() const;
    Q_INVOKABLE void setMissionindex(int i);
    bool getfocus();
    Q_INVOKABLE void setfocus(bool isfocus);
    int getPrenumber_x();
    int getPrenumber_y();
    Q_INVOKABLE void setPrenumber_x(int x);
    Q_INVOKABLE void setPrenumber_y(int y);

signals:
    void number_xChanged();
    void number_yChanged();
    void missionindexChanged();
    void focusChanged();
    void prenumber_xChanged();
    void prenumber_yChanged();

public:
    int missionindex = 0;
    int number_x = 0;
    int number_y = 0;
    int prenumber_x ;      //画线操作的前一点数据
    int prenumber_y ;
    bool focus = true;
};

#endif // MISSIONITEM_H
