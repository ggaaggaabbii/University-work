#ifndef COSTOMMODEL_H
#define COSTOMMODEL_H

#include <QAbstractTableModel>
#include "WatchList.h"
#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QStandardItem>
#include <QVariant>

class CostomModel: public QAbstractTableModel {
    private:
        WatchList& wList;
    public:
        CostomModel(WatchList& w, QObject* parent = NULL);
        int rowCount(const QModelIndex& parent) const override;
        int columnCount(const QModelIndex& parent) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation,
                            int role = Qt::DisplayRole) const override;
};

#endif // COSTOMMODEL_H
