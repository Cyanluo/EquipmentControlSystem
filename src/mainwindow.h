#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Q_PROPERTY(quint16 coordinate_x READ currentcoordinate_x WRITE setCoordinate_x NOTIFY coordinate_xChanged)
    Q_PROPERTY(quint16 coordinate_y READ currentcoordinate_y WRITE setCoordinate_y NOTIFY coordinate_yChanged)
    void setCoordinate_x(const quint16 _coordinate);
    quint16 currentcoordinate_x();

    void setCoordinate_y(const quint16 _coordinate);
    quint16 currentcoordinate_y();

private:
    void initServer(void);
    quint16 coordinate_x;
    quint16 coordinate_y;

    //槽函数
    void slotNewConnected(void);
    void slotReadyRead(void);

signals:
    void coordinate_xChanged();
    void coordinate_yChanged();

private:
    Ui::MainWindow *ui;
    QString recivedata;
    QTcpServer *server;
    QTcpSocket *socket;
};
#endif // MAINWINDOW_H
