#ifndef IMG_H
#define IMG_H

#include <QStyledItemDelegate>

class img: public QStyledItemDelegate {
    public:
        img(QWidget* parent = 0);
        void paint(QPainter* painter, const QStyleOptionViewItem& option,
                   const QModelIndex& index) const override;
};

#endif // IMG_H
