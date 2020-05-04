#ifndef Q_TABBAR_H_H
#define Q_TABBAR_H_H
#include <QTabBar>
#include <QTabWidget>
#include <QStylePainter>
#include <QStyleOptionTab>

class qtabbar_h : public QTabBar{
protected:
    QSize tabSizeHint(int) const override;
    void paintEvent(QPaintEvent*) override;
};

class qtabwidget_h : public QTabWidget{
public:
    qtabwidget_h();
};

#endif