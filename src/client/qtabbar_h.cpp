#include "client/qtabbar_h.h"

QSize qtabbar_h::tabSizeHint(int idx) const{
    QSize s = QTabBar::tabSizeHint(idx);
    s.transpose();
    return s;
}

void qtabbar_h::paintEvent(QPaintEvent* event){
    QStyleOptionTab opt;
    QStylePainter painter(this);
    for(int i = 0; i < count(); ++i){
        initStyleOption(&opt,i);
        painter.drawControl(QStyle::CE_TabBarTabShape, opt);
        painter.save();
	QSize s = opt.rect.size();
	s.transpose();
        QRect r(QPoint(), s);
        r.moveCenter(opt.rect.center());
        opt.rect = r;

        QPoint tab_rect_center = tabRect(i).center();
        painter.translate(tab_rect_center);
        painter.rotate(90);
        painter.translate(-tab_rect_center);
        painter.drawControl(QStyle::CE_TabBarTabLabel, opt);
        painter.restore();
    }
}

qtabwidget_h::qtabwidget_h(){
    setTabBar(new qtabbar_h());
    setTabPosition(QTabWidget::West);
}
