#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QMap>
#include<QList>
#include<QUrl>
#include<QTimer>
#include<QEvent>
#include<QMouseEvent>
#include<QContextMenuEvent>
#include<QMenu>

class QPaintEvent;

//枚举存储所有动作
namespace Act {
Q_NAMESPACE
enum RoleAct {
    b,
    bhc,
    d,
    ee,
    eend,
    eing,
    find,
    hc,
    hs,
    hx,
    hx2,
    mg,
    eeend
};
Q_ENUM_NS(RoleAct)
}


using namespace Act;


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    //动作展示
    void showActAnimation(RoleAct k);

public slots:
    void OnMenuTriggered(QAction* action);

protected:
    void paintEvent(QPaintEvent* event)override;
    void contextMenuEvent(QContextMenuEvent* event);

private:
    void loadRoleActRes();
    void initMenu();
private:
    QMap<RoleAct,QList<QUrl>> action_map; //存储动作和对应的资源映射
    QTimer* timer;//定时器对象，控制动画播放速度
    RoleAct cur_role_act;//当前展示动作
    QUrl cur_role_pix;//当前动作的图片资源
    QMenu* menu;//右键菜单
};

class DragFilter:public QObject{

public:
    bool eventFilter(QObject* obj,QEvent* event)//窗口拖动
    {
        auto w = dynamic_cast<QWidget*>(obj);
        if(!w)
            return false;
        if(event->type()==QEvent::MouseButtonPress)//鼠标按压
        {
            auto e = dynamic_cast<QMouseEvent*>(event);
            if(e)
            {
               pos = e->pos();//记录鼠标按下时的位置
            }
        }
        else if(event->type()==QEvent::MouseMove)//鼠标移动
        {
            auto e = dynamic_cast<QMouseEvent*>(event);
            if(e)
            {
                if(e->buttons()&Qt::MouseButton::LeftButton)//左键按压
                {
                 w->move(e->globalPosition().toPoint()-pos);//移动窗口
                }
            }
        }
        return QObject::eventFilter(obj,event);
    }
private:
    QPoint pos;//鼠标位置
};



#endif // WIDGET_H

